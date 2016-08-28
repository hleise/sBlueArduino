/*
Name:		BlueToyLib.h
Created:	04/06/2016 13:19:20
Author:	andre
Editor:	http://www.visualmicro.com
*/

#ifndef _BlueToyLib_h
#define _BlueToyLib_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#include <CurieBLE.h>

//#include <Servo.h>



#else
//#include "WProgram.h"
#endif
class BlueToyClass
{
protected:


public:


	BlueToyClass();
	void init();
	void processMessage(BLECharacteristic data, int id);
	void processGestureElement(BLECharacteristic datax);
	void processGesture(BLECharacteristic datax);
	void processProfile(BLECharacteristic datax);
	void processLink(BLECharacteristic datax);
	byte typeValue(char type);
	byte idValue(char a);
	byte peripheralValue(char one);
	byte timesValue(char times);
	int eAddressGestureElement(int id);
	int eAddressGesture(int id);
	int eAddressProfile(int id);
	int eAddressLink(int id);
	void gestureElementModify(byte iden, byte peri, byte veces);
	void gestureElementEmpty(byte iden);
	void gestureElementQuery(byte iden);
	void gestureModify(byte iden, byte idW0, byte idW1, byte idW2, byte idW3, byte idW4);
	void gestureEmpty(byte iden);
	void gestureQuery(byte iden);
	void profileModify(byte iden, byte app, byte size, byte cont0, byte cont1, byte cont2, byte cont3, byte cont4, byte cont5, byte cont6, byte cont7, byte cont8, byte cont9, byte contA, byte contB);
	void profileEmpty(byte iden);
	void profileQuery(byte iden);
	void linkModify(byte iden, byte idges, byte idprof);
	void linkEmpty(byte iden);
	void linkQuery(byte iden);
	void gestureReader(char  info[14]);
	void pWrite(unsigned long dir, byte value);

	void pUpdate(unsigned long dir1, byte value);

	void pWriteGesElem(byte id, byte perId, byte veces);

	void pUpdateGesElem(byte id, byte perId, byte veces);

	void pWriteGes(byte id, byte gesId1, byte gesId2, byte gesId3, byte gesId4, byte gesId5);

	void pUpdateGes(byte id, byte gesId1, byte gesId2, byte gesId3, byte gesId4, byte gesId5);

	void pReadGesElem(byte iden);

	void pReadGes(byte id);

	void pWriteProf(byte id, byte appId, byte siz, char user[12]);

	void pUpdateProf(byte id, byte appId, byte siz, char user[12]);

	void pReadProf(byte id);

	void pWriteLink(byte id, byte gesId, byte profId);

	void pUpdateLink(byte id, byte gesId, byte profId);

	void pReadLink(byte id);

	void gestureExecutor(unsigned long func);

	void rotate(int angle);

	void pRead(unsigned long dir);



	void testGestureElement();

	void memoryInit();

};

extern BlueToyClass BlueToy;
//extern Servo myservo;




#endif