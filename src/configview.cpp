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
#include "configview.hpp"
#include "model.hpp"
#include "commonconfigview.hpp"

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QIntValidator>
#include <QFileDialog>
#include <QDir>
#include <QCheckBox>

#include <limits>


namespace FGComGui {

	ConfigView::ConfigView(QWidget* parent)
		: QWidget(parent)
	{
		Model& model = Model::get_instance();

		m_fgcom_path_edit = new QLineEdit(this);
		m_fgcom_path_edit->setToolTip("Name or full path to the fgcom binary");
		m_fgcom_path_edit->setText(model.get_fgcom_path());
		connect(m_fgcom_path_edit, SIGNAL(textEdited(const QString&)),
				this, SLOT(handle_fgcom_path_change(const QString&)));

		m_fgcom_path_button = new QPushButton(this);
		m_fgcom_path_button->setText("...");
		m_fgcom_path_button->setToolTip("open file browser");
		connect(m_fgcom_path_button, SIGNAL(clicked()),
				this, SLOT(handle_fgcom_path_browse()));

		m_fgcom_server_edit = new QLineEdit(this);
		m_fgcom_server_edit->setToolTip("FGCom server to connect to");
		m_fgcom_server_edit->setText(model.get_fgcom_server());
		connect(m_fgcom_server_edit, SIGNAL(textEdited(const QString&)),
				this, SLOT(handle_fgcom_server_change(const QString&)));

		m_fgfs_port_edit = new QLineEdit(this);
		m_fgfs_port_edit->setToolTip("Port that you configured flightgear to communicate with fgcom");
		m_fgfs_port_edit->setText(QString::number(model.get_fgfs_port()));
		m_fgfs_port_edit->setValidator(new QIntValidator(
					std::numeric_limits<unsigned short>::min(),
					std::numeric_limits<unsigned short>::max(),
					this));
		connect(m_fgfs_port_edit, SIGNAL(textEdited(const QString&)),
				this, SLOT(handle_fgfs_port_change(const QString&)));

		m_systray_checkbox = new QCheckBox(this);
		m_systray_checkbox->setChecked(model.get_systray_enabled());
#if FGCOM_GUI_PLATFORM == FGCOM_GUI_PLATFORM_LINUX
		m_systray_checkbox->setText("Run in the system tray");
#elif FGCOM_GUI_PLATFORM == FGCOM_GUI_PLATFORM_MSWIN
		m_systray_checkbox->setText("Run in the notification area");
#endif
		connect(m_systray_checkbox, SIGNAL(toggled(bool)),
				&model, SLOT(set_systray_enabled(bool)));
		connect(&model, SIGNAL(systray_enabled_changed(bool)),
				m_systray_checkbox, SLOT(setChecked(bool)));
		
		//--fgcomgui group
	
		QGroupBox* fgcomgui_box = new QGroupBox(this);
		fgcomgui_box->setTitle("FGComGui");

		QVBoxLayout* fgcomgui_layout = new QVBoxLayout;
		fgcomgui_layout->addWidget(m_systray_checkbox);
		fgcomgui_box->setLayout(fgcomgui_layout);

		//-- fgcom_group

		QGroupBox* fgcom_box = new QGroupBox(this);
		fgcom_box->setTitle("FGCom");

		QLabel* path_label = new QLabel(this);
		path_label->setText("Binary");

		QLabel* server_label = new QLabel(this);
		server_label->setText("Server");

		QVBoxLayout* label_layout = new QVBoxLayout;
		label_layout->addWidget(path_label);
		label_layout->addWidget(server_label);

		QHBoxLayout* path_layout = new QHBoxLayout;
		path_layout->addWidget(m_fgcom_path_edit);
		path_layout->addWidget(m_fgcom_path_button);

		QVBoxLayout* edit_layout = new QVBoxLayout;
		edit_layout->addLayout(path_layout);
		edit_layout->addWidget(m_fgcom_server_edit);

		QHBoxLayout* config_layout = new QHBoxLayout;
		config_layout->addLayout(label_layout);
		config_layout->addLayout(edit_layout);

		QVBoxLayout* fgcom_layout = new QVBoxLayout;
		fgcom_layout->addWidget(new CommonConfigView(this));
		fgcom_layout->addLayout(config_layout);
		fgcom_box->setLayout(fgcom_layout);

		//--flightgear group

		QGroupBox* fgfs_box = new QGroupBox(this);
		fgfs_box->setTitle("FlightGear");

		QLabel* port_label = new QLabel(this);
		port_label->setText("Port");

		QHBoxLayout* fgfs_layout = new QHBoxLayout;
		fgfs_layout->addWidget(port_label);
		fgfs_layout->addWidget(m_fgfs_port_edit);
		fgfs_box->setLayout(fgfs_layout);

		//

		QVBoxLayout* main_layout = new QVBoxLayout;
		main_layout->addWidget(fgcomgui_box);
		main_layout->addWidget(fgcom_box);
		main_layout->addWidget(fgfs_box);
		setLayout(main_layout);
		
		//
		connect(this, SIGNAL(fgcom_path_changed(const QString&)),
				&model, SLOT(set_fgcom_path(const QString&)));
		connect(this, SIGNAL(fgcom_server_changed(const QString&)),
				&model, SLOT(set_fgcom_server(const QString&)));
		connect(this, SIGNAL(fgfs_port_changed(unsigned short)),
				&model, SLOT(set_fgfs_port(unsigned short)));

		connect(&model, SIGNAL(fgcom_path_changed(const QString&)),
				this, SLOT(set_fgcom_path(const QString&)));
		connect(&model, SIGNAL(fgcom_server_changed(const QString&)),
				this, SLOT(set_fgcom_server(const QString&)));
		connect(&model, SIGNAL(fgfs_port_changed(unsigned short)),
				this, SLOT(set_fgfs_port(unsigned short)));
	}

	ConfigView::~ConfigView()
	{
	}

	void ConfigView::handle_fgcom_path_change(const QString& path)
	{
		emit fgcom_path_changed(path);
	}

	void ConfigView::handle_fgcom_path_browse()
	{
		QString path = QFileDialog::getOpenFileName(this, "Select FGCom executable - FGComGui",
#if FGCOM_GUI_PLATFORM == FGCOM_GUI_PLATFORM_LINUX
			QDir::homePath(), ""
#elif FGCOM_GUI_PLATFORM == FGCOM_GUI_PLATFORM_MSWIN
			QDir::currentPath(), "Executable (*.exe)"
#endif
		);
		
		if (path.isEmpty())
			return;

		m_fgcom_path_edit->setText(path);
		emit fgcom_path_changed(path);
	}

	void ConfigView::handle_fgcom_server_change(const QString& url)
	{
		emit fgcom_server_changed(url);
	}

	void ConfigView::handle_fgfs_port_change(const QString& port)
	{
		emit fgfs_port_changed(
				static_cast<unsigned short>(port.toUInt()) );
	}

	void ConfigView::set_fgcom_path(const QString& path)
	{
		m_fgcom_path_edit->setText(path);
	}

	void ConfigView::set_fgcom_server(const QString& url)
	{
		m_fgcom_server_edit->setText(url);
	}

	void ConfigView::set_fgfs_port(unsigned short port)
	{
		m_fgfs_port_edit->setText(QString::number(port));
	}

} // namespace FGComGui

#include "configview.hpp.moc"

