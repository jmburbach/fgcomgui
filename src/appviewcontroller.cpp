/* FGComGui - A simple gui frontend for fgcom.
 *
 * Copyright (C) 2009 Jacob Burbach <jmburbach@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 3, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "appviewcontroller.hpp"
#include "settingsmodel.hpp"
#include "settingsview.hpp"

#include <QPushButton>
#include <QTextEdit>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QCloseEvent>
#include <QProcess>
#include <QTextEdit>


namespace FGComGui {

	AppViewController::AppViewController()
		: QMainWindow(0)
		, m_model(new SettingsModel)
		, m_settings_view(new SettingsView(this))
		, m_start_button(new QPushButton("Start", this))
		, m_stop_button(new QPushButton("Stop", this))
		, m_process_output(new QTextEdit(this))
		, m_systray(new QSystemTrayIcon(this))
		, m_process(new QProcess(this))
	{
		QIcon icon(":images/appicon.png");

		resize(600, 400);
		setWindowTitle("FGCom Gui");
		setWindowIcon(icon);

		QMenu* file_menu = menuBar()->addMenu("&File");
		file_menu->addAction("&Quit", qApp, SLOT(quit()));
		
		statusBar();

		QWidget* widget = new QWidget(this);
		QVBoxLayout* layout = new QVBoxLayout;
		widget->setLayout(layout);
		setCentralWidget(widget);

		m_settings_view->set_mode(m_model->get_mode());
		m_settings_view->set_path(m_model->get_path());
		m_settings_view->set_input_volume(m_model->get_input_volume());
		m_settings_view->set_output_volume(m_model->get_output_volume());
		layout->addWidget(m_settings_view);

		QHBoxLayout* button_layout = new QHBoxLayout;
		button_layout->addWidget(m_start_button);
		button_layout->addWidget(m_stop_button);
		layout->addLayout(button_layout);

		m_start_button->setToolTip("start fgcom");
		m_stop_button->setToolTip("stop fgcom");

		m_process_output->setReadOnly(true);
		layout->addWidget(m_process_output);
		
		m_systray->setIcon(icon);
		m_systray->setContextMenu(file_menu);
		m_systray->setToolTip("FGCom Gui");
		m_systray->show();

		connect(m_settings_view, SIGNAL(mode_changed(RunMode)),
			   	this, SLOT(handle_mode_change(RunMode)));
		connect(m_settings_view, SIGNAL(path_changed(const QString&)),
			   	this, SLOT(handle_path_change(const QString&)));
		connect(m_settings_view, SIGNAL(input_volume_changed(float)),
				this, SLOT(handle_input_volume_change(float)));
		connect(m_settings_view, SIGNAL(output_volume_changed(float)),
				this, SLOT(handle_output_volume_change(float)));
		connect(m_systray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
				this, SLOT(handle_system_tray_activation(QSystemTrayIcon::ActivationReason)));
		connect(m_start_button, SIGNAL(clicked()),
				this, SLOT(handle_start_request()));
		connect(m_stop_button, SIGNAL(clicked()),
				this, SLOT(handle_stop_request()));
		connect(m_process, SIGNAL(stateChanged(QProcess::ProcessState)),
				this, SLOT(handle_process_state_change(QProcess::ProcessState)));
		connect(m_process, SIGNAL(readyRead()),
				this, SLOT(handle_process_output()));
		connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)),
				this, SLOT(handle_process_finished(int, QProcess::ExitStatus)));
		connect(m_process, SIGNAL(error(QProcess::ProcessError)),
				this, SLOT(handle_process_error(QProcess::ProcessError)));
	}

	AppViewController::~AppViewController()
	{
		delete m_model;
	}

	void AppViewController::closeEvent(QCloseEvent* event)
	{
		hide();
		event->ignore();
		m_systray->showMessage("FGComGui", "FGComGui has been hidden to the system tray");
	}

	void AppViewController::handle_mode_change(RunMode mode)
	{
		m_model->set_mode(mode);
	}

	void AppViewController::handle_path_change(const QString& path)
	{
		m_model->set_path(path);
	}

	void AppViewController::handle_input_volume_change(float v)
	{
		m_model->set_input_volume(v);
	}

	void AppViewController::handle_output_volume_change(float v)
	{
		m_model->set_output_volume(v);
	}

	void AppViewController::handle_system_tray_activation(QSystemTrayIcon::ActivationReason reason)
	{
		if (reason == QSystemTrayIcon::Trigger) {
			if (isVisible()) {
				m_savedPos = pos();
				hide();
			}
			else {
				show();
				move(m_savedPos);
			}
		}
	}

	void AppViewController::handle_start_request()
	{
		QString cmd = m_model->get_path();

		QStringList args;
		args << "-Sfgcom.flightgear.org.uk"
			<< "-i" + QString::number(m_model->get_input_volume())
			<< "-o" + QString::number(m_model->get_output_volume());

		if (m_model->get_mode() == RM_TEST) 
			args << "-f910";

		// merge stderr with stdout
		m_process->setProcessChannelMode(QProcess::MergedChannels);
		m_process->setReadChannel(QProcess::StandardOutput);
		
		m_process->start(cmd, args);

		m_process->closeWriteChannel();
		m_process_output->clear();
	}

	void AppViewController::handle_stop_request()
	{
		m_process->kill();
		m_process->waitForFinished();
	}

	void AppViewController::handle_process_state_change(QProcess::ProcessState state)
	{
		switch (state) {
			case QProcess::Starting:
			case QProcess::Running:
				m_settings_view->setEnabled(false);
				m_start_button->setEnabled(false);
				m_stop_button->setEnabled(true);
				break;
			case QProcess::NotRunning:
				m_settings_view->setEnabled(true);
				m_start_button->setEnabled(true);
				m_stop_button->setEnabled(false);
				break;
		}
	}

	void AppViewController::handle_process_output()
	{
		QByteArray output = m_process->readAll();
		if (output.isEmpty())
			return;
		m_process_output->insertPlainText(output);
		m_process_output->moveCursor(QTextCursor::End);
	}

	void AppViewController::handle_process_finished(int code, QProcess::ExitStatus status)
	{
		m_process_output->append(">> process finished with code: " + QString::number(code) + '\n');
		m_process_output->moveCursor(QTextCursor::End);
	}

	void AppViewController::handle_process_error(QProcess::ProcessError error)
	{
		QString message(">> error: ");

		switch (error) {
			case QProcess::FailedToStart:
				message += "process failed to start; incorrect path?";
				break;
			case QProcess::ReadError:
				message += "error reading from process";
				break;
			case QProcess::UnknownError:
				message += "unknown error";
				break;
			default:
				return;
		}

		m_process_output->append(message + '\n');
		m_process_output->moveCursor(QTextCursor::End);
	}

} // namespace FGComGui

#include "appviewcontroller.hpp.moc"

