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

#pragma once
#include "WString.h"

class CState {
public:
    static const int state_rows = 16;
    String m_state[state_rows][2] = {
      { "timestamp", "n/a" },
      { "cityName", "n/a" }, 
      { "cityDescription", "n/a" },
      { "mayorName", "n/a" },
      
      { "lowWealthPopulation", "n/a" },
      { "medWealthPopulation", "n/a" },
      { "highWealthPopulation", "n/a" },
      
      { "ytdIncome", "n/a" },
      { "ytdExpenses", "n/a" },
      
      { "estIncome", "n/a" },
      { "estExpenses", "n/a" },
      
      { "totalMonthlyExpense", "n/a" },
      { "totalYearlyExpense", "n/a" },
      { "totalMonthlyIncome", "n/a" },
      { "totalYearlyIncome", "n/a" },

      { "pauseAtEndOfMonth", "0" },
    };
    
    /*! \brief Returns a JSON string of the internal state
    *
    * - for only non-nested, string only key/value pairs
    * 
    */
    String serializeToJson();
    
    /*! \brief Update internal State from JSON String
    *
    * - Overwrite internal state with values from JSON string
    * - Simplified more efficient JSON parsing
    * - allows only non-nested, string only key/value pairs and expects keys to have previously existed
    * - assumes no curly braces inside of values
    */
    void updateFromJson(String data);
    
    String getEntry(String key);
    void setEntry(String key, String value);   
};
