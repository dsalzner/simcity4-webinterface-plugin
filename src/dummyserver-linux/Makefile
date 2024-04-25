all:
	g++ --std=c++17 -fpermissive ../../lib/arduinocore-avr-1.8.6-wstring/WString.cpp ../arduino_wstring_x86_64.cpp ../common.cpp ../CState.cpp ../CServer.cpp main.cpp -I../../lib/libmicrohttpd/linux -I../../lib/libmicrohttpd -I../../lib/arduinocore-avr-1.8.6-wstring/ -I../ ../../lib/libmicrohttpd/linux/libmicrohttpd.a -o main

clean:
	rm main
