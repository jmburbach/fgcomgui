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

#include <iostream>

#include <QTimer>
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
#include <QStatusBar>
#include <QKeySequence>
#include <QMessageBox>


namespace FGComGui {

	AppViewController::AppViewController()
		: QMainWindow(0)
		, m_model(0)
		, m_settings_view(0)
		, m_start_button(0)
		, m_stop_button(0)
		, m_process_output(0)
		, m_systray(0)
		, m_process(0)
		, m_file_menu(0)
		, m_systray_menu(0)
		, m_quit_action(0)
		, m_start_action(0)
		, m_stop_action(0)
		, m_show_hide_action(0)
	{
		resize(600, 400);
		setWindowTitle("FGCom Gui");
		setWindowIcon(QIcon(":images/fgcomgui_22x22.png"));
		
		setup_actions();
		setup_menus();
		setup_systray();
		setup_process();
		statusBar();
		
		QWidget* widget = new QWidget(this);
		QVBoxLayout* layout = new QVBoxLayout;
		widget->setLayout(layout);
		setCentralWidget(widget);

		m_model = new SettingsModel;

		m_settings_view = new SettingsView(this);		
		m_settings_view->set_mode(m_model->get_mode());
		m_settings_view->set_path(m_model->get_path());
		m_settings_view->set_input_volume(m_model->get_input_volume());
		m_settings_view->set_output_volume(m_model->get_output_volume());
		layout->addWidget(m_settings_view);
		
		m_start_button = new QPushButton("Start", this);
		m_start_button->setToolTip("start fgcom");
		connect(m_start_button, SIGNAL(clicked()),
				m_start_action, SLOT(trigger()));

		m_stop_button = new QPushButton("Stop", this);
		m_stop_button->setToolTip("stop fgcom");
		connect(m_stop_button, SIGNAL(clicked()),
				m_stop_action, SLOT(trigger()));
		
		QHBoxLayout* button_layout = new QHBoxLayout;
		button_layout->addWidget(m_start_button);
		button_layout->addWidget(m_stop_button);
		layout->addLayout(button_layout);

		m_process_output = new QTextEdit(this);
		m_process_output->setReadOnly(true);
		layout->addWidget(m_process_output);

		connect(m_settings_view, SIGNAL(mode_changed(RunMode)),
			   	this, SLOT(handle_mode_change(RunMode)));
		connect(m_settings_view, SIGNAL(path_changed(const QString&)),
			   	this, SLOT(handle_path_change(const QString&)));
		connect(m_settings_view, SIGNAL(input_volume_changed(float)),
				this, SLOT(handle_input_volume_change(float)));
		connect(m_settings_view, SIGNAL(output_volume_changed(float)),
				this, SLOT(handle_output_volume_change(float)));

		setTabOrder(m_settings_view, m_start_button);
		setTabOrder(m_start_button, m_stop_button);
		setTabOrder(m_stop_button, m_process_output);

		m_start_button->setFocus(Qt::OtherFocusReason);
		m_stop_button->setEnabled(false);
		m_stop_action->setEnabled(false);
	}

	AppViewController::~AppViewController()
	{
		m_process->kill();
		m_process->waitForFinished();
		delete m_model;
	}

	void AppViewController::closeEvent(QCloseEvent* event)
	{
#if FGCOM_GUI_PLATFORM ==  FGCOM_GUI_PLATFORM_LINUX
		event->ignore();
		m_show_hide_action->trigger();
		m_systray->showMessage("FGComGui", "FGComGui will continue running in the system tray...");
#else
		event->ignore();
		m_quit_action->trigger();
#endif
	}

