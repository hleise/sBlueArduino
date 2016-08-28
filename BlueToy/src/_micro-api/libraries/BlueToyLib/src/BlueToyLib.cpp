/*
Name:    BlueToyLib.cpp
Created:  04/06/2016 13:19:20
Author: andre
Editor: http://www.visualmicro.com
*/

#include "BlueToyLib.h"
#include <CurieBLE.h>
#include <Arduino.h>
#include <CurieEEPROM.h>

#include <WString.h>
//#include <Servo.h>

//Servo myservo;
int pos = 0;
//CurieEEPROM Curie;

BlueToyClass::BlueToyClass()
{

}

void BlueToyClass::init()
{

}
/*
Method to process the different kind of messages
*/
void BlueToyClass::processMessage(BLECharacteristic data, int id)
{


	switch (id)
	{
		//gestureElementCharacteristicWritten
	case 0:
	{

		// central wrote new value to characteristic, update gestureElements list

		Serial.print("\ngestureElementCharacteristic event, written: \n");

		processGestureElement(data);

		break;
	}
	//gestureCharacteristicWritten
	case 1:
	{

		Serial.print("\ngestureCharacteristic event, written: \n");
		processGesture(data);
		break;
	}
	//profileCharacteristicWritten
	case 2:
	{

		Serial.print("\nprofileCharacteristic event, written: ");
		processProfile(data);
		break;
	}
	//linkCharacteristicWritten
	case 3:
	{
		Serial.print("\nlinkCharacteristic event, written: \n");
		processLink(data);
		break;
	}

	default:
	{
		//error en la lectura
		break;
	}
	}



}
void BlueToyClass::processGestureElement(BLECharacteristic datax)
{
	//Serial.print((char)toAscii(data[0]) + (char)toAscii(data[1]) + (char)toAscii(data[2]) + "Valio\n\n"); 
	//eg (msgtype,ID,peripheral,function,times)--->>(1charto int,2chars to int, 3char to string, 1 char to int)

	byte type = typeValue(datax[0]);
	byte iden = idValue(datax[1]);
	byte peri = peripheralValue(datax[2]);
	byte veces = timesValue(datax[3]);

	Serial.println("processing Gesture Element");

	switch (type)
	{
	case 0:
	{
		//modify
		Serial.println("case 0 to modify");
		gestureElementModify(iden, peri, veces);

		break;

	}
	case 1:
	{
		//empty
		Serial.println("case 1 to clear");
		gestureElementEmpty(iden);
		break;
	}
	case 2:
	{
		//query
		Serial.println("case 2 to query");
		gestureElementQuery(iden);

		break;
	}
	default:
	{
		//mensaje invalido
		break;
	}
	}

}

