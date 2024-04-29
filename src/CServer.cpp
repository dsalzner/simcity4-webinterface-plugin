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
 * SimCity 4 Web-Interface Plug-In - CServer
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "common.h"
#include "microhttpd.h"
#include "CState.h"
#include "CServer.h"

CServer::CServer(std::shared_ptr<CState> state) { 
  logMessage("[ ] Server Init on http://127.0.0.1:" + String(std::to_string(m_port).c_str())  + "/");
  data_for_handler.m_state = state;

#ifdef MICROHTTPD_ENABLED
  m_server = MHD_start_daemon(MHD_USE_AUTO | MHD_USE_INTERNAL_POLLING_THREAD | MHD_USE_ERROR_LOG,
    (uint16_t)m_port,  NULL, NULL, &ahc_echo, &data_for_handler, MHD_OPTION_CONNECTION_TIMEOUT, (unsigned int)120, MHD_OPTION_END);

  if (!m_server) {
    logMessage("[E] Couldn't start server");
  }
#endif
}

CServer::~CServer() {
#ifdef MICROHTTPD_ENABLED
  if (m_server) {
    MHD_stop_daemon(m_server);
  }
#endif
  logMessage("[ ]Server Closed\n");
}

std::shared_ptr<CState> CServer::state() {
  return data_for_handler.m_state;
}

std::string readFile(const std::string& fileName) {
  logMessage("[ ] Read file " + String(fileName.c_str()));
  std::ifstream inFile(getModulePath().c_str() + fileName);
  std::stringstream ss;
  while(inFile >> ss.rdbuf());
  return ss.str();
}

String CServer::handleRequest(std::shared_ptr<CState> state, String url) {
  logMessage("[ ] GET Request " + String(url.c_str()));
  // -- json state
  if (url == "/state") {
      return state->serializeToJson();
  }
  // -- play/pause
  if (url == "/playpause") {
    if (state->getEntry("pauseAtEndOfMonth") == "1") {
	    state->setEntry("pauseAtEndOfMonth", "0");
    } else {
	    state->setEntry("pauseAtEndOfMonth", "1");
    }
    return state->serializeToJson();
  }
  // -- index page
  String response = readFile("SC4WebInterface-index.html").c_str();
  return response;
}

#ifdef MICROHTTPD_ENABLED
enum MHD_Result CServer::ahc_echo(void* cls, struct MHD_Connection* connection,
    const char* url, const char* method, const char*, const char*, size_t*, void** req_cls) {

  // -- allow only http-get
  if (0 != strcmp(method, "GET")) {
      return MHD_NO;
  }
  // -- reset when done
  *req_cls = NULL;

  // -- load json
  struct handler_param* param = (struct handler_param*)cls;
  param->m_response = handleRequest(param->m_state, url); // note: stays alive to giver server time to respond from its thread

  // -- respond
  struct MHD_Response* response;
  response = MHD_create_response_from_buffer_static(param->m_response.length(), param->m_response.c_str());
  enum MHD_Result ret;
  ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
  MHD_destroy_response(response);
  return ret;
}
#endif
