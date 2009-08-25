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
#ifndef __fgcomgui_settingsview_hpp__
#define __fgcomgui_settingsview_hpp__

#include "fgcomgui.hpp"
#include <QWidget>

class QPushButton;
class QSlider;
class QLineEdit;
class QComboBox;


namespace FGComGui {

	class SettingsView
		: public QWidget
	{
		Q_OBJECT

		public:
			SettingsView(QWidget* parent);
			~SettingsView();

			void set_mode(RunMode mode);
			void set_path(const QString& path);
			void set_input_volume(float volume);
			void set_output_volume(float volume);

		signals:
			void mode_changed(RunMode mode);
			void path_changed(const QString& path);
			void input_volume_changed(float value);
			void output_volume_changed(float value);

		private slots:
			void handle_mode_change(int index);
			void handle_path_change(const QString& text);
			void handle_input_volume_change(int volume);
			void handle_output_volume_change(int volume);		
			void handle_path_browser();

		private:
			QComboBox* m_mode_combo;
			QLineEdit* m_path_edit;
			QPushButton* m_path_button;
			QSlider* m_input_volume_slider;
			QSlider* m_output_volume_slider;
	};

} // namespace FGComGui
#endif // __fgcomgui_settingsview_hpp__