void BlueToyClass::processGesture(BLECharacteristic datax)
{
	byte type = typeValue(datax[0]);
	byte iden = idValue(datax[1]);
	byte idW0 = idValue(datax[2]);
	byte idW1 = idValue(datax[3]);
	byte idW2 = idValue(datax[4]);
	byte idW3 = idValue(datax[5]);
	byte idW4 = idValue(datax[6]);

	Serial.println("processing Gesture ");
	switch (type)
	{
	case 0:
	{
		//modify
		Serial.println("case 0 to modify");
		gestureModify(iden, idW0, idW1, idW2, idW3, idW4);

		break;
	}
	case 1:
	{
		//empty
		Serial.println("case 1 to clear");
		gestureEmpty(iden);
		break;

	}
	case 2:
	{
		//query
		Serial.println("case 2 to query");
		gestureQuery(iden);
		break;
	}
	default:
	{
		//mensaje invalido
		break;
	}
	}
}
void BlueToyClass::processProfile(BLECharacteristic datax)
{
	byte type = typeValue(datax[0]);
	byte iden = idValue(datax[1]);
	byte app = idValue(datax[2]);
	byte size = idValue(datax[3]);
	byte cont0 = idValue(datax[4]);
	byte cont1 = idValue(datax[5]);
	byte cont2 = idValue(datax[6]);
	byte cont3 = idValue(datax[7]);
	byte cont4 = idValue(datax[8]);
	byte cont5 = idValue(datax[9]);
	byte cont6 = idValue(datax[10]);
	byte cont7 = idValue(datax[11]);
	byte cont8 = idValue(datax[12]);
	byte cont9 = idValue(datax[13]);
	byte contA = idValue(datax[14]);
	byte contB = idValue(datax[15]);


	if (size > 0x0C)
	{
		size = 0x0C;
	}

	Serial.println("processing Profile");

	switch (type)
	{
	case 0:
	{
		//modify
		Serial.println("case 0 to modify");
		profileModify(iden, app, size, cont0, cont1, cont2, cont3, cont4, cont5, cont6, cont7, cont8, cont9, contA, contB);

		//delete[]contact;
		break;

	}
	case 1:
	{
		//empty
		Serial.println("case 1 to clear");
		profileEmpty(iden);

		//delete[]contact;
		break;

	}
	case 2:
	{
		Serial.println("case 2 to query");
		profileQuery(iden);


		break;


	}
	default:
	{
		//mensaje invalido

		break;
	}
	}
}
void BlueToyClass::processLink(BLECharacteristic datax)
{
	byte type = typeValue(datax[0]);
	byte iden = idValue(datax[1]);
	byte idges = idValue(datax[2]);
	byte idprof = idValue(datax[3]);

	Serial.println("processing Link");

	switch (type)
	{
	case 0:
	{
		//modify
		Serial.println("case 0 to modify");
		linkModify(iden, idges, idprof);
		break;

	}
	case 1:
	{
		//empty
		Serial.println("case 1 to clear");
		linkEmpty(iden);
		break;


	}
	case 2:
	{
		Serial.println("case 2 to query");
		linkQuery(iden);
		break;
	}
	default:
	{
		//mensaje invalido
		break;
	}

	}
}




byte BlueToyClass::typeValue(char type)
{
	byte tipe = type;
	return tipe;

}
byte BlueToyClass::idValue(char a)
{
	byte id = a;

	return id;
}

byte BlueToyClass::peripheralValue(char one)
{
	byte per = one;
	return per;
}

byte BlueToyClass::timesValue(char times)
{
	byte tim = times;
	return tim;

}



void BlueToyClass::gestureElementModify(byte iden, byte peri, byte veces)
{


	pUpdateGesElem(iden, peri, veces);


}

void BlueToyClass::gestureElementEmpty(byte iden)
{

	byte cl = byte(255);
	pUpdateGesElem(iden, cl, cl);

}
void BlueToyClass::gestureElementQuery(byte iden)
{
	pReadGesElem(iden);

}


void BlueToyClass::gestureModify(byte iden, byte idW0, byte idW1, byte idW2, byte idW3, byte idW4)
{

	pUpdateGes(iden, idW0, idW1, idW2, idW3, idW4);

}
void BlueToyClass::gestureEmpty(byte iden)
{
	byte cl = byte(255);
	pUpdateGes(iden, cl, cl, cl, cl, cl);

}
void BlueToyClass::gestureQuery(byte iden)
{
	pReadGes(iden);

}

void BlueToyClass::profileModify(byte iden, byte app, byte siz, byte cont0, byte cont1,
	byte cont2, byte cont3, byte cont4, byte cont5, byte cont6, byte cont7, byte cont8,
	byte cont9, byte contA, byte contB)
{

	char auxUser[12] = { cont0,cont1,cont2,cont3,cont4,cont5,cont6,cont7,cont8,cont9,contA,contB };
	pUpdateProf(iden, app, siz, auxUser);

}
void BlueToyClass::profileEmpty(byte iden)
{
	byte cl = byte(255);
	char auxUser[12] = { cl ,cl ,cl ,cl ,cl ,cl ,cl ,cl ,cl ,cl ,cl ,cl };
	pUpdateProf(iden, cl, (byte)(12), auxUser);


}
void BlueToyClass::profileQuery(byte iden)
{
	pReadProf(iden);

}
void BlueToyClass::linkModify(byte iden, byte idges, byte idprof)
{

	pUpdateLink(iden, idges, idprof);

}
void BlueToyClass::linkEmpty(byte iden)
{
	byte cl = byte(255);
	pUpdateLink(iden, cl, cl);

}
void BlueToyClass::linkQuery(byte iden)
{
	pReadLink(iden);

}


