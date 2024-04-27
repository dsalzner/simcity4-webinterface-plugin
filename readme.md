# Sim City 4 Web-Interface Plug-In

A plug-in for Sim City 4 that allows viewing game metrics in a web browser. The web browser can run on a secondary monitor, smart phone or tablet. This adds basic second-screen/multi-monitor capabilities to the game.

The web interface can be edited by altering the included *.html page. It uses AJAX to automatically update game metrics from the plug-in via JSON.

The plug-in supports pausing the game so it can automatically pause the game based on a metric e.g if available power or population fall below a threshold. That way the game can be run unattended without risk.

![SimCity 4 Web-Interface Plug-In](scrn/2024-05-27-SimCity4WebInterfacePlugIn.png)

## Dependencies

Inspiration was taken from

* GitHub 0xC0000054/sc4-legalize-gambling-ordinance-upgrade
* GitHub Killeroo/SC4MessageViewer

Dependencies are in the ```lib/``` folder

* GitHub nsgomez/gzcom-dll 
* GitHub Karlson2k/libmicrohttpd
* GitHub arduino/ArduinoCore-avr for WString.c/.h

## Usage

Copy ```SC4WebInterface.dll``` and ```SC4WebInterface_index.html``` to

```
C:\Users\<UserName>\Documents\SimCity 4\Plugins
```

Unblock port 9030/tcp in firewall. For this on administrator PowerShell:

``` 
netsh advfirewall firewall add rule name="Open Port 9030" dir=in action=allow protocol=TCP localport=9030
```

Run the game. It may be helpful to run it in window mode (see below).

Then in your web-browser open

```
http://127.0.0.1:9030/
```

### JSON REST Interface

The JSON state can be directly accessed in case you want to do data analysis/live charts with Python or similar.

```
http://127.0.0.1:9030/state
```

```
{
"timestamp": "xxxx-yy-zz_hh-mm-ss",
"cityName": "n/a",
"cityDescription": "n/a",
"mayorName": "n/a",
"lowWealthPopulation": "n/a",
"medWealthPopulation": "n/a",
"highWealthPopulation": "n/a",
"ytdIncome": "n/a",
"ytdExpenses": "n/a",
"estIncome": "n/a",
"estExpenses": "n/a",
"totalMonthlyExpense": "n/a",
"totalYearlyExpense": "n/a",
"totalMonthlyIncome": "n/a",
"totalYearlyIncome": "n/a",
"isPaused": "n/a",
}
```

## Sim City 4 for Window Mode

You may want to add additional parameters to launch the game in window mode and without the intro video

```
-w -intro:off
```

When launching from Steam set these parameters in the Steam game options menu.

## Compiling from source

The code can be compiled from source on Windows with Visual Studio 2022.
Alternatively there is a Dummy-Server that can be built and run under Linux.

### Visual Studio

* Visual Studio 2022 Community Edition

### Configure

In ```SC4WebInterface.vcxproj``` adjust

* ```<Command>xcopy "$(TargetPath)" "``` xcopy to your Sim City 4 plugin path

### Build

From the VS 2022 Developer Command Prompt, run

```
cd src/
msbuild .\SC4WebInterface.sln
```

## (Optional) a standalone Dummy-Server for Linux

```
cd lib/libmicrohttpd/linux
make
make -f Makefile.staticlib
cd ../../../src/dummyserver-linux
make
./main
```

## Release History

### v0.0.2

* Performance improvement. Less frequent internal state updates.
* Pause from the interface now works more reliably. It engages/disengages and when engaged pauses the game at the next simulated month.
* Interface now also shows a plot of income/expenses
* Visual Studio project configuration path fixes

### v0.0.1

* Initial Release
* Interface shows JSON
