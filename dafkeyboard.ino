//DAF 2020 ROMANIAN TERMINAL KEYBOARD TO ARDUINO PRO MICRO
//USB KEYBOARD
//MADE by: Elekes Károly in 2021
//MADE PUBLIC UNDER GPL LICENSE
//For keyboard status led function to work you need to update the keyboard.h and HID.h


#include "Keys.h"
#define capslock_led A0
#define line_led A3
#define busy_led A1
#define local_led A2
#define CLOCK_PIN 15 //15 UNO 13
#define Keyboard_delay 100

boolean capslock = false;
boolean oldcapslock = false;
boolean numlock=false;
boolean oldnumlock=false;

boolean shift = false;
boolean oldshift = false;
boolean ctrl = false;
boolean oldctrl = false;
boolean cmode=false;
boolean nmode=false;
boolean keychanged;
boolean pressed=0;

const byte inputpins[7] = {2, 4, 5, 6, 7, 8, 14}; //PRO: 2,4,5,6,7,8,14  UNO 2, 4, 5, 6, 7, 8, 12;
const byte outputpins[4] ={3, 9, 10, 16};         //PRO: 3,9,10,16       UNO 3, 9, 10, 11;
byte keystatus[16];
byte oldkeystatus[16];
Keys key[16][6] {};

void setup() {

/******KEY MAPPING******/

key[0][1].c='q';
key[0][2].c=0xB1; //esc
key[0][3].c='1';
key[0][4].c=0xC1; //Caps lock

key[1][1].c='p';
key[2][1].c='t';
key[3][1].c='\344';
key[4][1].c='e';
key[5][1].c=']';
key[6][1].c='u';
key[7][1].c= '\346';
key[9][1].c='[';
key[8][1].c='w';
key[10][1].c='y';
key[11][1].c='\345';
key[12][1].c='r';
key[13][1].c='o';
key[14][1].c='i';
key[15][1].c=',';

key[1][2].c=0xD8; //down
key[2][2].c=0xC2; //F1
key[3][2].c='\333' ;
key[4][2].c='`'; //-->
key[5][2].c= '\353';
key[6][2].c=0xB3; //TAB
key[7][2].c=0xC5; //F4
key[8][2].c=0x27; //-->
key[9][2].c=0xD7; //-->
key[10][2].c=0xC3;; //F2
key[12][2].c=0x7C; //-->
key[13][2].c=0xDA; //up
key[14][2].c=0xD9; //<--

key[1][3].c='0';
key[2][3].c='5';
key[3][3].c=0xB2; //backspace
key[4][3].c='3';
key[5][3].c='=';
key[6][3].c='7';
key[7][3].c='\350';
key[8][3].c='2';
key[9][3].c='-';
key[10][3].c='6';
key[11][3].c='\347';
key[12][3].c='4';
key[13][3].c='9';
key[14][3].c='8';
key[15][3].c='\351';

key[ 1][4].c=',';
key[ 2][4].c='v';
key[ 3][4].c=0x82; //Alt
key[ 4][4].c='x';
key[ 5][4].c='/';
key[ 6][4].c=' ';
key[ 7][4].c=0xD4; //Del
key[ 8][4].c='z';
key[ 9][4].c='.';
key[10][4].c='b';
key[11][4].c='\352' ;
key[12][4].c='c';
key[13][4].c='m';
key[14][4].c='n';
key[15][4].c='\340'  ;

key[ 1][5].c='l';
key[ 2][5].c='f';
key[ 3][5].c=0xB0; //RETURN
key[ 4][5].c='s';
key[ 5][5].c='\\';
key[ 6][5].c='h';
key[ 7][5].c='\342';
key[ 8][5].c='a';
key[ 9][5].c=';';
key[10][5].c='g';
key[11][5].c='\341';
key[12][5].c='d';
key[13][5].c='k';
key[14][5].c='j';
key[15][5].c='\343' ;

//Set input pins
  for (int i = 0; i < 7; i++) {
  pinMode(inputpins[i], INPUT);}
//Set output pins  
// Used to counting in binary from 00 to 16
  for (int i = 0; i < 4; i++) {
  pinMode(outputpins[i], OUTPUT);}
  
//Clock pin for binary counter pins output clock
  pinMode(CLOCK_PIN, OUTPUT);

// Keyboard led pins   
  pinMode(capslock_led, OUTPUT);
  pinMode(line_led, OUTPUT);
  pinMode(busy_led, OUTPUT);
  pinMode(local_led, OUTPUT);
 
  Keyboard.begin();
    capslock=Keyboard.getLedStatus(LED_CAPS_LOCK);
    numlock=Keyboard.getLedStatus(LED_NUM_LOCK);
    oldnumlock=numlock;
    oldcapslock=capslock;
        if (capslock) digitalWrite(capslock_led, LOW);
        if (numlock) digitalWrite(line_led, LOW);
  Keyboard.end();  
  
   for (int i=0;i<16;i++) {
   keystatus[i]=0b11111111;
   oldkeystatus[i]=keystatus[i];
    } 

   initpins(); //just some random led blinking on the power up
}

