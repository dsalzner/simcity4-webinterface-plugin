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

#include "common.h"
#include "CServer.h"

#include <memory>

#include "cMessageLoggerCOMDirector.h"
#include "cIGZFrameWork.h"
#include "cIGZMessage2Standard.h"
#include "cIGZMessageServer2.h"
#include "cISC4App.h"
#include "cISC4City.h"
#include "GZServPtrs.h"
#include "cISC4Simulator.h"
#include "cISC4ResidentialSimulator.h"
#include "cISC4DemandSimulator.h"
#include "cISC4Demand.h"
#include "cISC4BudgetSimulator.h"
#include "cISC4PollutionSimulator.h"


cMessageLoggerCOMDirector::cMessageLoggerCOMDirector() {
  m_state = std::make_shared<CState>();
  m_server = std::make_shared<CServer>(m_state);
}
cMessageLoggerCOMDirector::~cMessageLoggerCOMDirector() { }

bool cMessageLoggerCOMDirector::OnStart(cIGZCOM* pCOM) {
  RZGetFrameWork()->AddHook(static_cast<cIGZFrameWorkHooks*>(this));
  return true;
}

bool cMessageLoggerCOMDirector::PostAppInit() {
  cIGZMessageServer2Ptr pMessageServer;
  if (!pMessageServer)
  {
    logMessage("[E] Could not fetch message server.\n");
    return true;
  }
  pMessageServer->AddNotification(this, 0x66956816); // kSC4MessageSimNewMonth
  return true;
}

bool cMessageLoggerCOMDirector::DoMessage(cIGZMessage2* pMessage) {
  cIGZMessage2Standard* pStandardMessage = static_cast<cIGZMessage2Standard*>(pMessage);
  uint32_t dwType = pMessage->GetType();
  if (dwType == 0x66956816) { // kSC4MessageSimNewMonth
	  logMessage("[ ] Update Internal State");
	  cISC4AppPtr pSC4App;
	  if (pSC4App) {
		  cISC4City* pCity = pSC4App->GetCity();
		  if (pCity) {
			  cRZBaseString tmp;

			  // -- set city name
			  pCity->GetCityName(tmp);
			  m_state->setEntry("cityName", tmp.ToChar());

			  // -- set city description
			  pCity->GetCityDescription(tmp);
			  m_state->setEntry("cityDescription", tmp.ToChar());

			  // -- set mayor name
			  pCity->GetMayorName(tmp);
			  m_state->setEntry("mayorName", tmp.ToChar());

			  // -- set low/medium/high wealth population
			  auto getPopulation = [&](uint32_t groupId) {
				  cISC4DemandSimulator* pDemandSimulator = pCity->GetDemandSimulator();
				  if (pDemandSimulator) {
					  constexpr uint32_t cityCensusIndex = 0;
					  const cISC4Demand* demand = pDemandSimulator->GetDemand(groupId, cityCensusIndex);
					  if (demand) {
						  float value = demand->QuerySupplyValue();
						  return String(static_cast<int>(value));
					  }
				  }
				  return String("");
				};
			  m_state->setEntry("populationR1", getPopulation(0x1010));
			  m_state->setEntry("populationR2", getPopulation(0x1020));
			  m_state->setEntry("populationR3", getPopulation(0x1030));

			  m_state->setEntry("populationCs1", getPopulation(0x3110));
			  m_state->setEntry("populationCs2", getPopulation(0x3120));
			  m_state->setEntry("populationCs3", getPopulation(0x3130));
        m_state->setEntry("populationCo2", getPopulation(0x3320));
        m_state->setEntry("populationCo3", getPopulation(0x3330));

        m_state->setEntry("populationIR", getPopulation(0x4100));
        m_state->setEntry("populationID", getPopulation(0x4200));
        m_state->setEntry("populationIM", getPopulation(0x4300));
        m_state->setEntry("populationIHT", getPopulation(0x4400));

			  // -- set budget
			  cISC4BudgetSimulator* pBudgetSimulator = pCity->GetBudgetSimulator();
			  if (pBudgetSimulator) {
				  m_state->setEntry("ytdIncome", String(static_cast<int>(pBudgetSimulator->GetYTDIncome())));
				  m_state->setEntry("ytdExpenses", String(static_cast<int>(pBudgetSimulator->GetEstIncome())));

				  m_state->setEntry("estIncome", String(static_cast<int>(pBudgetSimulator->GetYTDExpenses())));
				  m_state->setEntry("estExpenses", String(static_cast<int>(pBudgetSimulator->GetEstExpenses())));

				  m_state->setEntry("totalMonthlyExpense", String(static_cast<int>(pBudgetSimulator->GetTotalMonthlyExpense())));
				  m_state->setEntry("totalYearlyExpense", String(static_cast<int>(pBudgetSimulator->GetTotalYearlyExpense())));

				  m_state->setEntry("totalMonthlyIncome", String(static_cast<int>(pBudgetSimulator->GetTotalMonthlyIncome())));
				  m_state->setEntry("totalYearlyIncome", String(static_cast<int>(pBudgetSimulator->GetTotalYearlyIncome())));
			  }

			  // -- set water pollution
			  cISC4PollutionSimulator* pPolutionSimulator = pCity->GetPollutionSimulator();
			  if (pPolutionSimulator) {
				  m_state->setEntry("waterPollutionLevel", String(static_cast<int>(pPolutionSimulator->GetAverageWaterValue())));
			  }

			  // -- set play/pause
			  auto setPause = [&](bool pause) {
				  cISC4Simulator* pSimulator = pCity->GetSimulator();
				  if (pSimulator) {
					  if (pause) {
						  pSimulator->Pause();
					  }
					  else {
						  pSimulator->SetSimSpeed(0);
					  }
				  }
				  };

			  if (m_state->getEntry("pauseAtEndOfMonth") == "1") {
				  logMessage("[ ] Pause Game");
				  setPause(true);
			  }
		  }
	  }
  }
  return true;
}
