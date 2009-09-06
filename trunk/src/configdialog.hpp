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
#ifndef ____fgcomgui_configdialog_hpp____
#define ____fgcomgui_configdialog_hpp____

#include "fgcomgui.hpp"
#include <QDialog>

namespace FGComGui {

	class ConfigDialog
		: public QDialog
	{
		public:
			ConfigDialog(QWidget* parent);
			~ConfigDialog();
	};

} // namespace FGComGui
#endif // ____fgcomgui_configdialog_hpp____
