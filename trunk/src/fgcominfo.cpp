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
#include "fgcominfo.hpp"
#include "model.hpp"
#include <iostream>


namespace FGComGui {

	FGComInfo::FGComInfo()
	{
		reset();
		m_frequency_rx.setPattern("Selected frequency: (\\d*.\\d+)\n");
		m_call_0_rx.setPattern("Call 0 (accepted|answered|timed out)\n");
		m_hangup_rx.setPattern("Hanging up call 0\n");
		m_rejected_rx.setPattern("Call rejected by remote\n");
		m_station_info_rx.setPattern(
				"Airport (.*) \\((.*) (.*) at (\\d*.\\d+) MHz\\) is in range \\(\\s*(\\d*.\\d+) km\\)\n");
	}

	FGComInfo::~FGComInfo()
	{
	}

	void FGComInfo::interpret_fgcom_output(const QString& line)
	{
		if (m_frequency_rx.exactMatch(line)) {
			reset();
			m_station_frequency = m_frequency_rx.cap(1);
		}
		else if (m_call_0_rx.exactMatch(line)) {
			QString what = m_call_0_rx.cap(1);
			if (what == "accepted" || what == "answered") {
				m_station_connected = true;
			}
			else {
				m_station_connected = false;
			}
		}
		else if (m_hangup_rx.exactMatch(line) || m_rejected_rx.exactMatch(line)) {
			m_station_connected = false;
		}
		else if (m_station_info_rx.exactMatch(line)) {
			m_station_connected = true;
			m_station_name = m_station_info_rx.cap(1);			
			m_station_icao = m_station_info_rx.cap(2);
			m_station_type = m_station_info_rx.cap(3);
			m_station_frequency = m_station_info_rx.cap(4);
			m_station_distance = m_station_info_rx.cap(5);
		}
	}
	
	void FGComInfo::reset()
	{
		m_station_connected = false;
		m_station_name = "";
		m_station_icao = "";
		m_station_type = "";
		m_station_frequency = "";
		m_station_distance = "";
	}

} // namespace FGComGui

