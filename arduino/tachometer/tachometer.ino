//BCD 1, these are the digital pins of the first CD4511 chip, the one placed on the right hand side.
// They will be used to output bits to the input pins of the IC.
#define A_1 8
#define A_2 9
#define A_3 10
#define A_4 11

//BCD 2, same as above but different pins
#define B_1 4
#define B_2 5
#define B_3 6
#define B_4 7

// external interrupt pin for IR sensor input
#define SENSOR_PIN 2
#define BUFFER_SIZE 9

volatile bool fValidResult = false;
volatile unsigned int rpmSensorPulses = 0;
unsigned long lastInterruptTime = 0;
unsigned long lastReadingTime = 0;
unsigned int timeBuffer[BUFFER_SIZE];
unsigned int pulseBuffer[BUFFER_SIZE];
int iBuffer = 0;
unsigned int rpm = 0;
unsigned int dig1;
unsigned int dig2;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  //this will set all the pins to output, and the sensor pin to input to receive an electrical signal.
  pinMode(A_1, OUTPUT);
  pinMode(A_2, OUTPUT);
  pinMode(A_3, OUTPUT);
  pinMode(A_4, OUTPUT);
  pinMode(B_1, OUTPUT);
  pinMode(B_2, OUTPUT);
  pinMode(B_3, OUTPUT);
  pinMode(B_4, OUTPUT);
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), countUpdate, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  getRPM();
  displayRPM_lin(rpmSensorPulses);
}

void countUpdate() {
  unsigned int currentInterruptTime = millis();
  if (currentInterruptTime - lastInterruptTime > 10) // we set a no-interrupts window
  {
    rpmSensorPulses++; //increase count
    fValidResult = true;
    lastInterruptTime = currentInterruptTime;
  }
}

unsigned int getRPM()
{
  unsigned int currentReadingTime = millis();
  if (currentReadingTime - lastReadingTime >= 1000)
  {
    pulseBuffer[iBuffer] = rpmSensorPulses;
    timeBuffer[iBuffer] = currentReadingTime;

    unsigned int dTime = timeBuffer[iBuffer] - timeBuffer[(iBuffer + 1) % (BUFFER_SIZE)];
    unsigned int sPulse = pulseBuffer[iBuffer] - pulseBuffer[(iBuffer + 1) % (BUFFER_SIZE)];
    rpm = sPulse * 30 / ((dTime + 500) / 1000);

    if (true == fValidResult) {
      Serial.print(sPulse);
      Serial.print(" ");
      Serial.print(dTime);
      Serial.print(" ");
      Serial.println(rpm);
      fValidResult = false;
    }

    ++iBuffer %= BUFFER_SIZE;
    lastReadingTime = currentReadingTime;
  }

  return rpm;
}

void displayRPM_lin(unsigned int rpm)
{
  rpm %= 100; // roll over

  // render display
  dig1 = rpm % 10; // This will divide n by 10 and the remainder will be stored in d1, this will hold the placeholder value for the first 7 segment display
  dig2 = rpm / 10; // This will divide n by 10 and the value before decimal will be stored in d2, this will hold the placeholder value for the second 7 segment display
  dispBCD(dig1, A_1, A_2, A_3, A_4);
  dispBCD(dig2, B_1, B_2, B_3, B_4);
}

//this method entails making 0-9 combinations using the BCD pins by sending different outputs to turn each segment on or off.
void dispBCD(unsigned int num, unsigned int d1, unsigned int d2, unsigned int d3, unsigned int d4) {
  if (num == 0) //0000
  {
    digitalWrite(d1, LOW);
    digitalWrite(d2, LOW);
    digitalWrite(d3, LOW);
    digitalWrite(d4, LOW);
  }
  if (num == 1) //0001
  {
    digitalWrite(d1, HIGH);
    digitalWrite(d2, LOW);
    digitalWrite(d3, LOW);
    digitalWrite(d4, LOW);
  }
  if (num == 2) //0010
  {
    digitalWrite(d1, LOW);//0
    digitalWrite(d2, HIGH);//1
    digitalWrite(d3, LOW);//0
    digitalWrite(d4, LOW);//0
  }
  if (num == 3) //0011
  {
    digitalWrite(d1, HIGH);//1
    digitalWrite(d2, HIGH);//1
    digitalWrite(d3, LOW);//0
    digitalWrite(d4, LOW);//0
  }
  if (num == 4) //0100
  {
    digitalWrite(d1, LOW);//0
    digitalWrite(d2, LOW);//0
    digitalWrite(d3, HIGH);//1
    digitalWrite(d4, LOW);//0
  }
  if (num == 5) //0101
  {
    digitalWrite(d1, HIGH);//1
    digitalWrite(d2, LOW);//0
    digitalWrite(d3, HIGH);//1
    digitalWrite(d4, LOW);//0
  }
  if (num == 6) //0110
  {
    digitalWrite(d1, LOW);//0
    digitalWrite(d2, HIGH);//1
    digitalWrite(d3, HIGH);//1
    digitalWrite(d4, LOW);//0
  }
  if (num == 7) //0111
  {
    digitalWrite(d1, HIGH);//1
    digitalWrite(d2, HIGH);//1
    digitalWrite(d3, HIGH);//1
    digitalWrite(d4, LOW);//0
  }
  if (num == 8) //1000
  {
    digitalWrite(d1, LOW);//0
    digitalWrite(d2, LOW);//0
    digitalWrite(d3, LOW);//0
    digitalWrite(d4, HIGH);//1
  }
  if (num == 9) //1001
  {
    digitalWrite(d1, HIGH);//1
    digitalWrite(d2, LOW);//0
    digitalWrite(d3, LOW);//0
    digitalWrite(d4, HIGH);//1
  }
}
