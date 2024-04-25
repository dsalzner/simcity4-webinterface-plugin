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
 * SimCity 4 Web-Interface Plug-In - Standalone Web-Server 
 * 
 * for testing. It will responds with the default values.
 *
 * - compiles on Linux
 * - uses libmicrohttpd for webserver
 * - basic JSON serializable Key-Value-Store
 * - code for string handling taken from Arduino with compatibility header
 *
*/

#include <iostream>
#include "common.h"
#include "CState.h"
#include "CServer.h"

int main() {
  std::shared_ptr<CState> state = std::make_shared<CState>();
  CServer server(state);
  server.state()->setEntry("cityName", "Dummy City");
  server.state()->setEntry("cityDescription", "Fake City State information from the Dummy-Server");
  
  (void)getc(stdin);

  return 0;
}
