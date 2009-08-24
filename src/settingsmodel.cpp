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
#include "settingsmodel.hpp"
#include <QSettings>


namespace FGComGui {

	SettingsModel::SettingsModel()
	{
		QSettings settings("JBurbach", "FGComGui");
		m_mode = static_cast<RunMode>(settings.value("mode", 0).toInt());
#if FGCOM_GUI_PLATFORM == FGCOM_GUI_PLATFORM_LINUX
		m_path = settings.value("path", "fgcom").toString();
#elif FGCOM_GUI_PLATFORM == FGCOM_GUI_PLATFORM_MSWIN
		m_path = settings.value("path", "fgcom.exe").toString();
#endif
		m_input_volume = settings.value("input_volume", 0.75).toDouble();
		m_output_volume = settings.value("output_volume", 0.75).toDouble();
	}

	SettingsModel::~SettingsModel()
	{
	}

	RunMode SettingsModel::get_mode() const
	{
		return m_mode;
	}

	void SettingsModel::set_mode(RunMode mode)
	{
		m_mode = mode;

		QSettings settings("JBurbach", "FGComGui");
		settings.setValue("mode", static_cast<int>(mode));
		settings.sync();
	}

	const QString& SettingsModel::get_path() const
	{
		return m_path;
	}

	void SettingsModel::set_path(const QString& path)
	{
		m_path = path;
		
		QSettings settings("JBurbach", "FGComGui");
		settings.setValue("path", path);
		settings.sync();
	}

	float SettingsModel::get_input_volume() const
	{
		return m_input_volume;
	}

	void SettingsModel::set_input_volume(float v)
	{
		m_input_volume = v;
		
		QSettings settings("JBurbach", "FGComGui");
		settings.setValue("input_volume", v);
		settings.sync();
	}

	float SettingsModel::get_output_volume() const
	{
		return m_output_volume;
	}

	void SettingsModel::set_output_volume(float v)
	{
		m_output_volume = v;
		
		QSettings settings("JBurbach", "FGComGui");
		settings.setValue("output_volume", v);
		settings.sync();
	}

} // namespace FGComGui