void BlueToyClass::gestureReader(char info[14])
{
	byte buff[270];
	for (int h = 0; h < 270; h++)
	{
		buff[h] = EEPROM.read(h);
	}

	unsigned long auxProf = 0B11111111;
	int auxGes = 0B11111111;

	//15
	for (int i = 0; i < 10; i++)
	{
		bool someMatch = true;
		unsigned long dir = eAddressProfile(i);
		unsigned long idR = (info[0]) - 48;

		int size = info[1];
		Serial.println("Valores en la EEPROM");

		Serial.println(buff[dir + 1]);

		unsigned long cont[12];
		unsigned long idE = (unsigned long)(buff[dir + 1]);
		for (int r = 0; r <size; r++)
		{

			cont[r] = buff[dir + r + 3];
			Serial.println(cont[r]);
		}
		Serial.println("Valores Recibidos");
		unsigned long infcont[12];
		Serial.println(idR);
		for (int r = 0; r <size; r++)
		{

			infcont[r] = info[2 + r];
			Serial.println(infcont[r]);
		}

		//Serial.println("control point3");
		for (int r = 0; r <size; r++)
		{

			if ((infcont[r] != cont[r]))
			{
				someMatch = false;
			}

			//Serial.println(infcont[r]);
		}
		if (someMatch == true)
		{
			Serial.println("Almost a Match");
			if (idE == idR)
			{
				Serial.println("There is a profile match");
				auxProf = buff[dir];
				for (int j = 0; j < 10; j++)
				{
					unsigned long dir1 = eAddressLink(j);
					unsigned long idPro;
					idPro = buff[dir1 + 2];

					if (idPro == auxProf)
					{
						Serial.println("There is a link match");
						auxGes = buff[dir1 + 1];

					}

				}
			}
		}


	}




	if ((auxGes != 0B11111111) && (auxGes<10))
	{

		unsigned long aux[5];
		aux[0] = 0B11111111;
		aux[1] = 0B11111111;
		aux[2] = 0B11111111;
		aux[3] = 0B11111111;
		aux[4] = 0B11111111;

		unsigned long dirx = eAddressGesture(auxGes);

		aux[0] = buff[dirx + 1];
		aux[1] = buff[dirx + 2];
		aux[2] = buff[dirx + 3];
		aux[3] = buff[dirx + 4];
		aux[4] = buff[dirx + 5];

		for (int k = 0; k < 5; k++)
		{
			unsigned long time;
			unsigned long func;
			if (aux[k] != 0B11111111 && aux[k] < 10)
			{
				unsigned long diry = eAddressGestureElement((int)aux[k]);
				func = buff[diry + 1];
				time = buff[diry + 2];

				if (time > 5)
				{
					time = 0;
				}
				if (func > 10)
				{
					func = 255;
				}
				for (int g = 0; g < (int)time; g++)
				{
					gestureExecutor(func);

				}

			}
		}
	}

}