	void AppViewController::changeEvent(QEvent* event)
	{
#if FGCOM_GUI_PLATFORM == FGCOM_GUI_PLATFORM_MSWIN
		if (event->type() == QEvent::WindowStateChange) {
			QWindowStateChangeEvent* ce = static_cast<QWindowStateChangeEvent*>(event);
			bool was_minimized = ce->oldState() & Qt::WindowMinimized;
			bool is_minimized = windowState() & Qt::WindowMinimized;
			if (!was_minimized && is_minimized) {
				event->ignore();
				m_systray->showMessage("FGComGui", "FGComGui was minimized to the notification area...");
				
				// doesn't work properly if called directly...
				QTimer::singleShot(10, m_show_hide_action, SLOT(trigger()));
			}
		}
#else
		QMainWindow::changeEvent(event);
#endif
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
			m_show_hide_action->trigger();
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
				m_settings_view->setEnabled(false);
				m_start_button->setEnabled(false);
				m_start_action->setEnabled(false);
				m_stop_button->setEnabled(true);
				m_stop_action->setEnabled(true);
				statusBar()->showMessage("fgcom is starting", 3000);
				break;
			case QProcess::Running:
				statusBar()->showMessage("fgcom is running", 3000);
				break;
			case QProcess::NotRunning:
				m_settings_view->setEnabled(true);
				m_start_button->setEnabled(true);
				m_start_action->setEnabled(true);
				m_stop_button->setEnabled(false);
				m_stop_action->setEnabled(false);
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

	void AppViewController::handle_show_hide()
	{
		if (isVisible()) {
			hide();
			m_savedPos = pos();
		}
		else {
			show();
			setWindowState((windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
			move(m_savedPos);
		}
	}

	void AppViewController::setup_actions()
	{
		m_quit_action = new QAction("&Quit", this);
		m_quit_action->setShortcut(QKeySequence("Ctrl+Q"));
		connect(m_quit_action, SIGNAL(triggered()),
				this, SLOT(handle_quit_request()));

		m_start_action = new QAction("Start", this);
		connect(m_start_action, SIGNAL(triggered()),
				this, SLOT(handle_start_request()));

		m_stop_action = new QAction("Stop", this);
		connect(m_stop_action, SIGNAL(triggered()),
				this, SLOT(handle_stop_request()));

		m_show_hide_action = new QAction("Show/Hide", this);
		connect(m_show_hide_action, SIGNAL(triggered()),
				this, SLOT(handle_show_hide()));
	}

	void AppViewController::setup_menus()
	{
		m_file_menu = menuBar()->addMenu("&File");
		m_file_menu->addSeparator();
		m_file_menu->addAction(m_quit_action);
	}

	void AppViewController::setup_systray()
	{
		QIcon appicon(":images/fgcomgui_22x22.png");

		m_systray_menu = new QMenu("FGComGui", this);
		m_systray_menu->setIcon(appicon);
		m_systray_menu->addAction(m_show_hide_action);
		m_systray_menu->addAction(m_start_action);
		m_systray_menu->addAction(m_stop_action);
		m_systray_menu->addSeparator();
		m_systray_menu->addAction(m_quit_action);

		m_systray = new QSystemTrayIcon(this);
		m_systray->setIcon(appicon);
		m_systray->setToolTip("FGComGui");
		m_systray->setContextMenu(m_systray_menu);
		m_systray->show();
		
		connect(m_systray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
				this, SLOT(handle_system_tray_activation(QSystemTrayIcon::ActivationReason)));
	}

	void AppViewController::setup_process()
	{
		m_process = new QProcess(this);
		m_process->setProcessChannelMode(QProcess::MergedChannels);
		m_process->setReadChannel(QProcess::StandardOutput);
		
		connect(m_process, SIGNAL(stateChanged(QProcess::ProcessState)),
				this, SLOT(handle_process_state_change(QProcess::ProcessState)));
		connect(m_process, SIGNAL(readyRead()),
				this, SLOT(handle_process_output()));
		connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)),
				this, SLOT(handle_process_finished(int, QProcess::ExitStatus)));
		connect(m_process, SIGNAL(error(QProcess::ProcessError)),
				this, SLOT(handle_process_error(QProcess::ProcessError)));
	}

	void AppViewController::handle_quit_request()
	{
		QProcess::ProcessState state = m_process->state();
		if (state == QProcess::Running || state == QProcess::Starting) {
			QMessageBox query;
			query.setWindowTitle("FGComGui?");
			query.setText("FGCom is running.");
			query.setInformativeText("Are you sure you want to quit?");
			query.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
			query.setDefaultButton(QMessageBox::Yes);
			int rv = query.exec();
			if (rv == QMessageBox::Yes) {
				handle_stop_request();
				qApp->quit();
			}
		}
		else {
			qApp->quit();
		}
	}

} // namespace FGComGui

#include "appviewcontroller.hpp.moc"

