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
#ifndef __fgcom_settingsmodel_hpp__
#define __fgcom_settingsmodel_hpp__

#include "fgcomgui.hpp"
#include <QString>

namespace FGComGui {

	class SettingsModel
	{
		public:
			SettingsModel();
			~SettingsModel();
			RunMode get_mode() const;
			void set_mode(RunMode mode);
			const QString& get_path() const;
			void set_path(const QString& path);
			float get_output_volume() const;
			void set_output_volume(float v);
			float get_input_volume() const;
			void set_input_volume(float v);

		private:
			RunMode m_mode;
			QString m_path;
			float m_input_volume;
			float m_output_volume;
	};

} // namespace FGComGui
#endif // __fgcom_settingsmodel_hpp__

