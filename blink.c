#include <wiringPi.h>
int main() {
	wiringPiSetup();
	pinMode(0, OUTPUT);
	for(;;) {
		digitalWrite(0, HIGH);
		delay(1000);
		digitalWrite(0, LOW);
		delay(500);
	}
	return 0;
}

// gcc -Wall -o blink blink.c -lwiringPi
// sudo ./blink