void BlueToyClass::gestureExecutor(unsigned long func)
{
	int redpin = 3; //select the pin for the red LED
	int greenpin = 6;// select the pin for the green LED
	int bluepin = 5; // select the pin for the  blue LED
					 /*pinMode(redpin, OUTPUT);
					 pinMode(bluepin, OUTPUT);
					 pinMode(greenpin, OUTPUT);*/

	if (func == 0x00)
	{
		//Blink 
		Serial.println("BLINK");
		pinMode(12, OUTPUT);
		pinMode(13, OUTPUT);
		digitalWrite(13, HIGH);
		digitalWrite(12, HIGH);
		delay(500);
		digitalWrite(12, LOW);
		digitalWrite(13, LOW);
		delay(500);






	}
	if (func == 0x01)
	{
		//RandomRGB
		Serial.println("RGB");
		for (pos = 255; pos>0; pos--)
		{
			analogWrite(redpin, pos); analogWrite(greenpin, 255 - pos); analogWrite(bluepin, 128 - pos); delay(10);
		}
		for (pos = 0; pos<255; pos++)
		{
			analogWrite(redpin, pos); analogWrite(greenpin, 255 - pos); analogWrite(bluepin, 128 - pos); delay(10);
		}
		analogWrite(greenpin, 0);
		analogWrite(redpin, 0);
		analogWrite(bluepin, 0);

	}
	if (func == 0x02)
	{
		Serial.println("Servo");
		int del = 40;


		pinMode(9, OUTPUT);
		rotate(0);

		delay(del);

		for (pos = 0; pos <= 255; pos += 40)
		{ // goes from 0 degrees to 180 degrees
		  // in steps of 1 degree
		  //analogWrite(9, pos);            // tell servo to go to position in variable 'pos'
			rotate(pos);

			delay(del);                       // waits 15ms for the servo to reach the position
		}
		for (pos = 255; pos >= 0; pos -= 40)
		{ // goes from 180 degrees to 0 degrees
		  //analogWrite(9, pos);              // tell servo to go to position in variable 'pos'
			rotate(pos);
			delay(del);                       // waits 15ms for the servo to reach the position
		}
		for (pos = 0; pos <= 255; pos += 40)
		{ // goes from 0 degrees to 180 degrees
		  // in steps of 1 degree
		  //analogWrite(9, pos);            // tell servo to go to position in variable 'pos'
			rotate(pos);

			delay(del);                       // waits 15ms for the servo to reach the position
		}
		for (pos = 255; pos >= 0; pos -= 40)
		{ // goes from 180 degrees to 0 degrees
		  //analogWrite(9, pos);              // tell servo to go to position in variable 'pos'
			rotate(pos);
			delay(del);                       // waits 15ms for the servo to reach the position
		}


		pinMode(9, INPUT);

	}
	if (func == 0x03)
	{
		pinMode(redpin, OUTPUT);
		pinMode(bluepin, OUTPUT);
		pinMode(greenpin, OUTPUT);
		Serial.println("Red");
		//RedBlink
		analogWrite(greenpin, 0);
		analogWrite(redpin, 255);
		analogWrite(bluepin, 0);
		delay(500);
		analogWrite(greenpin, 0);
		analogWrite(redpin, 0);
		analogWrite(bluepin, 0);


	}
	if (func == 0x04)
	{
		//BlueBlink
		pinMode(redpin, OUTPUT);
		pinMode(bluepin, OUTPUT);
		pinMode(greenpin, OUTPUT);
		Serial.println("Blue");
		analogWrite(greenpin, 0);
		analogWrite(redpin, 0);
		analogWrite(bluepin, 255);
		delay(500);
		analogWrite(greenpin, 0);
		analogWrite(redpin, 0);
		analogWrite(bluepin, 0);


	}
	if (func == 0x05)
	{
		//GreenBlink
		pinMode(redpin, OUTPUT);
		pinMode(bluepin, OUTPUT);
		pinMode(greenpin, OUTPUT);
		Serial.println("Green");
		analogWrite(greenpin, 255);
		analogWrite(redpin, 0);
		analogWrite(bluepin, 0);
		delay(500);
		analogWrite(greenpin, 0);
		analogWrite(redpin, 0);
		analogWrite(bluepin, 0);

	}
	if (func == 0x06)
	{
		//YellowBlink
		pinMode(redpin, OUTPUT);
		pinMode(bluepin, OUTPUT);
		pinMode(greenpin, OUTPUT);
		Serial.println("Yellow");
		analogWrite(greenpin, 255);
		analogWrite(redpin, 255);
		analogWrite(bluepin, 0);
		delay(500);
		analogWrite(greenpin, 0);
		analogWrite(redpin, 0);
		analogWrite(bluepin, 0);

	}
	if (func == 0x07)
	{
		//OrangeBlink
		pinMode(redpin, OUTPUT);
		pinMode(bluepin, OUTPUT);
		pinMode(greenpin, OUTPUT);
		Serial.println("Orange");
		analogWrite(greenpin, 150);
		analogWrite(redpin, 255);
		analogWrite(bluepin, 0);
		delay(500);
		analogWrite(greenpin, 0);
		analogWrite(redpin, 0);
		analogWrite(bluepin, 0);

	}
	if (func == 0x08)
	{
		//PurpleBlink
		pinMode(redpin, OUTPUT);
		pinMode(bluepin, OUTPUT);
		pinMode(greenpin, OUTPUT);
		Serial.println("Purple");
		analogWrite(greenpin, 0);
		analogWrite(redpin, 255);
		analogWrite(bluepin, 255);
		delay(500);
		analogWrite(greenpin, 0);
		analogWrite(redpin, 0);
		analogWrite(bluepin, 0);

	}
	if (func == 0x09)
	{
		//WhiteBlink
		pinMode(redpin, OUTPUT);
		pinMode(bluepin, OUTPUT);
		pinMode(greenpin, OUTPUT);
		Serial.println("White");
		analogWrite(greenpin, 255);
		analogWrite(redpin, 255);
		analogWrite(bluepin, 255);
		delay(500);
		analogWrite(greenpin, 0);
		analogWrite(redpin, 0);
		analogWrite(bluepin, 0);

	}

	else
	{

		Serial.println("Weird");
		digitalWrite(8, HIGH);
		delay(500);
		digitalWrite(8, LOW);
		delay(500);



	}



}

