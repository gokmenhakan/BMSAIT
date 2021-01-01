// Version: 1.2    29.10.20

//MODULE SELECTION - uncomment the modules you want to use.
//#define LED               //drive LEDs
//#define LEDMatrix         //drive LED Matrix using a MAX7219 controller
//#define LCD               //drive LCD display
//#define SSegMAX7219       //drive 7-Segment displays via MAX7219 controller
//#define SSegTM1637        //drive 7-Segment displays via TM1367 controller
//#define ServoMotor        //drive servo motors directly connected to the arduino
//#define ServoPWM          //drive multiple servo motors via pwm shield
//#define StepperBYJ        //drive stepper motor 28BYJ-48
//#define StepperX27        //drive stepper motor X27.168
//#define StepperVID        //drive multiple stepper motors X25.168 with a VID66-06 controller
//#define MotorPoti         //motor-driven poti control
#define DED_PFL           //Enable DED or PFL on an 254x64 OLED display 
//#define SpeedBrake        //Enable display of the SpeedBrake indicator on an 128x64 OLED display
//#define Switches          //use the arduino to read switch positions and send keyboard commands
//#define ButtonMatrix      //use the arduino to read switch positions and send keyboard commands
//#define RotEncoder        //use the arduino to read rotary encoders and send keyboard commands
//#define AnalogAxis        //use the arduino to read analog resistors and sync this with a gamecontroller axis
//#define NewDevice         //placeholder. Use this line to activate your own code to drive other, specific hardware

//End if device definitions

    

//Basic program definitions

  #define POLLTIME 50             // set time between PULL data requests
  //#define PRIORITIZE_OUTPUT     //uncomment this to put a stress on fast update of outputs (should be used for motors to allow smoother movements)
  //#define PRIORITIZE_INPUT      //uncomment this to put a stress on fast er poll of inputs (switches/Buttons) 
  const char ID[]= "BMSAIT_DED";  //Set the ID for this arduino program. Use any string. The program will use this ID to check in with the BMSAIT windows application
  
//BOARD SELECTION

  #define UNO         //uncomment this if this sketch will be loaded on an UNO
  //#define NANO        //uncomment this if this sketch will be loaded on an NANO
  //#define MICRO       //uncomment this if this sketch will be loaded on an MICRO
  //#define LEONARDO    //uncomment this if this sketch will be loaded on an LEONARDO
  //#define MEGA        //uncomment this if this sketch will be loaded on an MEGA
  //#define DUE         //uncomment this if this sketch will be loaded on an DUE

// This is the most important part of this sketch. You need to set the data that the Arduino will have to handle
// Make sure that you chose the definition of VARIABLENANZAHL matches the number of entries in this table
// Fill data as follows: 
// 1. Short description (max 5 characters)
// 2. Flightdata ID (check BMSAIT Variablen.csv)  as a 4-digit string (needed for PULL mode)
// 3. data type (check BMSAIT Variablen.csv: b=bool, y=byte, 1=byte[], i=integer, f=float, s=string, 2=string[]))  (needed for PULL mode)
// 4. Output type (10-LED, 20-LCD, 30-MAX7219, 31-TM1637, 40-Servo, 41-ServoPWM, 50-Stepper 28BYJ, 51-Stepper X27-168, 52-StepperBoard VID6606, 60-MotorPoti)
/* mod
// 5. Reference1 - i.e.  Output PIN of LEDs, the line on LCD displays or a link to an entry in container in motor modules
// 6. Reference2 - i.e. number of characters to display (control display length on 7-segment or LCD displays)
// 7. Reference3 - i.e. start position (control position of data on 7-segment or LCD displays) 
// 8. Reference4 - i.e. decimal point (will add a decimal point on 7-segment displays after the given position)
// 9. Reference5 - i.e. decimal point (will add a decimal point on 7-segment displays after the given position)
mod */
// 10. Initial value as string (i.e. "00")

Datenfeld datenfeld[]=
  {
    //Description ID    DT    OT    IV
     {"DED1v",  "0235", 's',  70,     ""}            //DED Line 1 vorn
    ,{"DED2v",  "0236", 's',  70,     ""}            //DED Line 2 vorn
    ,{"DED3v",  "0237", 's',  70,     "      DED"}   //DED Line 3 vorn
    ,{"DED4v",  "0238", 's',  70,     ""}            //DED Line 4 vorn
    ,{"DED5v",  "0239", 's',  70,     ""}            //DED Line 5 vorn
    ,{"DED1h",  "0240", 's',  70,     ""}            //DED Line 1 hinten
    ,{"DED2h",  "0241", 's',  70,     ""}            //DED Line 2 hinten 
    ,{"DED3h",  "0242", 's',  70,     " READY"}      //DED Line 3 hinten
    ,{"DED4h",  "0243", 's',  70,     ""}            //DED Line 4 hinten
    ,{"DED5h",  "0244", 's',  70,     ""}            //DED Line 5 hinten
    ,{"MPWR",   "1260", 'i',   0,     "1"}           // a/c power status (0-off , 1-battery, 2-generators)
  }; 
const byte VARIABLENANZAHL = sizeof(datenfeld)/sizeof(datenfeld[0]); 
