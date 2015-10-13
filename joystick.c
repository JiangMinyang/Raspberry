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
void printBin(int n) {
	for(int i = 0; i < 8; i++) {
		printf("%d", (n & 0x80) >> 7);
		n <<= 1;
	}
}
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
	int ans = 0;
	int input = 0x18 | channel;
	for(int i = 0; i < 12; i++) {
		digitalWrite(Din, input & (1 << (11 - i)));
		digitalWrite(CLK, HIGH);
		digitalWrite(CLK, LOW);
	}
	for(int i = 0; i < 12; i++) {
		digitalWrite(CLK, HIGH);
		digitalWrite(CLK, LOW);
		ans <<= 1;
		if (digitalRead(Dout)) {
			ans |= 0x1;
		}
	}
	ans >>= 1;
	digitalWrite(CS, HIGH);
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
		if (check(last_x, x) || check(last_y, y)) {
			printf("x: %d y: %d\n", x, y);
			last_x = x;
			last_y = y;
		}
		delay(1000);
	}
	return 0;
}