void BlueToyClass::rotate(int angle)
{
	analogWrite(9, map(angle, 0, 255, 0, 255));
}
void BlueToyClass::pRead(unsigned long dir1)
{
	unsigned long dir = (unsigned long)dir1;
	unsigned char valu;
	EEPROM.begin();
	valu = EEPROM.read(dir);
	EEPROM.end();

	Serial.print(valu);
	Serial.print(" ");
}

void BlueToyClass::pWrite(unsigned long dir1, byte value)
{

	unsigned long dir = (unsigned long)dir1;
	EEPROM.begin();

	EEPROM.put(dir, (unsigned long)value);
	EEPROM.end();
	unsigned long a1;
	EEPROM.begin();
	a1 = EEPROM.read(dir);
	while (value != a1)
	{
		EEPROM.begin();
		EEPROM.put(dir, (unsigned long)value);
		EEPROM.end();
		EEPROM.begin();
		a1 = EEPROM.read(dir);
		EEPROM.end();
	}


	Serial.print(a1);
	Serial.print(" ");
}
void BlueToyClass::pUpdate(unsigned long dir1, byte value)
{
	unsigned long dir = (unsigned long)dir1;
	EEPROM.begin();
	EEPROM.update(dir, (unsigned long)value);
	EEPROM.end();
	unsigned long a1;
	EEPROM.begin();
	a1 = EEPROM.read(dir);
	EEPROM.end();
	while (value != a1)
	{
		EEPROM.begin();
		EEPROM.update(dir, (unsigned long)value);
		EEPROM.end();
		EEPROM.begin();
		a1 = EEPROM.read(dir);
		EEPROM.end();

	}

	Serial.print(a1);
	Serial.print(" ");
}
void BlueToyClass::pWriteGesElem(byte id, byte perId, byte veces)
{
	/*byte buff[270];
	for (int h = 0; h < 270; h++)
	{
	buff[h] = EEPROM.read(h);
	}
	unsigned long add = eAddressGestureElement((unsigned long)id);
	*/

	unsigned long add = eAddressGestureElement((unsigned long)id);
	pWrite(add, id);
	pWrite(add + 1, perId);
	pWrite(add + 2, veces);

	Serial.println();
}
void BlueToyClass::pUpdateGesElem(byte id, byte perId, byte veces)
{
	byte buff[270];
	for (int h = 0; h < 270; h++)
	{
		buff[h] = EEPROM.read(h);
	}
	unsigned long add = eAddressGestureElement((unsigned long)id);
	buff[add] = id;
	buff[add + 1] = perId;
	buff[add + 2] = veces;

	byte buff1[270];
	for (int h = 0; h < 270; h++)
	{
		buff1[h] = buff[h];
	}


	for (int r = 0; r < 270; r++)
	{
		pWrite(r, buff1[r]);
	}

	Serial.println();
}
void BlueToyClass::pReadGesElem(byte id)
{
	unsigned long add = eAddressGestureElement((unsigned long)id);
	pRead(add);
	pRead(add + 1);
	pRead(add + 2);

}
void BlueToyClass::pWriteGes(byte id, byte gesId1, byte gesId2, byte gesId3, byte gesId4, byte gesId5)
{



	unsigned long add = eAddressGesture((unsigned long)id);
	pWrite(add, id);

	pWrite(add + 1, gesId1);
	pWrite(add + 2, gesId2);
	pWrite(add + 3, gesId3);
	pWrite(add + 4, gesId4);
	pWrite(add + 5, gesId5);

	Serial.println();
}
void BlueToyClass::pUpdateGes(byte id, byte gesId1, byte gesId2, byte gesId3, byte gesId4, byte gesId5)
{
	byte buff[270];
	for (int h = 0; h < 270; h++)
	{
		buff[h] = EEPROM.read(h);
	}
	unsigned long add = eAddressGesture((unsigned long)id);
	buff[add] = id;
	buff[add + 1] = gesId1;
	buff[add + 2] = gesId2;
	buff[add + 3] = gesId3;
	buff[add + 4] = gesId4;
	buff[add + 5] = gesId5;

	byte buff1[270];
	for (int h = 0; h < 270; h++)
	{
		buff1[h] = buff[h];
	}

	for (int r = 0; r < 270; r++)
	{
		pWrite(r, buff1[r]);
	}

	Serial.println();

}


