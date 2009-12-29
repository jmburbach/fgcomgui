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
#ifndef __fgcominfo_hpp__
#define __fgcominfo_hpp__

#include <QRegExp>

namespace FGComGui {

	class FGComInfo
	{
		public:
			FGComInfo();
			~FGComInfo();

			void interpret_fgcom_output(const QString& line);
			void reset();
			bool get_station_connected() const { return m_station_connected; }
			const QString& get_station_name() const { return m_station_name; }
			const QString& get_station_icao() const { return m_station_icao; }
			const QString& get_station_type() const { return m_station_type; }
			const QString& get_station_frequency() const { return m_station_frequency; }
			const QString& get_station_distance() const { return m_station_distance; }

		private:
			bool m_station_connected;
			QString m_station_name;
			QString m_station_icao;
			QString m_station_type;
			QString m_station_frequency;
			QString m_station_distance;
			QRegExp m_frequency_rx;
			QRegExp m_call_0_rx;
			QRegExp m_hangup_rx;
			QRegExp m_rejected_rx;
			QRegExp m_station_info_rx;
	};

} // namespace FGComGui
#endif // __fgcominfo_hpp__

