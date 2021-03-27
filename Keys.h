//DAF 2020 ROMANIAN TERMINAL KEYBOARD TO ARDUINO PRO MICRO
//USB KEYBOARD
//MADE by: Elekes Károly in 2021
//MADE PUBLIC UNDER GPL LICENSE
//For keyboard status led function to work you need to update the keyboard.h and HID.h

#include "Keyboard.h"
class Keys
{
  private: 
   
  public:
  
  uint8_t c;
   
  Keys(){ }
  
  void sendpress()
   {
      Keyboard.begin();
      Keyboard.press(c);delay(5);
      Keyboard.end();
    };
    
  void sendrelease()
  {
    Keyboard.begin();
    Keyboard.release(c);
    Keyboard.end();
     
    }
};