void BlueToyClass::pReadGes(byte id)
{
	unsigned long add = eAddressGesture((unsigned long)id);
	pRead(add);
	pRead(add + 1);
	pRead(add + 2);
	pRead(add + 3);
	pRead(add + 4);
	pRead(add + 5);


}
void BlueToyClass::pWriteProf(byte id, byte appId, byte siz, char user[12])
{


	unsigned long add = eAddressProfile((unsigned long)id);
	pWrite(add, id);
	pWrite(add + 1, appId);
	pWrite(add + 2, siz);
	for (int i = 0; i<siz; i++)
	{
		pWrite(add + 3 + i, user[i]);
	}
	for (int i = siz; i<12; i++)
	{
		pWrite(add + 3 + i, 255);
	}
	Serial.println();
}
void BlueToyClass::pUpdateProf(byte id, byte appId, byte siz, char user[12])
{
	byte buff[270];
	for (int h = 0; h < 270; h++)
	{
		buff[h] = EEPROM.read(h);
	}
	unsigned long add = eAddressProfile((unsigned long)id);
	buff[add] = id;
	buff[add + 1] = appId;
	buff[add + 2] = siz;
	for (int w = 0; w < siz; w++)
	{
		buff[add + 3 + w] = user[w];
	}
	for (int q = siz; q<12; q++)
	{
		buff[add + 3 + q] = 255;
	}

	byte buff1[270];
	for (int h = 0; h < 270; h++)
	{
		buff1[h] = buff[h];
	}

	for (int r = 0; r < 270; r++)
	{
		pWrite(r, buff1[r]);
	}

	/*
	unsigned long add = eAddressProfile((unsigned long)id);
	pUpdate(add, id);
	pUpdate(add + 1, appId);
	pUpdate(add + 2, siz);
	for (int i = 0; i<siz; i++)
	{
	pUpdate(add + 3 + i, user[i]);
	}
	for (int i = siz; i<12; i++)
	{
	pUpdate(add + 3 + i, 255);
	}*/
	Serial.println();
}
void BlueToyClass::pReadProf(byte id)
{
	unsigned int add = eAddressProfile((unsigned int)id);
	pRead(add);
	pRead(add + 1);
	pRead(add + 2);
	for (int i = 0; i<12; i++)
	{
		pRead(add + 3 + i);
	}

}

void BlueToyClass::pWriteLink(byte id, byte gesId, byte profId)
{


	unsigned int add = eAddressLink((unsigned long)id);
	pWrite(add, id);
	pWrite(add + 1, gesId);
	pWrite(add + 2, profId);

	Serial.println();
}
void BlueToyClass::pUpdateLink(byte id, byte gesId, byte profId)
{
	byte buff[270];
	for (int h = 0; h < 270; h++)
	{
		buff[h] = EEPROM.read(h);
	}
	unsigned long add = eAddressLink((unsigned long)id);
	buff[add] = id;
	buff[add + 1] = gesId;
	buff[add + 2] = profId;
	byte buff1[270];
	for (int h = 0; h < 270; h++)
	{
		buff1[h] = buff[h];
	}


	for (int r = 0; r < 270; r++)
	{
		pWrite(r, buff1[r]);
	}


	/*unsigned long add = eAddressLink((unsigned long)id);
	pUpdate(add, id);
	pUpdate(add + 1, gesId);
	pUpdate(add + 2, profId);

	Serial.println();*/
}
void BlueToyClass::pReadLink(byte id)
{
	unsigned long add = eAddressLink((unsigned long)id);
	pRead(add);
	pRead(add + 1);
	pRead(add + 2);

}
int BlueToyClass::eAddressGestureElement(int id)
{
	int dir = 0 + id * 3;
	return dir;
}
int BlueToyClass::eAddressGesture(int id)
{
	int dir = 30 + id * 6;
	return dir;
}
int BlueToyClass::eAddressProfile(int id)
{
	int dir = 90 + id * 15;
	return dir;
}
int BlueToyClass::eAddressLink(int id)
{
	int dir = 240 + id * 3;
	return dir;
}


