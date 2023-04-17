# Password-verifier-for-opening-a-door-8051-microcontroller
embedded system using 8051 microcontroller to lock a door for safety reasons

In the program first we import the 8051-family header file which contain all the necessary classes. Then we assign every connected pin to the variables. In keypad we assign variable as keyrow1 to keyrows4 for keypad rows and keycolumn1 to keycolumn3 for keypad columns. Then we connected the motor pins and lcd pins in the variable called motor pins and rs, rw and en.

After assign all the connected pins to the variables. We declare functions for every single task. The main function calls the other functions for execute the program.

Delay function is used for delay the program execution for few seconds. It helps us to execute the program smoothly. We delay the execution for only 1000ms = 1secs.

The lcdcmd function is help us to control the lcd. It will control the current flow for the lcd screen and also help to perform Read/Write Operation. The lcddat function control the lcd data pins. In the LCD there is total 8 pins D0 to D7 Pins used to send Command or data to the LCD.

The lcddisplay function is used for display user input characters and also assign the values for every keypad character values. First, we select a single keypad row and assign the values for the key. Also encoded with the asterisk (*) character, for pin protection.

The check function is used for compare the user input with the assign password number. If the user input match the assign password, it will show the “pin correct” message and give the signal to run the lock motor. After lock motor will run, again it will show the “door open” message. On the other hand, if the user input password is wrong, it will show the “wrong pin” message. Then it will delay few second and give another chance to input the password again.

The main function is the mother function of the program. Main function will call other function in other to perform the task. At first it will call the lcdcmd function to control the lcd, then it will call the lcddisplay function for display the messages in the lcd screen. It will delay for few seconds. After that it will run loop until the correct pin enter. To check the password is correct it will call check function, then execute the program.

To simulate the program circuit, we use the proteus simulation. All the code is written in embedded C code, which is not directly executed by the 8051 microcontrollers. To run the program first we need to build the program and convert the program in hex file. The hex file is supported by the 8051 microcontrollers. Every 8051 controller has a clock frequency for perform the task. To run the program, we use 11.0592 MHZ clock frequency. It will run the simulation smoothly without any kind of errors.
