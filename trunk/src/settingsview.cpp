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
#include "settingsview.hpp"

#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>


namespace FGComGui {

	SettingsView::SettingsView(QWidget* parent)
		: QWidget(parent)
		, m_mode_combo(new QComboBox(this))
		, m_path_edit(new QLineEdit(this))
		, m_path_button(new QPushButton(this))
		, m_input_volume_slider(new QSlider(Qt::Horizontal, this))
		, m_output_volume_slider(new QSlider(Qt::Horizontal, this))
	{
		QHBoxLayout* path_layout = new QHBoxLayout;
		QLabel* path_label = new QLabel(this);
		path_label->setText("FGCom:");
		path_layout->addWidget(path_label, 0);
		path_layout->addWidget(m_path_edit, 5);
		path_layout->addWidget(m_path_button, 0);		

		QHBoxLayout* volume_layout = new QHBoxLayout;
		QVBoxLayout* volume_vbox = new QVBoxLayout;
		QLabel* input_label = new QLabel(this);
		QLabel* output_label = new QLabel(this);
		input_label->setText("Input Volume");
		output_label->setText("Output Volume");
		volume_vbox->addWidget(input_label);
		volume_vbox->addWidget(output_label);
		volume_layout->addLayout(volume_vbox);
		volume_vbox = new QVBoxLayout;
		volume_vbox->addWidget(m_input_volume_slider);
		volume_vbox->addWidget(m_output_volume_slider);
		volume_layout->addLayout(volume_vbox);
		
		QVBoxLayout* main_layout = new QVBoxLayout;
		main_layout->addWidget(m_mode_combo);
		main_layout->addLayout(path_layout);
		main_layout->addLayout(volume_layout);
		setLayout(main_layout);

		m_mode_combo->addItem("FGCom Normal Mode");
		m_mode_combo->addItem("FGCom Echo Test Mode");
		m_mode_combo->setToolTip(
				"Select fgcom run mode.\n\n"
				"Normal Mode - Normal mode used with flightgear.\n"
				"Echo Test Mode - Connect to echo frequency for testing.\n");
		m_path_edit->setToolTip("Name or full path to the fgcom executable.");
		m_path_button->setText("...");
		m_path_button->setToolTip("open file browser");
		m_output_volume_slider->setTickPosition(QSlider::TicksBelow);
		m_output_volume_slider->setToolTip("Adjust output(playback) volume.");
		m_input_volume_slider->setTickPosition(QSlider::TicksBelow);
		m_input_volume_slider->setToolTip("Adjust input(recording) volume.");

		connect(m_mode_combo, SIGNAL(activated(int)), this, SLOT(handle_mode_change(int)));
		connect(m_path_edit, SIGNAL(textChanged(const QString&)), this, SLOT(handle_path_change(const QString&)));
		connect(m_path_button, SIGNAL(clicked()), this, SLOT(handle_path_browser()));
		connect(m_output_volume_slider, SIGNAL(valueChanged(int)), this, SLOT(handle_output_volume_change(int)));
		connect(m_input_volume_slider, SIGNAL(valueChanged(int)), this, SLOT(handle_input_volume_change(int)));

		setTabOrder(m_mode_combo, m_path_edit);
		setTabOrder(m_path_edit, m_path_button);
		setTabOrder(m_path_button, m_input_volume_slider);
		setTabOrder(m_input_volume_slider, m_output_volume_slider);
	}	

	SettingsView::~SettingsView()
	{
	}

	void SettingsView::set_mode(RunMode mode)
	{
		switch (mode) {
			case RM_NORMAL:
				m_mode_combo->setCurrentIndex(0);
				break;
			case RM_TEST:
				m_mode_combo->setCurrentIndex(1);
				break;
			default:
				break;
		}
	}

	void SettingsView::set_path(const QString& path)
	{
		m_path_edit->setText(path);
	}

	void SettingsView::set_input_volume(float volume)
	{
		int v = static_cast<int>(100 * volume);
		m_input_volume_slider->setValue(v);
	}

	void SettingsView::set_output_volume(float volume)
	{
		int v = static_cast<int>(100 * volume);
		m_output_volume_slider->setValue(v);
	}

	void SettingsView::handle_mode_change(int index)
	{
		switch (index) {
			case 0:
				emit mode_changed(RM_NORMAL);
				break;
			case 1:
				emit mode_changed(RM_TEST);
				break;
			default:
				break;
		}
	}

	void SettingsView::handle_path_change(const QString& path)
	{
		emit path_changed(path);
	}

	void SettingsView::handle_input_volume_change(int volume)
	{
		emit input_volume_changed( static_cast<float>(volume) / 100.0 );
	}

	void SettingsView::handle_output_volume_change(int volume)
	{
		emit output_volume_changed( static_cast<float>(volume) / 100.0 );
	}

	void SettingsView::handle_path_browser()
	{
		QString filename = QFileDialog::getOpenFileName(this, "Select fgcom executable",
#if FGCOM_GUI_PLATFORM == FGCOM_GUI_PLATFORM_LINUX
				QDir::homePath(), ""
#elif FGCOM_GUI_PLATFORM == FGCOM_GUI_PLATFORM_MSWIN
				QDir::currentPath(), "Executable (*.exe)"
#endif
				);
		if (filename.isEmpty())
			return;

		set_path(filename);
	}

} // namespace FGComGui

#include "settingsview.hpp.moc"

