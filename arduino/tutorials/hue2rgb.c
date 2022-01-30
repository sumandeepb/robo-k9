// color pins
const unsigned char BLUE = 6;
const unsigned char GREEN = 9;
const unsigned char RED = 10;

// color values
unsigned char blueValue;
unsigned char greenValue;
unsigned char redValue;

// debug buffer
char buffer[64];

void setup() {
  // put your setup code here, to run once:
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);

  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);

  // for debug
  // Serial.begin(9600); // setup serial port baud rate
}

void HsvToRgb(unsigned char h, unsigned char s, unsigned char v)
{
  unsigned char region, remainder, p, q, t;

  if (s == 0)
  {
    redValue = v;
    greenValue = v;
    blueValue = v;
  }

  region = h / 43;
  remainder = (h - (region * 43)) * 6;

  p = (v * (255 - s)) >> 8;
  q = (v * (255 - ((s * remainder) >> 8))) >> 8;
  t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

  switch (region)
  {
    case 0:
      redValue = v; greenValue = t; blueValue = p;
      break;
    case 1:
      redValue = q; greenValue = v; blueValue = p;
      break;
    case 2:
      redValue = p; greenValue = v; blueValue = t;
      break;
    case 3:
      redValue = p; greenValue = q; blueValue = v;
      break;
    case 4:
      redValue = t; greenValue = p; blueValue = v;
      break;
    default:
      redValue = v; greenValue = p; blueValue = q;
      break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for (unsigned char i = 0; i < 256; i++)
  {
    HsvToRgb(i, 255, 255);

    // boundary conditions
    if (0 == i) {
      greenValue = 0;
    }
    if (86 == i) {
      blueValue = 0;
    }
    if (172 == i) {
      redValue = 0;
    }

    // RGB LED has common anode, so need to invert
    analogWrite(BLUE, (255 - blueValue));
    analogWrite(GREEN, (255 - greenValue));
    analogWrite(RED, (255 - redValue));

    // sprintf(buffer, "%d %d %d %d", i, redValue, greenValue, blueValue);
    // Serial.println(buffer);

    delay(100);
  }
}