void loop() {


 for (int i = 0; i < 16; i++) {
    send_mode(i);                       // Sending out a binary counter signal on 4 pins
    pulse_clock(0.01);                  // Sendig the clock signal after the binary counter pins are all set
    byte s =0b11111111;                 // preparing the reading byte variable 

/* Start reading the input lines*/

 for (int j = 0; j < 7; j++) {if (digitalRead(inputpins[j]) == 0) bitWrite(s,j,0); else bitWrite(s,j,1);}
        keystatus[i] = s;
        if (bitRead(s,0)==0) shift=true;
        if (bitRead(s,0)==1) shift=false;
        if (bitRead(s,6)==0) ctrl=true;
        if (bitRead(s,6)==1) ctrl=false;
        if ((i==0)&&bitRead(s,4)==0) capslock=true;
        if ((i==0)&&bitRead(s,4)==1) capslock=false;
        if ((i==3)&&bitRead(s,2)==0) numlock=true;
        if ((i==3)&&bitRead(s,2)==1) numlock=false;
        if ((i==15)&&bitRead(s,2)==0) {Keyboard.begin();Keyboard.releaseAll();Keyboard.end();}
     
   }



Keyboard.begin();
 if (Keyboard.getLedStatus(LED_CAPS_LOCK)) digitalWrite(capslock_led, LOW); else digitalWrite(capslock_led, HIGH);;
 if (Keyboard.getLedStatus(LED_NUM_LOCK)) digitalWrite(line_led, LOW); else digitalWrite(line_led, HIGH);
Keyboard.end();


if (numlock!=oldnumlock) {
    if (!numlock==true)  numLock();
 oldnumlock=numlock; 
  }

if (shift!=oldshift) {
    Keyboard.begin();
    
    if (shift==true)  Keyboard.press(0x85); 
                 else Keyboard.release(0x85);
                 oldshift=shift; 
    Keyboard.end();}

if (ctrl!=oldctrl)  {
    Keyboard.begin();
    if (ctrl) {Keyboard.press(0x80);
               digitalWrite(local_led, LOW);}
         else {Keyboard.release(0x80);digitalWrite(local_led, HIGH);}
      oldctrl=ctrl; 
    Keyboard.end();}


if (capslock!=oldcapslock)  {
 if (!capslock) capsLock();
     oldcapslock=capslock;}

  
  for (int i=0;i<16;i++) {
  if (keystatus[i]!=oldkeystatus[i]) {
                   for (int j=1;j<6;j++) {
                   int a= bitRead(keystatus[i],j); 
                   int b= bitRead(oldkeystatus[i],j);

                if (a!=b) {
                            pressed=!a;
                            if (pressed) {key[i][j].sendpress();digitalWrite(busy_led, LOW);}
                            else         {key[i][j].sendrelease();digitalWrite(busy_led,HIGH);}
                          }   
                   }
    oldkeystatus[i]=keystatus[i];
    } 
   }
}

void pulse_clock(float t)
{
  digitalWrite(CLOCK_PIN, HIGH);
  delay(t);
  digitalWrite(CLOCK_PIN, LOW);
}
void send_mode(int a)
{
  for (int i=0;i<4;i++)
  digitalWrite(outputpins[i], bitRead(a, i));
 }

void capsLock()
{
  cmode=!cmode;
  if (cmode)  digitalWrite(capslock_led, LOW);
  if (!cmode) digitalWrite(capslock_led, HIGH);
 }

void numLock()
{
  nmode=!nmode;
  if (nmode)  digitalWrite(line_led, LOW);
  if (!nmode) digitalWrite(line_led, HIGH);
 }

void initpins() {
  digitalWrite(capslock_led, LOW);
  digitalWrite(line_led, HIGH);
  digitalWrite(busy_led, HIGH);
  digitalWrite(CLOCK_PIN, LOW);
  for (int i = 0; i < 2; i++) {
    digitalWrite(line_led, LOW);
    digitalWrite(local_led, LOW);
    digitalWrite(busy_led, LOW);
    delay(200);
    digitalWrite(capslock_led, HIGH);
    digitalWrite(line_led, HIGH);
    digitalWrite(local_led, HIGH);
    digitalWrite(busy_led, HIGH);
    delay(200);
  }
  
}
