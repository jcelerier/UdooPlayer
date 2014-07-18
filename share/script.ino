#include <stdlib.h>
#include <string.h>
#include <stdio.h>
unsigned char PadNote[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
unsigned char status;
int PadCutOff[16] = {100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};
int MaxPlayTime[16] = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
#define  midichannel 0;
boolean activePad[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int PinPlayTime[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
boolean VelocityFlag  = true;
int analogPin[2] = {A0,A1};
int hitavg[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int pad = 0;
int r0 = 0;
int r1 = 0;
int r2 = 0;
int count = 0;
int multiplex1[8];
int multiplex2[8];
int total_playtime = 0;

int numPins = 5;
//*******************************************************************************************************************
// Setup
//*******************************************************************************************************************

void setup()
{
	pinMode(2, OUTPUT);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	Serial.begin(115200);                                  // connect to the serial port 115200
}

void loop()
{
	readSensors(0);
	checkSensors(0);
}

void readSensors (int analogPin)
{
	for(count=0; count <= numPins; count++)
	{
		r2 = bitRead(count,0);
		r1 = bitRead(count,1);
		r0 = bitRead(count,2);
		digitalWrite(2, r0);
		digitalWrite(3, r1);
		digitalWrite(4, r2);

		multiplex1[count] = analogRead(analogPin);
	}
}

void checkSensors (int analogPin)
{
	const int num_iters = 1;
	if(total_playtime < num_iters)
	{
		for(int pin=0; pin <= numPins; pin++)
		{
			hitavg[pin] += multiplex1[pin];
		}

		total_playtime++;
		return;
	}
	else
	{
		int v_max = 0;
		int i_max = 0;

		for(int pin=0; pin <= numPins; pin++)
		{

			if(hitavg[pin] > v_max)
			{
				v_max = hitavg[pin] / num_iters;
				i_max = pin;
			}

                        hitavg[pin] = 0;
                        if(PinPlayTime[pin] > 0)
			{
				PinPlayTime[pin]--;
			}
		}

		if(v_max > 130)
		{
			if(PinPlayTime[i_max] == 0)
			{
				debug(i_max);
				PinPlayTime[i_max] = 1024;
			}
		}


		total_playtime = 0;
	}
}

void debug(int num)
{
	char message[32];
	sprintf(message, "%d\r\n", num);
	Serial.write(message);
}

void MIDI_TX(unsigned char MESSAGE, int PITCH, int VELOCITY)
{
	/*
	status = MESSAGE + midichannel;
	Serial.write(status);
	Serial.write(PITCH);
	Serial.write(VELOCITY);
	*/

	char message[128];
	sprintf(message, "PAD: %d %d %d\r\n", (int) MESSAGE, (int)PITCH, (int)VELOCITY);
	Serial.write(message);

}
