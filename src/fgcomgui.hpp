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
#ifndef __fgcomgui_hpp__
#define __fgcomgui_hpp__

namespace FGComGui {

#define FGCOM_GUI_PLATFORM_LINUX 0
#define FGCOM_GUI_PLATFORM_MSWIN 1

#if defined(LINUX)
#define FGCOM_GUI_PLATFORM FGCOM_GUI_PLATFORM_LINUX
#elif defined(WINDOWS)
#define FGCOM_GUI_PLATFORM FGCOM_GUI_PLATFORM_MSWIN
#else
#error "unsupported platform!"
#endif

	enum RunMode {
		RM_NORMAL = 0,
		RM_TEST = 1
	};

	class SettingsView;
	class SettingsModel;

} // namespace FGComGui
#endif // __fgcomgui_hpp__

