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
#ifndef __fgcomgui_commonconfigview_hpp__
#define __fgcomgui_commonconfigview_hpp__

#include "fgcomgui.hpp"
#include <QWidget>

class QPushButton;
class QSlider;
class QLineEdit;
class QComboBox;


namespace FGComGui {

	class CommonConfigView
		: public QWidget
	{
		Q_OBJECT

		public:
			CommonConfigView(QWidget* parent);
			~CommonConfigView();

		signals:
			void fgcom_mode_changed(RunMode mode);
			void fgcom_input_volume_changed(float value);
			void fgcom_output_volume_changed(float value);
			
		public slots:
			void set_fgcom_mode(RunMode mode);
			void set_fgcom_input_volume(float volume);
			void set_fgcom_output_volume(float volume);

		private slots:
			void handle_fgcom_mode_change(int index);
			void handle_fgcom_input_volume_change(int volume);
			void handle_fgcom_output_volume_change(int volume);		

		private:
			QComboBox* m_mode_combo;
			QSlider* m_input_volume_slider;
			QSlider* m_output_volume_slider;
	};

} // namespace FGComGui
#endif // __fgcomgui_commonconfigview_hpp__

