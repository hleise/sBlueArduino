/*
Name:    BlueToy.ino
Created:  04/06/2016 13:19:20
Author: andre
Editor: http://www.visualmicro.com
*/





#include <SoftwareSerial.h>
//#include <Servo.h>
#include <CurieEEPROM.h>
#include <CurieBLE.h>
#include <BLEUuid.h>
#include <BLETypedCharacteristics.h>
#include <BLETypedCharacteristic.h>
#include <BLEService.h>
#include <BLEPeripheral.h>
#include <BLEDescriptor.h>
#include <BLECommon.h>
#include <BLECharacteristic.h>
#include <BLECentral.h>
#include <BLEAttribute.h>
#include <Arduino.h>

#include "BlueToyLib.h"


BLEPeripheral blePeripheral;// create peripheral instance
BLEService blueToyService2("B8DD6091-F051-B715-6B1E-EF10A2AA9F7A"); // create the custom service
BLEService blueToyService("A7DD6091-F051-B715-6B1E-EF10A2AA9F7A"); // create the custom service


																   /*create multiple characteristics that allow to the remote device read and write
																   each characteristic is the representation of the functions of the API
																   */
BLECharacteristic gestureElementChar("A7DD6091-F051-B715-6B1E-EF10A2AA9F7B", BLERead | BLEWrite | BLENotify, 4);
BLECharacteristic gestureChar("A7DD6091-F051-B715-6B1E-EF10A2AA9F7C", BLERead | BLEWrite | BLENotify, 7);
BLECharacteristic profileChar("A7DD6091-F051-B715-6B1E-EF10A2AA9F7D", BLERead | BLEWrite | BLENotify, 16);
BLECharacteristic linkChar("A7DD6091-F051-B715-6B1E-EF10A2AA9F7E", BLERead | BLEWrite | BLENotify, 4);
BLECharacteristic notificationChar("A7DD6091-F051-B715-6B1E-EF10A2AA9F8F", BLERead | BLEWrite | BLENotify, 15);

//Service that indicate if the Bluetooth is asociated

const int ledConexion = 8;
//Switch Button

volatile byte state = LOW;
//BlueToy Instance
//BlueToyClass BToy;
SoftwareSerial slavePort(2, 4);


BlueToyClass BTC;

int redpin = 3; //select the pin for the red LED
int greenpin = 5;// select the pin for the green LED
int bluepin = 6; // select the pin for the  blue LED



				 // the setup function runs once when you press reset or power the board
void setup()
{





	init();




}

// the loop function runs over and over again until power down or reset
void loop()
{
	// put your main code here, to run repeatedly:
	// poll peripheral
	//blePeripheral.poll();
	//slavePort.listen();



	if (slavePort.available())
	{
		char  aux[14];
		int i = 0;

		while (slavePort.available())
		{

			char inByte = slavePort.read();
			Serial.print(inByte);
			aux[i] = inByte;
			i++;

		}
		Serial.println(aux);
		if (((aux[1] == '1') && (aux[2] == '0')) || ((aux[1] == '1') && (aux[2] == '1')) || ((aux[1] == '1') && (aux[2] == '2')))
		{
			char size = 2;
			if (aux[2] == '0')
			{
				size = 0x0A;
			}
			if (aux[2] == '1')
			{
				size = 0x0B;
			}
			if (aux[2] == '2')
			{
				size = 0x0C;
			}
			aux[1] = size;
			for (int i = 2; i<size + 2; i++)
			{
				aux[i] = aux[i + 1];
			}

		}
		Serial.println();
		Serial.println(aux[1]);
		BlueToy.gestureReader(aux);

	}
	//blePeripheral.poll();

	blePeripheral.poll();

	Serial.flush();



}


