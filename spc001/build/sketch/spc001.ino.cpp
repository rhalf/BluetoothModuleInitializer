#include <Arduino.h>
#line 1 "C:\\Users\\rhalf\\Documents\\GitHub\\SulitPisoBluetoothInitializer\\spc001\\spc001.ino"
#line 1 "C:\\Users\\rhalf\\Documents\\GitHub\\SulitPisoBluetoothInitializer\\spc001\\spc001.ino"
#include<Timer.h>
#include <SoftwareSerial.h>

Timer tExecute(Timer::MILLIS), tSerial(Timer::MILLIS);
SoftwareSerial bluetooth(9, 8);   // RX | TX

//uncomment if it is 
// SulitPisoCharge - SPC001
// SulitPisoMultipurpose - SPM001
// SulitPisoWifi - SPW001

String bluetoothName = "SPC001";
//String bluetoothName = "SPM001";
//String bluetoothName = "SPW001";

//default pin
String bluetoothPin = "0000";
String bluetoothUart = "9600,0,0";

uint32_t runTime = 0;

#line 22 "C:\\Users\\rhalf\\Documents\\GitHub\\SulitPisoBluetoothInitializer\\spc001\\spc001.ino"
void cbExecute();
#line 42 "C:\\Users\\rhalf\\Documents\\GitHub\\SulitPisoBluetoothInitializer\\spc001\\spc001.ino"
void print(String data);
#line 48 "C:\\Users\\rhalf\\Documents\\GitHub\\SulitPisoBluetoothInitializer\\spc001\\spc001.ino"
void cbSerial();
#line 59 "C:\\Users\\rhalf\\Documents\\GitHub\\SulitPisoBluetoothInitializer\\spc001\\spc001.ino"
void setup();
#line 76 "C:\\Users\\rhalf\\Documents\\GitHub\\SulitPisoBluetoothInitializer\\spc001\\spc001.ino"
void loop();
#line 22 "C:\\Users\\rhalf\\Documents\\GitHub\\SulitPisoBluetoothInitializer\\spc001\\spc001.ino"
void cbExecute() {
  runTime++;

  if (runTime == 1) print("AT+VERSION\r\n");
  if (runTime == 2) print("AT+ADDR\r\n");
  if (runTime == 3) print("AT+ROLE\r\n");

  if (runTime == 6) print("AT+NAME:" + bluetoothName + "\r\n");
  if (runTime == 7) print("AT+PSWD:\"" + bluetoothPin + "\"\r\n");
  if (runTime == 8) print("AT+UART=" + bluetoothUart +"\r\n");
  
  if (runTime == 12) print("AT+NAME\r\n");
  if (runTime == 13) print("AT+PSWD\r\n");
  if (runTime == 14) print("AT+UART\r\n");

  //Return the default settings
  //AT+RESET : Reset and exit AT mode
  //AT+ORGL : Restore factory settings
}

void print(String data) {
   bluetooth.print(data);
   Serial.println("====================");
   Serial.print(data);
}

void cbSerial() {
  // Keep reading from HC-05 and send to Arduino
  // Serial Monitor
  while (bluetooth.available())
    Serial.write(bluetooth.read());
  // Keep reading from Arduino Serial Monitor
  //  and send to HC-05
  while (Serial.available())
    bluetooth.write(Serial.read());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // HC-05 default baudrate in AT 34800
  // HC-06 default baudrate in AT 9600
  bluetooth.begin(9600);

  Serial.println("A.R.T.S Bluetooth Module Initializer");
  Serial.println("created by: Rhalf Wendel Caacbay");

  tExecute.begin(Timer::FOREVER, 500, cbExecute);
  tSerial.begin(Timer::FOREVER, 10, cbSerial);

  tExecute.start();
  tSerial.start();
}

void loop() {
  // put your main code here, to run repeatedly:
  tExecute.run();
  tSerial.run();
}

