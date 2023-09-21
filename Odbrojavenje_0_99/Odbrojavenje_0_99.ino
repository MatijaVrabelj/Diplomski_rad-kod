#include <Servo.h>

Servo myservo[14];

int segmentOn[14] = { 180, 180, 90, 85, 20, 100, 10, 180, 98, 5, 85, 10, 80, 100 };                                                                                                                                                                                                //Servo on position values for each servo
int segmentOff[14] = { 90, 88, 180, 180, 100, 180, 105, 80, 180, 99, 180, 90, 180, 10 };                                                                                                                                                                                           //Servo off position values for each servo
int digits[10][7] = { { 1, 1, 1, 1, 1, 1, 0 }, { 0, 1, 1, 0, 0, 0, 0 }, { 1, 1, 0, 1, 1, 0, 1 }, { 1, 1, 1, 1, 0, 0, 1 }, { 0, 1, 1, 0, 0, 1, 1 }, { 1, 0, 1, 1, 0, 1, 1 }, { 1, 0, 1, 1, 1, 1, 1 }, { 1, 1, 1, 0, 0, 1, 0 }, { 1, 1, 1, 1, 1, 1, 1 }, { 1, 1, 1, 1, 0, 1, 1 } };  //Position values for each digit

void setup() {
  myservo[0].attach(2);
  myservo[1].attach(3);
  myservo[2].attach(4);
  myservo[3].attach(5);
  myservo[4].attach(6);
  myservo[5].attach(7);
  myservo[6].attach(8);
  myservo[7].attach(9);
  myservo[8].attach(10);
  myservo[9].attach(11);
  myservo[10].attach(12);
  myservo[11].attach(13);
  myservo[12].attach(45);
  myservo[13].attach(44);
  for (int i = 0; i <= 13; i++) {
    myservo[i].write(segmentOn[i]);
  }
  delay(5000);
}

void loop() {
  for (int g = 9; g >= 0; g--)  //Large loop counter to count the tens
  {
    int mustDelay1 = 0;
    if (digits[g][6] != digits[g + 1][6])  //Logic to move segments next to middle segment out of the way
    {
      if (digits[g + 1][1] == 1) {
        myservo[8].write(segmentOn[8] - 30);
        mustDelay1 = 1;
      }
      if (digits[g + 1][5] == 1) {
        myservo[12].write(segmentOn[12] + 30);
        mustDelay1 = 1;
      }
    }
    if (g == 9) {
      myservo[8].write(segmentOn[8] - 30);
      myservo[12].write(segmentOn[12] + 30);
    }
    if (mustDelay1 == 1)
      delay(200);
    for (int h = 6; h >= 0; h--)  //Small loop counter to move individual segments  to make up the tens digit
    {
      if (digits[g][h] == 1)
        myservo[h + 7].write(segmentOn[h + 7]);
      else
        myservo[h + 7].write(segmentOff[h + 7]);
      if (h == 6)
        delay(200);
    }
    for (int i = 9; i >= 0; i--)  //Large loop counter to count the units
    {
      int mustDelay2 = 0;
      if (digits[i][6] != digits[i + 1][6])  //Logic to move segments next to middle segment out of the way
      {
        if (digits[i + 1][1] == 1) {
          myservo[1].write(segmentOn[1] - 30);
          mustDelay2 = 1;
        }
        if (digits[i + 1][5] == 1) {
          myservo[5].write(segmentOn[5] + 30);
          mustDelay2 = 1;
        }
      }
      if (i == 9) {
        myservo[1].write(segmentOn[1] - 30);
        myservo[5].write(segmentOn[5] + 30);
      }
      if (mustDelay2 == 1)
        delay(200);


      for (int j = 6; j >= 0; j--)  //Small loop counter to move individual segments  to make up the unit digit
      {
        if (digits[i][j] == 1)
          myservo[j].write(segmentOn[j]);
        else
          myservo[j].write(segmentOff[j]);
        if (j == 6)
          delay(200);
      }
      if (mustDelay2 == 1)  //Delay logic to reduce delay if the side segments moved (adding an additional 200ms delay)
        delay(600);
      else
        delay(800);  //Delay between digits. 200ms delay already experienced in the code
    }
  }
  delay(2000);  //Delay after countdown to 0 before resetting
}
