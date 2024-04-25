/*
Sim City 4 Web Interface Plug-In
Copyright (C) 2024 D.Salzner <mail@dennissalzner.de>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * Basic JSON serializable Key/Value-Store
 *
 * Useful to:
 * - keep all state in one central place
 * - easy store/load of state and transfer to websockets
 *
 * Usage:
 * - pre-configure available keys and default values in m_state
 * - getEntry/setEntry to get and set entries
 * - updateFromJson to load values from JSON
 * - serializeToJson to get JSON of current state
 *
 * Caution:
 * - does not handle nested JSON
 * - ignores keys that have not been previously configured in m_state
 * - will break curly braces in values
*/

#include "CState.h"
#include "common.h"

String CState::serializeToJson() {
  setEntry("timestamp", getTimestamp());

  String jsonBuffer = "{\n";
  for(int i = 0; i < state_rows; i++) {
    jsonBuffer += "\"" + m_state[i][0] + "\": ";
    jsonBuffer += "\"" +  m_state[i][1] + "\",\n";
  }
  jsonBuffer += "}";
  return jsonBuffer;
}

void CState::updateFromJson(String data) {
  data.replace(" ", "");
  data.replace("{", "");
  data.replace("}", "");
  data.replace("\"", "");
  
  String key = "";
  unsigned int i = 0;
  for(; i < data.length(); i++) { // read key
    if(data.substring(i, i+1) == ":") break;
    key += data.charAt(i);
  }
  i++; // skip ":"
  String value = "";
  for(; i < data.length(); i++) { // read value
    value += data.charAt(i);
  }
  
  setEntry(key, value);
}

String CState::getEntry(String key) {
  for(unsigned int i = 0; i < state_rows; i++) {
      if(m_state[i][0] == key) {
          return m_state[i][1];
      }
  }
  return "";
}

void CState::setEntry(String key, String value) {
 for(unsigned int i = 0; i < state_rows; i++) {
      if(m_state[i][0] == key) {
          m_state[i][1] = value;
          return;
      }
  }
}
