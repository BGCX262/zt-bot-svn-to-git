// X2 Test Program
//  Last Updated 05/16/07


#include <avr/io.h>
#include "LCD.h"
#include "SPI.h"
#include "BasicControl.h"


#define BUTTON1			( 1 << PC1 )
#define BUTTON4			( 1 << PC4 )
#define BUTTON6			( 1 << PC6 )
#define BUTTONS			( BUTTON1 | BUTTON4 | BUTTON6 )



#define checkForButton()		( PINC & BUTTONS )



// display X2 splashscreen
void displaySplashscreen()
{
	LCDString( "       Pololu" );

	LCDMoveCursor( LCD_ROW_3 );		// move cursor to start of bottom row
	unsigned char vMajor, vMinor;
	getFirmwareVersion( &vMajor, &vMinor );
	LCDAddString("version ");
	LCDHex( vMajor );
	LCDChar( '.' );
	LCDHex( vMinor );

	delay_ms( 400 );
	LCDMoveCursor( LCD_ROW_1 );		// move cursor to start of second row
	char *str = "O r a n g u t a n X2";
	unsigned char i = 0;
	while ( str[ i ] != 0 )
	{
		LCDChar( str[ i ] );
		playNote( str[ i ], 50 );
		delay_ms( 15 );
		i++;
	}

	delay_ms(900);
}



void motorsTest(void)
{
	LCDString( "speed = trimpot 0x" );	

	ADMUX = 0x27;			// bit 7 and 6 clear: voltage ref is Vref pin
							// bit 5 set: left-adjust result (only need ADCH)
							// bit 4 not implemented
							// bits 0-3: ADC channel (channel 7)

	while ( !checkForButton() ) 		// stay here until button is pressed
	{
		ADCSRA |= ( 1 << ADSC );			// start conversion
		while ( ADCSRA & ( 1 << ADSC ));	// wait for conversion to finish
		unsigned char speed = ADCH;
		LCDAddString( "Speed: " );
		LCDMoveCursor( LCD_ROW_3 );
		LCDAddString( "Speed: " );
		LCDHex( speed );
	
		
		setSpeed(255);
        delay_ms(6000);
		sing();
		setSpeed2(200,100);
		delay_ms(1000);
		sing();
		setSpeed(100);
        delay_ms(6000);
	    setSpeed2(100,200);
		sing();
		delay_ms(1000);
		setSpeed(-100);
        delay_ms(6000);
		sing();
		setSpeed(-255);
        delay_ms(6000);
		setSpeed2(50,200);
		delay_ms(6000);


		//LCDHex( getM1Current() );
	
		//LCDHex( getM2Current() );
		//LCDMoveCursor( LCD_ROW_0 + 18 );// move cursor to top row, column 18
										//  (just after "speed = trimpot 0x")
	//	setMotor1( speed - 128 );
	//	setMotor2( speed - 128 );		

		delay_ms(10);
	}
	brakeLowMotor1( 0 );
	brakeLowMotor2( 0 );
}


int setSpeed(int s)
{
	
brakeHighMotor2( 0 );
brakeHighMotor1( 0 );
setMotor1( s );
setMotor2( s );
LCDMoveCursor( LCD_ROW_0 );
LCDString("Speed: ");
LCDMoveCursor( LCD_ROW_1 );
LCDHex(s);
}

void setSpeed2(int s1, int s2)
{
brakeHighMotor2( 0 );
brakeHighMotor1( 0 );
setMotor1( s1 );
setMotor2( s2 );
LCDMoveCursor( LCD_ROW_0 );
LCDString("Speed: ");
LCDMoveCursor( LCD_ROW_1 );
LCDHex(s1);
}


void turnRight(int s)
{
brakeHighMotor2( 0 );
brakeHighMotor1( 0 );
setMotor1( s );
setMotor2( -s );
delay_ms(1000);
}

void sing()
{
 playNote( A(4) +5, 1000 );
		delay_ms( 100 );
		playNote( A(4) +5, 1000 );
		delay_ms( 100 );
		playNote( A(4) +7, 1000 );
		delay_ms( 100 );
		playNote( A(4) +3, 1000 );
		delay_ms( 100 );
		playNote( A(4) +9, 1000 );
		delay_ms( 1000 );
		playNote( A(4) +3, 1000 );
		delay_ms( 300 );
		playNote( A(4) +1, 1000 );
		delay_ms( 600 );
		playNote( A(4) +8, 1000 );
		delay_ms( 1000 );
		playNote( A(4) +2, 1000 );
		playNote( A(4) +5, 1000 );
		playNote( A(4) +2, 1000 );
}

