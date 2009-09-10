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
#ifndef __fgcomgui_appviewcontroller_hpp__
#define __fgcomgui_appviewcontroller_hpp__

#include "fgcomgui.hpp"

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QProcess>

class QPushButton;
class QTextEdit;
class QAction;
class QMenu;


namespace FGComGui {

	class AppViewController
		: public QMainWindow
	{
		Q_OBJECT

		public:
			AppViewController();
			~AppViewController();

		private slots:
			void handle_system_tray_activation(QSystemTrayIcon::ActivationReason reason);
			void handle_start_request();
			void handle_stop_request();
			void handle_process_state_change(QProcess::ProcessState state);
			void handle_process_output();
			void handle_process_finished(int code, QProcess::ExitStatus status);
			void handle_process_error(QProcess::ProcessError error);
			void handle_show_hide_request();
			void handle_quit_request();
			void handle_configure_request();
			void handle_about_fgcomgui();
			void handle_html_docs();

		private:
			void setup_actions();
			void setup_menus();
			void setup_systray();
			void setup_process();
			
			void closeEvent(QCloseEvent* event);
			void changeEvent(QEvent* event); 

			CommonConfigView* m_settings_view;
			QPushButton* m_start_button;
			QPushButton* m_stop_button;
			QTextEdit* m_process_output;
			QSystemTrayIcon* m_systray;
			QProcess* m_process;
			QPoint m_savedPos;

			QMenu* m_file_menu;
			QMenu* m_systray_menu;
			QMenu* m_settings_menu;

			QAction* m_quit_action;
			QAction* m_start_action;
			QAction* m_stop_action;
			QAction* m_show_hide_action;
			QAction* m_configure_action;

			AboutDialog* m_about_dialog;
	};

} // namespace FGComGui
#endif // __fgcomgui_appviewcontroller_hpp__

