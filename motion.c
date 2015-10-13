#include <wiringPi.h>

#define data 0
#define light 3
#define true 1
#define false 0

void setup() {
	wiringPiSetup();
	pinMode(data, INPUT);
	pinMode(light, OUTPUT);
}

int main() {
	setup();
	while (true) {
		if (digitalRead(data)) {
			digitalWrite(light, HIGH);
			while (digitalRead(data));
			digitalWrite(light, LOW);
		}
	}
	return 0;
}
