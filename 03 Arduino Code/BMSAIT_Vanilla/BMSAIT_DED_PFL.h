 // Display of the DED or the PFL on a 256x64 OLED display
 // inspired by the DEDuino coding by Uri_ba (https://pit.uriba.org/tag/deduino/)
 // V1.3.7 26.09.2021

  #include <U8g2lib.h>
  #include "FalconDEDFont.h"   //load font

// Declare screen Object
  U8G2_SSD1322_NHD_256X64_1_4W_SW_SPI displayDED(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 5, /* dc=*/ 3, /* reset=*/ 4); 

  
// How many seconds should go by before screens turn off after no response recived to the "I'm alive" signal
  #define SLEEP_TIMER 120

// How many milliseconds go before the displays reset after initillizing (for user inspection)
  #define PRE_BOOT_PAUSE 1000
  #define POST_BOOT_PAUSE 2000

unsigned long DED_last_comm = millis();
short Run = 0;

///draw empty display
void ClearDED()
{
  displayDED.firstPage();
  do 
  {
    for (byte line = 0; line < 5; line++ ) 
    {
      displayDED.drawStr(DED_H_CONST, line * DED_CHAR_H + DED_V_CONST, "                        ");
    }
  } while ( displayDED.nextPage() ); 
}

///draw DED data from SharedMem
void RealDED()
{
  displayDED.firstPage();
  do 
  {
    for (byte line = 0; line < 5; line++ ) 
    {
      displayDED.drawStr(DED_H_CONST, line * DED_CHAR_H + DED_V_CONST, datenfeld[line+1].wert);
    }
  } while ( displayDED.nextPage() ); 
}

///draw a test picture 
void TestDED()
{
  displayDED.firstPage();
  do {
      displayDED.drawFrame(0,0,256,64);
      displayDED.drawFrame(64,16,128,32);
      displayDED.drawStr(62+DED_H_CONST, DED_V_CONST+14+DED_CHAR_H , "BMSAIT - DED");       
      displayDED.drawLine(128,0,128,16);
      displayDED.drawLine(128,48,128,64);
      displayDED.drawLine(0,32,64,32);
      displayDED.drawLine(192,32,256,32);
  } while ( displayDED.nextPage() );
}

//setup the OLED
void SetupDED() 
{
  delay(PRE_BOOT_PAUSE); 
  
  displayDED.begin();
  displayDED.setFont(FalconDED);
  displayDED.setFontPosTop();
  TestDED();
  delay(POST_BOOT_PAUSE); 
  ClearDED();
}


///updates the output of the DED on the OLED
void DrawDED(bool mode) 
{
  if (mode)
    {RealDED();}
  else
    {TestDED();}
}


///update the DED
void UpdateDED() 
{ 
  if ((millis()-lastInput)>10000) //if no data was recieved within 10 seconds, shut down display
  {
    if (!debugmode) //in debugmode, display remains on regardless of data transfer status
    {
      ClearDED();
      displayDED.setPowerSave(1);
    }
  }
  else if (datenfeld[0].wert[0]!='T')  //PC is not in 3D
  {
    displayDED.setPowerSave(0);
    DrawDED(false);
  }
  else                                 //PC is in 3D
  {
    displayDED.setPowerSave(0);
    DrawDED(true);
  } 
}
