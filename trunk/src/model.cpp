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
#include "model.hpp"

#include <QSettings>
#include <QVariant>

#include <cassert>


namespace FGComGui {

	Model* Model::sm_instance = 0;

	Model::Model()
		: QObject()
		, m_settings(0)
	{
		assert(sm_instance == 0);
		sm_instance = this;

		m_settings = new QSettings(this);
	}

	Model::~Model()
	{
		assert(sm_instance != 0);
		sm_instance = 0;
	}

	Model& Model::get_instance()
	{
		assert(sm_instance != 0);
		return *sm_instance;
	}

	RunMode Model::get_fgcom_mode() const
	{
		return static_cast<RunMode>(m_settings->value("fgcom_mode", 0).toInt());
	}
	
	QString Model::get_fgcom_path() const
	{
#if FGCOM_GUI_PLATFORM == FGCOM_GUI_PLATFORM_MSWIN
		// would work fine without .exe, but users may be more comfortable with it
		QString default_path("fgcom.exe");
#else
		QString default_path("fgcom");
#endif

		return m_settings->value("fgcom_path", default_path).toString();
	}

	QString Model::get_fgcom_server() const
	{
		return m_settings->value("fgcom_server", "fgcom.flightgear.org.uk").toString();
	}

	float Model::get_fgcom_input_volume() const
	{
		return static_cast<float>(
				m_settings->value("fgcom_input_volume", 0.75).toDouble() );
	}

	float Model::get_fgcom_output_volume() const
	{
		return static_cast<float>(
				m_settings->value("fgcom_output_volume", 0.75).toDouble() );
	}

	unsigned short Model::get_fgfs_port() const
	{
		return static_cast<unsigned short>(
			   	m_settings->value("fgfs_port", 16661).toUInt() );
	}

	bool Model::get_systray_enabled() const
	{
		return m_settings->value("systray_enabled", true).toBool();
	}

	void Model::set_fgcom_mode(RunMode new_mode)
	{
		if (get_fgcom_mode() == new_mode)
			return;

		change_setting("fgcom_mode", static_cast<int>(new_mode));
		emit fgcom_mode_changed(new_mode);
	}

	void Model::set_fgcom_path(const QString& new_path)
	{
		if (get_fgcom_path() == new_path)
			return;

		change_setting("fgcom_path", new_path);
		emit fgcom_path_changed(new_path);
	}

	void Model::set_fgcom_input_volume(float new_volume)
	{
		if (get_fgcom_input_volume() == new_volume)
			return;

		change_setting("fgcom_input_volume", new_volume);
		emit fgcom_input_volume_changed(new_volume);
	}

	void Model::set_fgcom_output_volume(float new_volume)
	{
		if (get_fgcom_output_volume() == new_volume)
			return;

		change_setting("fgcom_output_volume", new_volume);
		emit fgcom_output_volume_changed(new_volume);
	}

	void Model::set_fgcom_server(const QString& new_server)
	{
		if (get_fgcom_server() == new_server)
			return;

		change_setting("fgcom_server", new_server);
		emit fgcom_server_changed(new_server);
	}

	void Model::set_fgfs_port(unsigned short new_port)
	{
		if (get_fgfs_port() == new_port)
			return;

		change_setting("fgfs_port", new_port);
		emit fgfs_port_changed(new_port);
	}

	void Model::set_systray_enabled(bool b)
	{
		if (get_systray_enabled() == b)
			return;

		change_setting("systray_enabled", b);
		emit systray_enabled_changed(b);
	}

	void Model::change_setting(const QString& name, const QVariant& value)
	{
		m_settings->setValue(name, value);
		m_settings->sync();
	}

} // namespace FGComGui

#include "model.hpp.moc"

