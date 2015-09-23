#include <wiringPi.h>

#define numData 1
#define segmentData 7
#define clock 4
#define latch 0

int num[5];
int segment[10];

void setup() {
  wiringPiSetup();
  pinMode(numData, OUTPUT);
  pinMode(segmentData, OUTPUT);
  pinMode(clock, OUTPUT);
  pinMode(latch, OUTPUT);
  num[1] = 128; num[2] = 64; num[3] = 32; num[4] = 16;
  segment[0] = 2; segment[1] = 194; segment[2] = 36; segment[3] = 12;
  segment[4] = 152; segment[5] = 72; segment[6] = 64; segment[7] = 30;
  segment[8] = 0; segment[9] = 8;

}

void display(int i) {
  int digit[5];
  digit[1] = i / 1000;
  digit[2] = (i / 100) % 10;
  digit[3] = (i / 10) % 10;
  digit[4] = i % 10;

  for(int i = 1; i < 5; i++) {
    int x1 = num[i];
    int x2 = segment[digit[i]];
    digitalWrite(latch, LOW);
    for(int j = 0; j < 8; j++) {
      digitalWrite(numData, x1 & 1);
      digitalWrite(segment, x2 & 1);
      x1 >>= 1;
      x2 >>= 1;
      digitalWrite(clock, LOW);
      delay(3);
      digitalWrite(clock, HIGH);
    }
    digitalWrite(latch, HIGH);
  }
}

int main() {
  setup();
  for(int i = 0; i < 1000; i++) {
    display(i);
    delay(100);
  }
  return 0;
}