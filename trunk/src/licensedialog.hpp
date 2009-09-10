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
#ifndef __fgcomgui_licensedialog_hpp__
#define __fgcomgui_licensedialog_hpp__

#include "fgcomgui.hpp"
#include <QDialog>

namespace FGComGui {

	class LicenseDialog
		: public QDialog
	{
		Q_OBJECT
		public:
			LicenseDialog(QWidget* parent = 0);
	};

} // namespace FGComGui
#endif // __fgcomgui_licensedialog_hpp__

