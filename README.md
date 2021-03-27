# DAF 2020 TERMINA -keyboard Arduino adaptation
DAF TERMINAL Keyboard USB connection to PC with arduino pro micro (Leonardo)

The DAF 2020 was a Romanian Computer Terminal, with graphic dispay and a qwerty keyboard.
This project is for converting the old keyboard to modern usb conection.
Similar projects can be made for any old keyboard: Commodore 64, Amiga, ZX spectrum etc;

The keyboard uses 4 lines as input and 6 lines as output.
The 4 lines are counting up in binary to 16, as the keyboard has 16 rows;
The 6 input lines are  for each row;
You send a LOW signal to the output and check the input lines, if you sent the numbber 0001 and read input line 2 and got a low signal, the P key is pressed.
If you need more help contact me elekeskaroly@gmail.com
