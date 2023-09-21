#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>

// Povezivanje senzora na digitalni pin 18
#define ONE_WIRE_BUS 18
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

Servo myservo[14];

int segmentOn[14] = { 180, 180, 90, 85, 20, 100, 10, 180, 98, 5, 85, 10, 80, 100 };                                                                                                                                                                                                //Servo on position values for each servo
int segmentOff[14] = { 90, 88, 180, 180, 100, 180, 105, 80, 180, 99, 180, 90, 180, 10 };                                                                                                                                                                                           //Servo off position values for each servo
int digits[10][7] = { { 1, 1, 1, 1, 1, 1, 0 }, { 0, 1, 1, 0, 0, 0, 0 }, { 1, 1, 0, 1, 1, 0, 1 }, { 1, 1, 1, 1, 0, 0, 1 }, { 0, 1, 1, 0, 0, 1, 1 }, { 1, 0, 1, 1, 0, 1, 1 }, { 1, 0, 1, 1, 1, 1, 1 }, { 1, 1, 1, 0, 0, 1, 0 }, { 1, 1, 1, 1, 1, 1, 1 }, { 1, 1, 1, 1, 0, 1, 1 } };  //Position values for each digit

void setup() {

  Serial.begin(9600);
  sensors.begin();

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
  for (int i = 0; i <= 13; i++)  //Set all of the servos to on or up (88 displayed)
  {
    myservo[i].write(segmentOn[i]);
  }
  delay(5000);
}


void loop() {
  sensors.requestTemperatures();                  // Zatraži novu temperaturu od senzora
  int temperatureC = sensors.getTempCByIndex(0);  // Dohvati temperaturu u Celzijusima
  if (temperatureC != DEVICE_DISCONNECTED_C) {
    Serial.print("Temperatura: ");
    Serial.print(temperatureC);
    Serial.println(" °C");
  } else {
    Serial.println("Senzor nije pronađen!");
  }
  // Prikaz temperature na segmentnom displeju
  int tensDigit = int(temperatureC) / 10;   // Desetice
  int unitsDigit = int(temperatureC) % 10;  // Jedinice

  displayTemperature(tensDigit, unitsDigit);
  delay(2000);
}

void displayTemperature(int tens, int units) {
  int mustDelay1 = 0;

  if (digits[tens][6] != digits[tens + 1][6]) {
    if (digits[tens + 1][1] == 1) {
      myservo[8].write(segmentOn[8] - 30);
      mustDelay1 = 1;
    }
    if (digits[tens + 1][5] == 1) {
      myservo[12].write(segmentOn[12] + 30);
      mustDelay1 = 1;
    }
  }

  if (tens == 9) {
    myservo[8].write(segmentOn[8] - 30);
    myservo[12].write(segmentOn[12] + 30);
  }

  if (mustDelay1 == 1)
    delay(200);

  for (int h = 6; h >= 0; h--) {
    if (digits[tens][h] == 1)
      myservo[h + 7].write(segmentOn[h + 7]);
    else
      myservo[h + 7].write(segmentOff[h + 7]);

    if (h == 6)
      delay(200);
  }

  int mustDelay2 = 0;

  if (digits[units][6] != digits[units + 1][6]) {
    if (digits[units + 1][1] == 1) {
      myservo[1].write(segmentOn[1] - 30);
      mustDelay2 = 1;
    }
    if (digits[units + 1][5] == 1) {
      myservo[5].write(segmentOn[5] + 30);
      mustDelay2 = 1;
    }
  }

  if (units == 9) {
    myservo[1].write(segmentOn[1] - 30);
    myservo[5].write(segmentOn[5] + 30);
  }

  if (mustDelay2 == 1)
    delay(200);

  for (int j = 6; j >= 0; j--) {
    if (digits[units][j] == 1)
      myservo[j].write(segmentOn[j]);
    else
      myservo[j].write(segmentOff[j]);

    if (j == 6)
      delay(200);
  }

  if (mustDelay2 == 1)
    delay(600);
  else
    delay(800);
}
