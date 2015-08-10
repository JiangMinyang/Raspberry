#include <wiringPi.h>
#include <stdio.h>

#define CS 6
#define Din 5
#define Dout 4
#define CLK 1
#define true 1
#define false 0
void setup() {
	wiringPiSetup();
	pinMode(CLK, OUTPUT);
	pinMode(CS, OUTPUT);
	pinMode(Din, OUTPUT);
	pinMode(Dout, INPUT);
}

int readadc(int channel) {
	if (channel > 7 || channel < 0) {
		return -1;
	}
	digitalWrite(CS, HIGH);
	digitalWrite(CLK, LOW);
	digitalWrite(CS, LOW);
	int command = channel | 0x18;
	command <<= 3;
	for(int i = 0; i < 5; i++) {
		if ((command & 0x80)) {
			digitalWrite(Din, HIGH);
		} 
		else {
			digitalWrite(Din, LOW);
		}
		digitalWrite(CLK, HIGH);
		digitalWrite(CLK, LOW);
		command <<= 1;
	}
	int ans = 0;
	for(int i = 0; i < 12; i++) {
		digitalWrite(CLK, HIGH);
		digitalWrite(CLK, LOW);
		ans <<= 1;
		if (digitalRead(Dout)) {
			ans |= 0x1;
		}
	}

	digitalWrite(CS, HIGH);
	ans >>= 1;
	return ans;
}

int main() {
	setup();
	int potentiometer = 0;
	int last_read = 0;
	int range = 0;
	while (true) {
		int changed = false;
		int read_pin = readadc(potentiometer);
		printf("%d\n", read_pin);
		delay(1000);
	}
	return 0;
}
