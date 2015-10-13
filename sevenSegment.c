#include <wiringPi.h>
#include <stdio.h>

#define numData 1
#define segmentData 7
#define clock 4
#define latch 0
#define clear 3

int num[5];
int segment[11];

void setup() {
  wiringPiSetup();
  pinMode(numData, OUTPUT);
  pinMode(segmentData, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(clear, OUTPUT);
  num[1] = 128; num[2] = 64; num[3] = 32; num[4] = 16;
  segment[0] = 2; segment[1] = 158; segment[2] = 36; segment[3] = 12;
  segment[4] = 152; segment[5] = 72; segment[6] = 64; segment[7] = 30;
  segment[8] = 0; segment[9] = 8;
  segment[10] = 255;
  digitalWrite(latch, LOW);
  digitalWrite(clear, LOW);
  digitalWrite(clock, LOW);
  digitalWrite(clock, HIGH);
  digitalWrite(clear, HIGH);
  digitalWrite(latch, HIGH);
}

void display(int i) {
  int digit[5];
  digit[1] = i / 1000;
  digit[2] = (i / 100) % 10;
  digit[3] = (i / 10) % 10;
  digit[4] = i % 10;
  int hash = 0;
  for(int count = 0; count < 250; count++) {
	  hash = 0;
  for(int k = 1; k < 5; k++) {
    int x1 = num[k];
    int x2 = segment[digit[k]];
	if (x2 != 2) hash = 1;
	if (hash == 0 && x2 == 2 && k != 4) x2 = segment[10];
    for(int j = 0; j < 8; j++) {
      digitalWrite(latch, LOW);
      digitalWrite(numData, (x1 >> j) & 1);
      digitalWrite(segmentData, (x2 >> j) & 1);
      digitalWrite(clock, LOW);
      digitalWrite(clock, HIGH);
      digitalWrite(latch, HIGH);
    }
	delay(1);
  }
  }
}

int main() {
  setup();
  int step = 1;
  int i = 99;
  while (1) {
	display(i);
	i += step;
	if (i == 0) step = 1;
	if (i == 9999) step = -1;
  }
  return 0;
}
