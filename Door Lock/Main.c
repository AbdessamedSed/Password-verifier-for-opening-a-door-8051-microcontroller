// embedded system to control a door in 8051 microncontroller

#include <reg51.h>


//Keypad Rows Pins
sbit keyRow1 = P2^0;
sbit keyRow2 = P2^1;
sbit keyRow3 = P2^2;
sbit keyRow4 = P2^3;

//Keypad Columns Pins
sbit keyColumn1 = P3^0;
sbit keyColumn2 = P3^1;
sbit keyColumn3 = P3^2;

//Motor Pins
sbit motorPin1 = P3^3;
sbit motorPin2 = P3^4;

//Led Pins
sbit RS = P3^5;
sbit RW = P3^6;
sbit EN = P3^7;

int boolean = 0;

/* Functions */
void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_DISPLAY(unsigned char *str);
char keypadValue();
void Check();
void Delay(unsigned int);
unsigned char Pin[] = {"12345"};
unsigned char InPin[5];

//Main
void main()
{
	unsigned int i = 0;
	
	LCD_INIT();
	
	while(1)
	{
		LCD_CMD(0x80);	//force cursor to begining of 1st row
		LCD_DISPLAY("ENTER PASSWORD");
		Delay(1000);
		LCD_CMD(0xC0);	//force cursor to begining of 2nd row
		
		while(Pin[i] != '\0')
		{
			InPin[i] = keypadValue();	//read the passwored character by character
			Delay(1000);
			i++;
		}
		
		Check();
		
	}
	
	
	
}

//LCD initializing funtion
void LCD_INIT(void)
{
	Delay(100);
	LCD_CMD(0x38);	// 	2 lines and 5×7 matrix
	LCD_CMD(0x0E);	// Display ON, cursor blinking
	LCD_CMD(0x01);	// Clear display screen
}

//Lcd commands function
void LCD_CMD(unsigned char x)
{
	P1 = x;
	RS = 0;	// command mode
	RW = 0;	// read
	EN = 1;
	Delay(1000);
	EN = 0;
	return;
}

//LCD displaynig data function
void LCD_DISPLAY(unsigned char *str)
{
    int k;
    for (k = 0; str[k] != '\0'; str++)
    {
        LCD_DATA(str[k]);
    }
    Delay(10000);
}

//LCD receiving data function
void LCD_DATA(unsigned char w)
{
	P1 = w;
	RS = 1;	// data mode
	RW = 0;	// read
	EN = 1;
	Delay(1000);
	EN = 0;
	return;
		
}

void Delay(unsigned int i)
{
    int a, b;
    for (a = 0; a < i; a++)
    {
        for (b = 0; b < 10; b++);
    }
}

//Getting keypad character value function
char keypadValue()
{
	int x = 0;
	while(x == 0)
	{
		
		//get values for first row
		keyRow1 = 0;
		keyRow2 = 1;
		keyRow3 = 1;
		keyRow4 = 1;
		
		if(keyColumn1 == 0)
		{
			LCD_DATA('*');
			Delay(1000);
			x = 1;
			return '1';
		}
		if(keyColumn2 == 0)
		{
			LCD_DATA('*');
			Delay(1000);
			x = 1;
			return '2';
		}
		if(keyColumn3 == 0)
		{
			LCD_DATA('*');
			Delay(1000);
			x = 1;
			return '3';
		}
	
	//get values for second row
		keyRow1 = 1;
		keyRow2 = 0;
		keyRow3 = 1;
		keyRow4 = 1;
	
		if(keyColumn1 == 0)
		{
			LCD_DATA('*');
			Delay(1000);
			x = 1;
			return '4';
		}
		if(keyColumn2 == 0)
		{
			LCD_DATA('*');
			Delay(1000);
			x = 1;
			return '5';
		}
		if(keyColumn3 == 0)
		{
			LCD_DATA('*');
			Delay(1000);
			x = 1;
			return '6';
		}

	//get values for third row
		keyRow1 = 1;
		keyRow2 = 1;
		keyRow3 = 0;
		keyRow4 = 1;
	
		if(keyColumn1 == 0)
		{
			LCD_DATA('*');
			Delay(1000);
			x = 1;
			return '7';
		}
		if(keyColumn2 == 0)
		{
			LCD_DATA('*');
			Delay(1000);
			x = 1;
			return '8';
		}
		if(keyColumn3 == 0)
		{
			LCD_DATA('*');
			Delay(1000);
			x = 1;
			return '9';
		}
	
	//get values for forth row
		keyRow1 = 1;
		keyRow2 = 1;
		keyRow3 = 1;
		keyRow4 = 0;
	
		if(keyColumn1 == 0)
		{
			LCD_DATA('*');
			Delay(1000);
			x = 1;
			return '*';
		}
		if(keyColumn2 == 0)
		{
			LCD_DATA('*');
			Delay(1000);
			x = 1;
			return '0';
		}
		if(keyColumn3 == 0)
		{
			LCD_DATA('*');
			Delay(1000);
			x = 1;
			return '#';
		}
	}
	//end while
}

//Password check function and run the door motor

void Check()
{
	//compare the input with the assign password value
	
	if(Pin[0] == InPin[0] && Pin[1] == InPin[1] && Pin[2] == InPin[2] && Pin[3] == InPin[3] && Pin[4] == InPin[4])
	{
		Delay(1000);
		LCD_CMD(0x01);	// clear display screen
		LCD_CMD(0x80);	// shift the entire display to the left
		// show input is correct
		LCD_DISPLAY("CORRECT PASSWORD");
		Delay(1000);
		// motor will run
		motorPin1 = 1;
		motorPin2 = 0;
		// show the door is opened
		LCD_CMD(0x01);	// clear display screen
		LCD_CMD(0x80);	// shift the entire display to the left
		LCD_DISPLAY("DOOR OPENED");
		Delay(10000);
		motorPin1 = 1;
		motorPin2 = 0;
		LCD_CMD(0x01);	// clear display screen
	}
	
	else
	{
		LCD_CMD(0x01);	// clear display screen
		LCD_CMD(0x18);	// shift the entire display to the left
		// show input is wrong
		LCD_DISPLAY(" WRONG PASSWORD");
		Delay(1000);
		// show the door is still closed
		LCD_CMD(0x01);	// clear display screen
		LCD_CMD(0x18);	// shift the entire display to the left
		LCD_DISPLAY(" DOOR STILL CLOSED");
		Delay(10000);
		LCD_CMD(0x01);	// clear display screen
	}
	
	boolean = 1;
	
}