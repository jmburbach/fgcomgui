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
#include "commonconfigview.hpp"
#include "model.hpp"

#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFileDialog>


namespace FGComGui {

	CommonConfigView::CommonConfigView(QWidget* parent)
		: QWidget(parent)
		, m_mode_combo(new QComboBox(this))
		, m_input_volume_slider(new QSlider(Qt::Horizontal, this))
		, m_output_volume_slider(new QSlider(Qt::Horizontal, this))
	{

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
		main_layout->addLayout(volume_layout);
		setLayout(main_layout);

		m_mode_combo->addItem("FGCom Normal Mode");
		m_mode_combo->addItem("FGCom Echo Test Mode");
		m_mode_combo->setToolTip(
				"Select fgcom run mode.\n\n"
				"Normal Mode - Normal mode used with flightgear.\n"
				"Echo Test Mode - Connect to echo frequency for testing.\n");
		m_output_volume_slider->setTickPosition(QSlider::TicksBelow);
		m_output_volume_slider->setToolTip("Adjust output(playback) volume.");
		m_input_volume_slider->setTickPosition(QSlider::TicksBelow);
		m_input_volume_slider->setToolTip("Adjust input(recording) volume.");

		// wire widget signals to our handler slots
		connect(m_mode_combo, SIGNAL(activated(int)),
			   	this, SLOT(handle_fgcom_mode_change(int)));
		connect(m_output_volume_slider, SIGNAL(valueChanged(int)),
			   	this, SLOT(handle_fgcom_output_volume_change(int)));
		connect(m_input_volume_slider, SIGNAL(valueChanged(int)),
			   	this, SLOT(handle_fgcom_input_volume_change(int)));

		setTabOrder(m_input_volume_slider, m_output_volume_slider);

		// get settings from model
		Model& m = Model::get_instance();
		set_fgcom_mode(m.get_fgcom_mode());
		set_fgcom_input_volume(m.get_fgcom_input_volume());
		set_fgcom_output_volume(m.get_fgcom_output_volume());

		// wire up Model signals to us
		connect(&m, SIGNAL(fgcom_mode_changed(RunMode)),
				this, SLOT(set_fgcom_mode(RunMode)));
		connect(&m, SIGNAL(fgcom_input_volume_changed(float)),
				this, SLOT(set_fgcom_input_volume(float)));
		connect(&m, SIGNAL(fgcom_output_volume_changed(float)),
				this, SLOT(set_fgcom_output_volume(float)));

		// wire up ourself to Model
		connect(this, SIGNAL(fgcom_mode_changed(RunMode)),
				&m, SLOT(set_fgcom_mode(RunMode)));
		connect(this, SIGNAL(fgcom_input_volume_changed(float)),
				&m, SLOT(set_fgcom_input_volume(float)));
		connect(this, SIGNAL(fgcom_output_volume_changed(float)),
				&m, SLOT(set_fgcom_output_volume(float)));
	}

	CommonConfigView::~CommonConfigView()
	{
	}

	void CommonConfigView::set_fgcom_mode(RunMode mode)
	{
		switch (mode) {
			case RM_NORMAL:
				m_mode_combo->setCurrentIndex(0);
				break;
			case RM_TEST:
				m_mode_combo->setCurrentIndex(1);
				break;
		}
	}

	void CommonConfigView::set_fgcom_input_volume(float volume)
	{
		int v = static_cast<int>(100 * volume);
		m_input_volume_slider->setValue(v);
	}

	void CommonConfigView::set_fgcom_output_volume(float volume)
	{
		int v = static_cast<int>(100 * volume);
		m_output_volume_slider->setValue(v);
	}

	void CommonConfigView::handle_fgcom_mode_change(int index)
	{
		RunMode mode = static_cast<RunMode>(index);
		emit fgcom_mode_changed(mode);
	}

	void CommonConfigView::handle_fgcom_input_volume_change(int volume)
	{
		emit fgcom_input_volume_changed( static_cast<float>(volume) / 100.0 );
	}

	void CommonConfigView::handle_fgcom_output_volume_change(int volume)
	{
		emit fgcom_output_volume_changed( static_cast<float>(volume) / 100.0 );
	}

} // namespace FGComGui

#include "commonconfigview.hpp.moc"

