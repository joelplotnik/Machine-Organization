// ledLights.c
// Red light blinks when the bit is 1. Green light blinks when the bit is 0.

#include <wiringPi.h>
#include <stdio.h>

void ledLights(unsigned int bit)
{
	wiringPiSetup();
	//ensuring both LED's are off
	digitalWrite(0, HIGH);
	digitalWrite(1, HIGH);

	if(bit != 0)
	{
		//blink red
		pinMode(0, OUTPUT); // 0 = gpio17
        digitalWrite(0, LOW);   //led on
        delay(50);   // wait 5 sec
        digitalWrite(0, HIGH);  //led off
		delay(50);
	}
	else if(bit == 0)
	{
        //blink green
        pinMode(1, OUTPUT); // 1 = gpio18
        digitalWrite(1, LOW);   //led on
        delay(50);   // wait 5 sec
        digitalWrite(1, HIGH);  //led off
		delay(50);
	}

}

