#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int i=0,j=0, taster_pritisnut=0;
	int r_value, r_val2, k=0;

	if(wiringPiSetup() == -1)
		exit(1);

	pinMode(21, INPUT);
	pinMode(22, INPUT);
	pinMode(25, OUTPUT);

	digitalWrite(25, HIGH);

	if(softPwmCreate(28,0,100) !=  0)
		exit(2);

	i = 0;
	taster_pritisnut = 0;
	j=0;
	while(1){
		r_value = digitalRead(21);
		r_val2 = digitalRead(22);
		digitalWrite(25, r_value);
		
		if(!r_value && !taster_pritisnut){
			for(k=0;k<10000;k++);
			taster_pritisnut = 1;	
			i += 20;
			if(i > 100) i = 100;
			printf("i = %d\n",i);
			fflush(stdout);

			softPwmWrite(28,i);
		}

		if(!r_val2 && !j){
			for(k=0;k<10000;k++);
			j = 1;
			i -= 20;
			if(i < 0) i = 0;
			printf("i = %d\n",i);
			fflush(stdout);

			softPwmWrite(28,i);
		}

		if (r_value) taster_pritisnut = 0;
		if (r_val2) j = 0;
	}
	return 0;
}