// Enable pullups on pins A and D, and display pin values.
//  Pins should all read high unless they are externally pulled low
//  (e.g. by connecting them to ground).
void portsTest()
{
	PORTA = 0xFF;						// enable pullups on A and D pins
	PORTD = 0xFF;

	delay_ms( 10 );

	unsigned char pind = PIND;
	unsigned char pina = PINA;

	LCDString( "  PORTA:    PORTD:   " );
    
    PIND = 0x80;
    LCDAddString( "  " );
    LCDBinary( PIND );
	delay_ms(1000);
	PIND = 0x0;


	while ( !checkForButton() )			// stay here until button is pressed
	{
		LCDBinary( PINA );				// display pin values
		LCDAddString( "  " );
  		LCDBinary( PIND );
        
		
		/*
	    playNote( A(4) +5, 1000 );
		delay_ms( 100 );
		playNote( A(4) +5, 1000 );
		delay_ms( 100 );
		playNote( A(4) +7, 1000 );
		delay_ms( 100 );
		playNote( A(4) +3, 1000 );
		delay_ms( 100 );
		playNote( A(4) +9, 1000 );
		delay_ms( 1000 );
		playNote( A(4) +3, 1000 );
		delay_ms( 300 );
		playNote( A(4) +1, 1000 );
		delay_ms( 600 );
		playNote( A(4) +8, 1000 );
		delay_ms( 1000 );
		playNote( A(4) +2, 1000 );
		playNote( A(4) +5, 1000 );
		playNote( A(4) +2, 1000 );
        */
		// if the pins have changed, play a note based on the changed pin
		if ( PIND != pind )
		{
			pind = PIND;

			if ( !( pind & 0x80 ))
				playNote( A(4), 1000 );
			else if ( !( pind & 0x40 ))
				playNote( A(4) + 1, 1000 );
			else if ( !( pind & 0x20 ))
				playNote( A(4) + 2, 1000 );
			else if ( !( pind & 0x10 ))
				playNote( A(4) + 3, 1000 );
			else if ( !( pind & 0x08 ))
				playNote( A(4) + 4, 1000 );
			else if ( !( pind & 0x04 ))
				playNote( A(4) + 5, 100 );
			else if ( !( pind & 0x02 ))
				playNote( A(4) + 6, 100 );
			else if ( !( pind & 0x01 ))
				playNote( A(4) + 7, 100 );
		}
		else if ( PINA != pina )
		{
			pina = PINA;

			if ( !( pina & 0x20 ))
				playNote( A(5) + 2, 100 );
			else if ( !( pina & 0x10 ))
				playNote( A(5) + 3, 100 );
			else if ( !( pina & 0x08 ))
				playNote( A(5) + 4, 100 );
			else if ( !( pina & 0x04 ))
				playNote( A(5) + 5, 100 );
			else if ( !( pina & 0x02 ))
				playNote( A(5) + 6, 100 );
			else if ( !( pina & 0x01 ))
				playNote( A(5) + 7, 100 );
		}

		delay_ms( 10 );

		LCDMoveCursor( LCD_ROW_2 + 1 );	// move cursor to third row, column 1
	}

	PORTA = 0;							// disable pullups on A and D pins
	PORTD = 0;
}


void firstTest ()
{
   #define FRONT_SENSOR_ONE    0x7F
   #define FRONT_SENSOR_TWO    0xBF
   #define BACK_SENSOR_ONE     0xDF
   #define BACK_SENSOR_TWO     0xEF    

   unsigned char pind = PIND;
   unsigned char pina = PINA;

   driveForward (255);
   while (1)
   {
   
      if (PIND == FRONT_SENSOR_ONE || PIND == FRONT_SENSOR_TWO)
      {
         driveBackward(255); 
      }
	  else if (PIND == BACK_SENSOR_ONE || PIND == BACK_SENSOR_TWO)
	  {
         driveForward(255);
	  }

	  delay_ms(20);
   
   
   }
   
   
   
   /*
   driveForward (255);
   turnRight90Degree();
   driveForward (255);
   turnLeft90Degree ();
   driveForward (255);
   driveBackward (255);
   driveBackward (255);
   brake ();
   driveForward (255);
   driveForward (255);
   brake ();
   */

}


int main()
{
	SPIInit();			// allows the mega644 to send commands to the mega168
	LCDInit();

	DDRC |= ~BUTTONS;
	PORTC |= ~BUTTONS;

	// initialize ADC
	ADCSRA = 0x87;		// bit 7 set: ADC enabled
						// bit 6 clear: don't start conversion
						// bit 5 clear: disable autotrigger
						// bit 4: ADC interrupt flag
						// bit 3 clear: disable ADC interrupt
						// bits 0-2 set: ADC clock prescaler is 128

	while ( 1 )
	{
		displaySplashscreen();

		// display test options and system voltage
		LCDString("weeeeeee");
		LCDMoveCursor( LCD_ROW_1 );
		LCDAddString("All your bases are belong to us!!  ");


		// setup the ADC to perform conversion on system voltage
		ADMUX = 0x26;		// bit 7 and 6 clear: voltage ref is Vref pin
							// bit 5 set: left-adjust result (only need ADCH)
							// bit 4 not implemented
							// bits 0-3: ADC channel (channel 6)

		// while waiting for button press, continuously perform ADC conversions
		while ( !checkForButton() ) 
		{
			ADCSRA |= ( 1 << ADSC );			// start conversion
			while ( ADCSRA & ( 1 << ADSC ));	// wait while converting
			LCDMoveCursorLeft();				// move cursor left one
			LCDMoveCursorLeft();				// move cursor left one
			LCDHex( ADCH );						// display conversion result
		}

		while ( 1 )
		{
			unsigned char button = checkForButton();
			delay_ms( 2 );						// let button finish bouncing
			while ( checkForButton() );			// wait while button held down
			delay_ms( 2 );						// let button finish bouncing

			if ( button == BUTTON1 )
				firstTest();

			if ( button == BUTTON4 )
				motorsTest();

			else if ( button == BUTTON6 )
				portsTest();

			while ( !checkForButton() );		// wait for button press
		}
    }

    return 0;
}

