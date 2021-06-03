/*Povezati izlaz DAC-a sa AIN2 (koji je slobodan)
* očitavati trimer potenciometar koji je na AIN3
* upisati tu vrednost u DAC,
* očitati DAC preko AIN2
* DAC izlaz je validan do oko ~220
*/
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
const char PCF8591 = 0x48; // adresa
int fd, adcValPrev, num;
char unsigned adcVal;
int main() {
 if (wiringPiSetup () == -1) exit (1);
 fd = wiringPiI2CSetup(PCF8591);
 while (1) {
	 if(num <9 && adcVal <220){
 	wiringPiI2CWriteReg8 (fd, PCF8591 + num, adcVal) ;
	num++;
	adcVal+=27;
	wiringPiI2CReadReg8(fd,PCF8591+2);
	if(adcVal<221){
		adcValPrev = wiringPiI2CReadReg8(fd,PCF8591+2);
 printf("DAC vrednost = %d \n\n" , adcValPrev);
	}
 delay(50);
 }
	 else{
		 adcVal=0;
		 num=0;
 }
 }
 return 0;
}
