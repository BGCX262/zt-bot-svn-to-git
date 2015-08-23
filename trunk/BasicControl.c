#include <avr/io.h>
#include "LCD.h"
#include "SPI.h"


#define MAX_ENGINE_POS_OUTPUT   255
#define MAX_ENGINE_NEG_OUTPUT   -255


static int setSpeed(int rightWheels, int leftWheels)
{
   brakeHighMotor2( 0 );
   brakeHighMotor1( 0 );
   setMotor1( rightWheels );
   setMotor2( leftWheels );
}

int turnRight90Degree( void )
{
   /* Set rightWheel to negative and leftWheel to positive for fast right turn*/
   /*add timer*/
   LCDAddString( " Turn Right" );
   LCDMoveCursor( LCD_ROW_0 );
   setSpeed( MAX_ENGINE_NEG_OUTPUT, MAX_ENGINE_POS_OUTPUT);
}

int turnLeft90Degree ( void)
{
   LCDAddString( " Turn Left" );
   LCDMoveCursor( LCD_ROW_0 );
   setSpeed( MAX_ENGINE_POS_OUTPUT, MAX_ENGINE_NEG_OUTPUT);
}

int driveForward ( int speed )
{
   LCDAddString( " Drive Straight" );
   LCDMoveCursor( LCD_ROW_0 );
   if (speed > 0)
      setSpeed( speed, speed);
}

int driveBackward ( int speed )
{
   LCDAddString( " Drive Backward" );
   LCDMoveCursor( LCD_ROW_0 );
   if (speed < 0)
      setSpeed( speed, speed);
}

int brake ( void )
{
   LCDAddString( " Breaking" );
   LCDMoveCursor( LCD_ROW_0 );
   setSpeed( 0, 0);
}


