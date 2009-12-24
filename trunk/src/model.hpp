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
#ifndef __fgcomgui_model_hpp__
#define __fgcomgui_model_hpp__

#include "fgcomgui.hpp"
#include <QObject>
#include <QString>

class QSettings;


namespace FGComGui {

	class Model
		: public QObject
	{
		Q_OBJECT

		public:
			Model();
			~Model();

			RunMode get_fgcom_mode() const;
			QString get_fgcom_path() const;
			float get_fgcom_output_volume() const;
			float get_fgcom_input_volume() const;
			QString get_fgcom_server() const;
			unsigned short get_fgfs_port() const;
			bool get_systray_enabled() const;
			static Model& get_instance();

		signals:
			void fgcom_mode_changed(RunMode mode);
			void fgcom_path_changed(const QString& path);
			void fgcom_server_changed(const QString& url);
			void fgcom_input_volume_changed(float v);
			void fgcom_output_volume_changed(float v);
			void fgfs_port_changed(unsigned short port);
			void systray_enabled_changed(bool enabled);
			
		public slots:
			void set_fgcom_mode(RunMode mode);
			void set_fgcom_path(const QString& path);
			void set_fgcom_server(const QString& url);
			void set_fgcom_output_volume(float v);
			void set_fgcom_input_volume(float v);
			void set_fgfs_port(unsigned short port);
			void set_systray_enabled(bool enabled);

		private:
			void change_setting(const QString& name, const QVariant& value);

			static Model* sm_instance;
			QSettings* m_settings;
	};

} // namespace FGComGui
#endif // __fgcomgui_model_hpp__

