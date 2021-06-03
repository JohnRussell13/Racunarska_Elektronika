#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <bcm2835.h>
#define PIN 20

int main(int argc, char *argv[]){
	int fd =  -1, ret;
	char *tmp1, tmp2[10], ch='t';
	char devname_head[50] = "/sys/devices/w1_bus_master1/28-00000";

	char devname_end[10] = "/w1_slave";
	char dev_name[100];
	long value;
	int integer, decimal;
	char buffer[100];
	int i,j;
	float lim;
	char qwe = 0;

	if(!bcm2835_init())	return 1;
	bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);

	lim = atof(argv[2]);

	strcpy(dev_name, devname_head);
	strcat(dev_name, argv[1]);
	strcat(dev_name, devname_end);
	while(1){
		if ((fd = open(dev_name, O_RDONLY)) < 0){
			perror("Greska!");
			exit(1);
		}
		ret = read(fd, buffer, sizeof(buffer));
		if(ret<0){
			perror("Greska2!");
			exit(1);
		}
	
		tmp1 = strchr(buffer,ch);
		sscanf(tmp1,"t=%s",tmp2);
		value = atoi(tmp2);
		integer = value/1000;
		decimal = value%1000;
		printf("Temp = %d.%d\n", integer, decimal);
		if(integer+(float)decimal/1000 > lim){
			if(qwe){
				bcm2835_gpio_write(PIN, HIGH);
				qwe = 0;
			}
			else{
				bcm2835_gpio_write(PIN, LOW);
				qwe = 1;
			}
		}
		else{
			bcm2835_gpio_write(PIN,LOW);
		}
		close(fd);
	}
	bcm2835_close();
	return  0;
}