void init()
{
	// put your setup code here, to run once:

	pinMode(ledConexion, OUTPUT);
	pinMode(10, INPUT);
	//pinMode(11, OUTPUT);
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);

	pinMode(9, OUTPUT);

	pinMode(redpin, OUTPUT);
	pinMode(bluepin, OUTPUT);
	pinMode(greenpin, OUTPUT);


	// set advertiserd local name an service UUID:
	blePeripheral.setLocalName("BlueToy");
	blePeripheral.setAdvertisedServiceUuid(blueToyService.uuid());
	blePeripheral.setDeviceName("BLEBLUETOY");
	// add service and characteristics:


	//blePeripheral.addAttribute(blueToyService);
	blePeripheral.addAttribute(blueToyService);

	blePeripheral.addAttribute(gestureElementChar);

	blePeripheral.addAttribute(gestureChar);

	blePeripheral.addAttribute(profileChar);

	blePeripheral.addAttribute(linkChar);

	blePeripheral.addAttribute(notificationChar);





	// assign event handlers for connected, disconected to peripheral
	blePeripheral.setEventHandler(BLEConnected, blePeripheralConnectHandler);
	blePeripheral.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

	// assign event handlers for characteristics
	gestureElementChar.setEventHandler(BLEWritten, gestureElementCharacteristicWritten);
	gestureChar.setEventHandler(BLEWritten, gestureCharacteristicWritten);
	profileChar.setEventHandler(BLEWritten, profileCharacteristicWritten);
	linkChar.setEventHandler(BLEWritten, linkCharacteristicWritten);
	notificationChar.setEventHandler(BLEWritten, notificationCharacteristicWritten);



	// set initial value for the characteristics:
	/*gestureElementChar.setValue(0, 0);
	gestureChar.setValue(0, 0);
	profileChar.setValue(0, 0);
	linkChar.setValue(0, 0);
	notificationChar.setValue(0, 0);*/



	// begin advertising BLE service:
	blePeripheral.begin();
	Serial.println("BLE Blue Toy Peripheral device active, waiting for connections...");

	slavePort.begin(9600);
	Serial.begin(9600);

}

void blePeripheralConnectHandler(BLECentral& central)
{
	// central connected event handler
	Serial.print("Connected event, central: ");
	Serial.println("LED on");
	digitalWrite(ledConexion, HIGH);
	Serial.println(central.address());
}

void blePeripheralDisconnectHandler(BLECentral& central)
{
	// central disconnected event handler
	Serial.print("Disconnected event, central: ");
	Serial.println("LED off");
	digitalWrite(ledConexion, LOW);
	Serial.println(central.address());
	blePeripheral.begin();
	int pin = 10;
	pinMode(pin, OUTPUT);      // sets the digital pin as output
	digitalWrite(pin, LOW); // sets the LED off 
}

void gestureElementCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic)
{


	//code here
	if (gestureElementChar.value())
	{
		//Call to the library processMessage Method

		BlueToy.processMessage(gestureElementChar, 0);




	}




}
void gestureCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic)
{
	// central wrote new value to characteristic, update gesture list



	//code here
	if (gestureChar.value())
	{
		// central wrote new value to characteristic, update gesture list

		BlueToy.processMessage(gestureChar, 1);



	}

}
void profileCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic)
{
	// central wrote new value to characteristic, update profile list

	//code here
	if (profileChar.value())
	{
		BlueToy.processMessage(profileChar, 2);



	}

}
void linkCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic)
{
	// central wrote new value to characteristic, update link list
	//code here


	if (linkChar.value())
	{
		BlueToy.processMessage(linkChar, 3);

	}

}


void notificationCharacteristicWritten(BLECentral& central, BLECharacteristic& characteristic)
{
	// central wrote new value to characteristic, update link list
	//code here

	Serial.print("\ngestureNotificationCharacteristic event, written: \n");

	if (notificationChar.value())
	{
		if (notificationChar[0] < 10)
		{
			//Android supports this directly
			BlueToy.gestureExecutor(notificationChar[0]);
		}
		if (notificationChar[0] >= 10)
		{
			BlueToy.memoryInit();
		}
		//BTC.testGestureElement();
		//Serial.print("\nnotificationCharacteristic event, written: \n");
		
	}
}

