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
#pragma once

#define MICROHTTPD_ENABLED

#ifdef MICROHTTPD_ENABLED
#include "microhttpd.h"
#endif

#include <memory>
#include <stdexcept>

#include "common.h"
#include "CState.h"

class CServer {
public:
    CServer(std::shared_ptr<CState> state);
    ~CServer();
    std::shared_ptr<CState> state();

    static String handleRequest(std::shared_ptr<CState> state, String url);
#ifdef MICROHTTPD_ENABLED
    static enum MHD_Result ahc_echo(void* cls, struct MHD_Connection* connection,
        const char* url, const char* method, const char*, const char*, size_t*, void** req_cls);
#endif

private:
    int m_port = 9030;

#ifdef MICROHTTPD_ENABLED
    struct MHD_Daemon* m_server;
#endif
    struct handler_param {
        std::shared_ptr<CState> m_state;
        String m_response;
    };
    struct handler_param data_for_handler;
};

