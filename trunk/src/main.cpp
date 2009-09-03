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
#include "model.hpp"

#include <QApplication>


int main(int argc, char** argv)
{
	QCoreApplication::setApplicationName("FGComGui");
	QCoreApplication::setOrganizationName("JBurbach");

	QApplication app(argc, argv);
	app.setQuitOnLastWindowClosed(false);

	FGComGui::Model model;
	FGComGui::AppViewController view;	
	view.show();

	return app.exec();
}

