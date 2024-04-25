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

#pragma once

#include <stdio.h>
#include <iostream>
#include <memory>
#include <thread>

#include "cRZCOMDllDirector.h"
#include "cRZMessage2COMDirector.h"
#include "cIGZMessage2.h"
#include "cIGZFrameWork.h"

#include "common.h"
#include "CState.h"
#include "CServer.h"

static const uint32_t kMessageLoggerDirectorId = 0xD81A8F98;

class cMessageLoggerCOMDirector : public cRZMessage2COMDirector {
public:
	cMessageLoggerCOMDirector();
	virtual ~cMessageLoggerCOMDirector();
public:
	uint32_t GetDirectorID() const { return kMessageLoggerDirectorId; }
	bool DoMessage(cIGZMessage2* pMessage);
	bool OnStart(cIGZCOM* pCOM);
	bool PostAppInit();
private:
	std::shared_ptr<CState> m_state;
	std::shared_ptr<CServer> m_server;
};

cRZCOMDllDirector* RZGetCOMDllDirector() {
	static cMessageLoggerCOMDirector sDirector;
	return &sDirector;
}