void BlueToyClass::testGestureElement()
{

	//Pwrite.pWrite(1, 2);

}


void BlueToyClass::memoryInit()
{

	byte gesEleId = 0;
	Serial.println("Gesture Elements Table");
	pWriteGesElem(gesEleId, 0, 1);  gesEleId++;
	pWriteGesElem(gesEleId, 1, 1);  gesEleId++;
	pWriteGesElem(gesEleId, 2, 1);  gesEleId++;
	pWriteGesElem(gesEleId, 3, 1); gesEleId++;
	pWriteGesElem(gesEleId, 4, 1);  gesEleId++;
	pWriteGesElem(gesEleId, 5, 1);  gesEleId++;
	pWriteGesElem(gesEleId, 6, 1);  gesEleId++;
	pWriteGesElem(gesEleId, 7, 1);  gesEleId++;
	pWriteGesElem(gesEleId, 8, 1);  gesEleId++;
	pWriteGesElem(gesEleId, 9, 1);  gesEleId++;

	byte gesId = 0;
	int nul = 255;
	Serial.println("Gesture Table");
	pWriteGes(gesId, 0, nul, nul, nul, nul);  gesId++;
	pWriteGes(gesId, 1, nul, nul, nul, nul);  gesId++;
	pWriteGes(gesId, 2, nul, nul, nul, nul);  gesId++;
	pWriteGes(gesId, 3, nul, nul, nul, nul);  gesId++;
	pWriteGes(gesId, 4, nul, nul, nul, nul);  gesId++;
	pWriteGes(gesId, 5, nul, nul, nul, nul);  gesId++;
	pWriteGes(gesId, 6, nul, nul, nul, nul);  gesId++;
	pWriteGes(gesId, 7, nul, nul, nul, nul);  gesId++;
	pWriteGes(gesId, 8, nul, nul, nul, nul);  gesId++;
	pWriteGes(gesId, 9, nul, nul, nul, nul); gesId++;


	byte profId = 0;
	Serial.println("Profiles Table");
	pWriteProf(profId, (byte)0, (byte)12, "Andres Rubio");  profId++;
	pWriteProf(profId, (byte)7, (byte)12, "@andresrubio"); profId++;
	pWriteProf(profId, (byte)2, (byte)12, "Xavier Rubio"); profId++;
	pWriteProf(profId, (byte)2, (byte)12, "Hunter Leise");  profId++;
	pWriteProf(profId, (byte)5, (byte)12, "Hunter Leise");  profId++;
	pWriteProf(profId, (byte)0, (byte)12, "Thomas Caniz");  profId++;
	pWriteProf(profId, (byte)7, (byte)12, "@HunterLeise");  profId++;
	pWriteProf(profId, (byte)4, (byte)12, "Andres Rubio");  profId++;
	pWriteProf(profId, (byte)1, (byte)12, "Hunter Leise");  profId++;
	pWriteProf(profId, (byte)3, (byte)12, "Huntes Leise");  profId++;


	byte linId = 0;
	Serial.println("Link Table");
	pWriteLink(linId, (byte)1, (byte)0);  linId++;
	pWriteLink(linId, (byte)1, (byte)1);  linId++;
	pWriteLink(linId, (byte)1, (byte)2);  linId++;
	pWriteLink(linId, (byte)3, (byte)3);  linId++;
	pWriteLink(linId, (byte)4, (byte)4);  linId++;
	pWriteLink(linId, (byte)5, (byte)5); linId++;
	pWriteLink(linId, (byte)6, (byte)6);  linId++;
	pWriteLink(linId, (byte)7, (byte)7);  linId++;
	pWriteLink(linId, (byte)8, (byte)8);  linId++;
	pWriteLink(linId, (byte)9, (byte)9); linId++;
	//Serial.println(Curie.end());
}
BlueToyClass BlueToy;