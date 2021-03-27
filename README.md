# DAF 2020 TERMINAL -keyboard Arduino adaptation
DAF TERMINAL Keyboard USB connection to PC with arduino pro micro (Leonardo)

The DAF 2020 was a Romanian Computer Terminal, with graphic dispay and a qwerty keyboard.
This project is for converting the old keyboard to modern usb conection.
Similar projects can be made for any old keyboard: Commodore 64, Amiga, ZX spectrum etc;

The keyboard uses 4 lines as input and 6 lines as output.
The 4 output lines are conected to bcd to binary IC's, to get the needed 16 output lines;
The 4 lines are counting up in binary to 16, as the keyboard has 16 rows; After each count a clock signal is sent to update the latch. 
In the case of the DAF, the latch is a 4 bit shift register 495E, made in romania by the IPRS factory in bucharest. 
The 6 input lines are  for each row;
You send a LOW signal to the output and check the input lines, if you sent the numbber 0001 and read input line 2 and got a low signal, the P key is pressed.
If you need more help contact me elekeskaroly@gmail.com


To read the keyboard capslock and numlock status leds you need to update 4 files on your computer.
COPY paste and overwrite original files.
But make backup copys first! 

Path for HID files:
 C:\Users\ * find your username  \AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.3\libraries\HID\src

Path for keyboard files:
C:\Program Files (x86)\Arduino\libraries\Keyboard\src

This program is as it is. I'm not a programmer, just a hobbyist. Use it at your own risk.
(it works fine for me, but it may not be working for you)
