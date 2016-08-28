#include <lib_aci.h>
#include <SPI.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <notif.h>



Notif notif(9,8);
ancs_notification_t* current_notif = NULL;
unsigned long auxVal=0;

SoftwareSerial masterSerialPort(2,4);




boolean connected = false;

void ancs_connected() {
  
    connected = true;
}
void ancs_disconnected() {
    connected = false;
}

void ancs_reset() {
    connected = false;
    Serial.println(" Bond Cleared ");
    Serial.println("Please Reset");
}

void ancs_notifications(ancs_notification_t* notif) {
     
  int pos=0;
int val;
    // pinMode(10, OUTPUT);
    
     Serial.print (F("["));
     if ((notif->flags & ANCS_EVT_FLAG_SILENT) == ANCS_EVT_FLAG_SILENT)
     Serial.print(F("-"));
     else if ((notif->flags & ANCS_EVT_FLAG_IMPORTANT) == ANCS_EVT_FLAG_IMPORTANT)
     Serial.print(F("!"));
     else
     Serial.print(" ");
     Serial.print (F("] "));
     Serial.print(F("Notif #")); 
     Serial.print( notif->uid); 
     Serial.print( F(" ; from: '"));
     #ifdef ANCS_USE_APP
     Serial.print( notif->app);
     #endif
     


     
     Serial.println( F("'"));
     Serial.print(F("   category: "));
     switch (notif->category) {
     case ANCS_CATEGORY_INCOMING_CALL:
       Serial.println(F("incoming call"));
     break;
     case ANCS_CATEGORY_MISSED_CALL:
       Serial.println(F("missed call"));
     break;
     case ANCS_CATEGORY_VOICEMAIL:
       Serial.println(F("voicemail call"));
     break;
     case ANCS_CATEGORY_SOCIAL:
       Serial.println(F("social msg"));
     break;
     case ANCS_CATEGORY_OTHER:
       Serial.println(F("other"));
     break;
     case ANCS_CATEGORY_SCHEDULE:
       Serial.println(F("schedule"));
     break;
     case ANCS_CATEGORY_EMAIL:
       Serial.println(F("email"));
     break;
     case ANCS_CATEGORY_NEWS :
       Serial.println(F("news"));
     break;
     case ANCS_CATEGORY_HEALTH_FITNESS:
       Serial.println(F("health & fitness"));
     break;
     case ANCS_CATEGORY_BUSINESS_FINANCE:
       Serial.println(F("business & finance"));
     break;
     case ANCS_CATEGORY_LOCATION:
       Serial.println(F("location"));
     break;
     case ANCS_CATEGORY_ENTERTAINMENT:
       Serial.println(F("entertainment"));
     break;
     default:
     Serial.print(F("unknown: "));
     Serial.println(notif->category, DEC);
     break;
     //return;
     }
     #ifdef ANCS_USE_APP
     Serial.print(F("   app:    '")); Serial.print( notif->app    ); Serial.println("'");
     #endif

     char tit[50];
     strcpy(tit,notif->title);
     Serial.print(F("   title:    '")); Serial.print( tit    ); Serial.println("'");
     
     #ifdef ANCS_USE_SUBTITLE
     Serial.print(F("   subtitle: '")); Serial.print( notif->subtitle ); Serial.println("'");
     #endif
     char mess[50];
     strcpy(mess,notif->message);
     Serial.print(F("   message:  '")); Serial.print( mess  ); Serial.println("'");


char appId=255;

if((String)tit=="WhatsApp")
{
  appId='0';
  Serial.println(appId);
  for(int i=0; i<(notif->msg_len);i++)
  {
  mess[i]=mess[i+3];
  }
 
  char * aux=strchr(mess,':');
  Serial.println((char)(aux-mess),HEX);
  if(aux-mess<12)
  {
    char auy[aux-mess];
    strncpy(auy,mess,aux-mess);
    auy[aux-mess]='\0';
    Serial.print(F("User Identifier: "));Serial.println(auy);

    masterSerialPort.print(appId);
    
    masterSerialPort.print((aux-mess),HEX);
    masterSerialPort.print(auy);
  }
  if(aux-mess>=12)
  {
    char auy[12];
    strncpy(auy,mess,12);
    auy[12]='\0';
    Serial.print(F("User Identifier: "));
    Serial.println(auy);
     masterSerialPort.print(appId);
     
     masterSerialPort.print(0x0C);
    masterSerialPort.print(auy);
  }
}
if((String)tit=="Messenger")
{
  appId='2';
  Serial.println(appId);
 
 
  char * aux=strchr(mess,':');
  Serial.println((byte)(aux-mess), HEX);
  if(aux-mess<12)
  {
    char auy[aux-mess];
    strncpy(auy,mess,aux-mess);
    auy[aux-mess]='\0';
    Serial.print(F("User Identifier: "));Serial.println(auy);

    masterSerialPort.print(appId);
    masterSerialPort.print((byte)(aux-mess),HEX);
    masterSerialPort.print(auy);
  }
  if(aux-mess>=12)
  {
    char auy[12];
    strncpy(auy,mess,12);
    auy[12]='\0';
    Serial.print(F("User Identifier: "));Serial.println(auy);
     masterSerialPort.print(appId);
     masterSerialPort.print(0x0C);
    masterSerialPort.print(auy);
  }
}
if((String)tit=="Skype")
{
  appId='2';
  Serial.println(appId);
 
 
  char * aux=strchr(mess,':');
  Serial.println((byte)(aux-mess), HEX);
  if(aux-mess<12)
  {
    char auy[aux-mess];
    strncpy(auy,mess,aux-mess);
    auy[aux-mess]='\0';
    Serial.print(F("User Identifier: "));Serial.println(auy);

    masterSerialPort.print(appId);
    masterSerialPort.print((byte)(aux-mess),HEX);
    masterSerialPort.print(auy);
  }
  if(aux-mess>=12)
  {
    char auy[12];
    strncpy(auy,mess,12);
    auy[12]='\0';
    Serial.print(F("User Identifier: "));Serial.println(auy);
     masterSerialPort.print(appId);
     masterSerialPort.print(0x0C);
    masterSerialPort.print(auy);
  }
}



/*char* y=notif->message;
char* d="😀";
if( strcmp(y,d)==0)
{
  Serial.println("Funciona");
  }*/

    current_notif = notif;
    
}

void eepromWrite(int address, uint8_t value)
{
eeprom_write_byte((unsigned char *) address, value);
}

void setup(void)
{
 
  
    //Wait until the serial port is available (useful only for the Leonardo)
    //As the Leonardo board is not reseted every time you open the Serial Monitor
    
/*#if defined (__AVR_ATmega32U4__)
    while(!Serial)
    {}
#endif*/
    
    //If things get really crazy, uncomment this line. It wipes the saved EEPROM information for the Nordic chip. Good to do this if the services.h file gets updated.
    //After it is wiped, comment and reupload.
    //eepromWrite(0, 0xFF);
    
    
    notif.setup();
    notif.set_notification_callback_handle(ancs_notifications);
    notif.set_connect_callback_handle(ancs_connected);
    notif.set_disconnect_callback_handle(ancs_disconnected);
    notif.set_reset_callback_handle(ancs_reset);

    masterSerialPort.begin(9600);
    /*
    Serial.println(F("Arduino setup"));
    Serial.print("    Apple iOS   ");
    Serial.print(" Notifications  ");*/
    //Serial.begin(9600);
    
}



void loop()
{
    notif.ReadNotifications();
    notif.set_notification_callback_handle(ancs_notifications);
}
