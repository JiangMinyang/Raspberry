#include <wiringPi.h>

#define data 7
#define clear 5
#define clock 4
#define latch 1

void setup() {
  wiringPiSetup();
  pinMode(data, OUTPUT);
  pinMode(clear, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(latch, OUTPUT);
}


int main() {
	setup();
  digitalWrite(clear, LOW);
  digitalWrite(clear, HIGH);

  digitalWrite(latch, LOW);
  digitalWrite(latch, HIGH);

  int number = 1;
  for(;;) {
    for(int i = 0; i < 4; i++) {
      digitalWrite(latch, LOW);
      digitalWrite(data, (number >> i) & 1);
      digitalWrite(clock, HIGH);
      delay(100);
      digitalWrite(clock, LOW);
      digitalWrite(latch, HIGH);
    } 
  }
	return 0;
}
