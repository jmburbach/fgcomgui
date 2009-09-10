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
#ifndef __fgcomgui_aboutdialog_hpp__
#define __fgcomgui_aboutdialog_hpp__

#include "fgcomgui.hpp"
#include <QDialog>

namespace FGComGui {

	class AboutDialog
		: public QDialog
	{
		Q_OBJECT

		public:
			AboutDialog(QWidget* parent = 0);
			~AboutDialog();

		private slots:
			void handle_link_activated(const QString&);

		private:
			void setup_title_widget();
			void setup_about_page();
			void setup_authors_page();

			QWidget* m_title_widget;
			QWidget* m_about_page;
			QWidget* m_authors_page;
			LicenseDialog* m_license_dialog;
	};

} // namespace FGComGui
#endif // __fgcomgui_aboutdialog_hpp__

