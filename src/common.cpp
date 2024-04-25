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

#include <time.h>
#include "common.h"

#define PLUGIN_NAME "Sim City 4 Web Interface"
#define PLUGIN_AUTHOR "www.dennissalzner.de 2024"

#ifdef _WIN32
#include <codecvt>
#include <Windows.h>
#include <shlwapi.h>
#include <atlstr.h>
HANDLE hConsoleOutput;
#else
#include <iostream>
#endif

const String getTimestamp() {
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d_%H-%M-%S", &tstruct);
  return buf;
}

const String getModulePath() {
#ifdef _WIN32
  WCHAR path[MAX_PATH];
  HMODULE hm;
  if(GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
    (LPWSTR) &getModulePath, &hm )) {
    GetModuleFileNameW(hm, path, MAX_PATH);
    PathRemoveFileSpecW(path);
  }
  using convert_type = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_type, wchar_t> converter;
  std::string converted_str = converter.to_bytes(path);
  converted_str = converted_str + "\\";
  return converted_str.c_str();
#else
  return "";
#endif
}

void logInit() {
#ifdef _WIN32
  // -- open console
  AllocConsole();
  hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  if(!hConsoleOutput) {
	MessageBoxA(NULL, "SC4WebInterface - Could not create console", "SC4WebInterface", MB_OK | MB_ICONERROR);
  }
  // -- disable close
  HWND consoleWindowHandle = GetConsoleWindow();
  HMENU consoleMenuHandle = GetSystemMenu(consoleWindowHandle, FALSE);
  EnableMenuItem(consoleMenuHandle, SC_CLOSE, MF_GRAYED);
#endif
  logMessage(PLUGIN_NAME);
  logMessage(PLUGIN_AUTHOR);
  logMessage(getModulePath());
}

void logMessage(String msg) {
#ifdef _WIN32
  if (!hConsoleOutput) {
    logInit();
  }
  msg += "\n";
  WriteFile(hConsoleOutput, msg.c_str(), msg.length(), NULL, NULL);
#else
  std::cout << msg.c_str() << std::endl;
#endif
}
