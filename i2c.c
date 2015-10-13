#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

int main (int argc, char *argv[])
{
        int fd;
        int data;
        wiringPiSetup () ;
        fd=wiringPiI2CSetup (0x68) ;  /*Use i2cdetect command to find your respective device address*/
		wiringPiI2CWriteReg8(fd, 0x6b, 0);
        if(fd==-1)
        {
                printf("Can't setup the I2C device\n");
                return -1;
        }
        else
        {
                for (;;)
                {
                        int a = wiringPiI2CReadReg8(fd, 0x43);
						int b = wiringPiI2CReadReg8(fd, 0x44);
						data = (a << 8) | b;
                        if(data==-1)
                        {
                                printf("No data\n");
                                //return -1;
                        }
                        else
                        {
                                //print data
								if (data >= 0x8000) {
									data = -((65535 - data) + 1);
								}
                                printf("data=%d\n", data / 131);
                        }
						delay(1000);
                }
        }
        return 0;
}
