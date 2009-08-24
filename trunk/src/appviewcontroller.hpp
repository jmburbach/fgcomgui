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
#ifndef __fgcom_appviewcontroller_hpp__
#define __fgcom_appviewcontroller_hpp__

#include "fgcomgui.hpp"

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QProcess>

class QPushButton;
class QTextEdit;


namespace FGComGui {

	class AppViewController
		: public QMainWindow
	{
		Q_OBJECT

		public:
			AppViewController();
			~AppViewController();

		private slots:
			void handle_mode_change(RunMode mode);
			void handle_path_change(const QString& path);
			void handle_input_volume_change(float v);
			void handle_output_volume_change(float v);
			void handle_system_tray_activation(QSystemTrayIcon::ActivationReason reason);
			void handle_start_request();
			void handle_stop_request();
			void handle_process_state_change(QProcess::ProcessState state);
			void handle_process_output();
			void handle_process_finished(int code, QProcess::ExitStatus status);
			void handle_process_error(QProcess::ProcessError error);

		private:			
			void closeEvent(QCloseEvent* event);

			SettingsModel* m_model;
			SettingsView* m_settings_view;
			QPushButton* m_start_button;
			QPushButton* m_stop_button;
			QTextEdit* m_process_output;
			QSystemTrayIcon* m_systray;
			QProcess* m_process;
			QPoint m_savedPos;
	};

} // namespace FGComGui
#endif // __fgcom_appviewcontroller_hpp__

