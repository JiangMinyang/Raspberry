#include <wiringPi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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

int check(int a, int b) {
	int c = abs(a - b);
	if ((double)(c) / (double)b - 0.05 > 1e-8) {
		return 1;
	}
	return 0;
}

int main() {
	setup();
	int last_x = 0;
	int last_y = 0;
	while (true) {
		int x = readadc(0);
		int y = readadc(1);
		if (check(x, last_x) || check(y,last_y)) {
			printf("x: %d  y: %d\n", x, y);
		}	
		last_x = x; last_y = y;
		delay(1000);
	}
	return 0;
}
