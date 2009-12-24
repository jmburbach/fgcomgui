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
#ifndef __fgcomgui_configview_hpp__
#define __fgcomgui_configview_hpp__

#include "fgcomgui.hpp"
#include <QWidget>

class QLineEdit;
class QPushButton;
class QCheckBox;


namespace FGComGui {

	class ConfigView
		: public QWidget
	{
		Q_OBJECT
		public:
			ConfigView(QWidget* parent = 0);
			~ConfigView();

		signals:
			void fgcom_path_changed(const QString& path);
			void fgcom_server_changed(const QString& url);
			void fgfs_port_changed(unsigned short port);

		public slots:
			void set_fgcom_path(const QString& path);
			void set_fgcom_server(const QString& url);
			void set_fgfs_port(unsigned short port);

		private slots:
			void handle_fgcom_path_change(const QString& path);
			void handle_fgcom_server_change(const QString& path);
			void handle_fgcom_path_browse();
			void handle_fgfs_port_change(const QString& port);

		private:
			QLineEdit* m_fgcom_path_edit;
			QPushButton* m_fgcom_path_button;
			QLineEdit* m_fgcom_server_edit;
			QLineEdit* m_fgfs_port_edit;
			QCheckBox* m_systray_checkbox;
	};

} // namespace FGComGui
#endif // __fgcomgui_configview_hpp__

