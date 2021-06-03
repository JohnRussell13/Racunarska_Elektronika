#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<wiringPi.h>
#include<lcd.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/fcntl.h>


const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;
const char PCF8591 = 0x48;

int main()
{
	int lcd_h, fd, adcVal;
	if(wiringPiSetup() == -1)
		exit(1);
	lcd_h = lcdInit(2,16,4,RS,EN,D0,D1,D2,D3,D0,D1,D2,D3);
	fd = wiringPiI2CSetup(PCF8591);
	while(1)
	{
		wiringPiI2CReadReg8(fd, PCF8591);
		adcVal = wiringPiI2CReadReg8(fd, PCF8591);
		adcVal = adcVal/2.55;
		printf("%d\n", adcVal);
		lcdPosition(lcd_h,0,0);
		lcdPrintf(lcd_h,"%d",adcVal);
		if(adcVal < 33)
		{
			lcdPosition(lcd_h, 0, 1);
			lcdPrintf(lcd_h, "SLABO");
		}
		if(adcVal>=33 && adcVal<66)
		{
			
			lcdPosition(lcd_h, 0, 1);
			lcdPrintf(lcd_h, "DNEVNO");
		}
		if(adcVal>66)
		{

			lcdPosition(lcd_h, 0, 1);
			lcdPrintf(lcd_h, "NOCNO");
		}

		delay(500);
		lcdClear(lcd_h);
			
	}	
	return 0;
}
