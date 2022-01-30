const int RED1 = 2;
const int AMBER1 = 3;
const int GREEN1 = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode (RED1, OUTPUT);
  pinMode (AMBER1, OUTPUT);
  pinMode (GREEN1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sequence1();
  sequence2();
  sequence3();
  sequence4();
}

void sequence1() {
  digitalWrite(RED1, HIGH);
  digitalWrite(AMBER1, LOW);
  digitalWrite(GREEN1, LOW);
  delay(1000);
}

void sequence2() {
  digitalWrite(RED1, HIGH);
  digitalWrite(AMBER1, HIGH);
  digitalWrite(GREEN1, LOW);
  delay(1000);

}

void sequence3() {
  digitalWrite(RED1, LOW);
  digitalWrite(AMBER1, LOW);
  digitalWrite(GREEN1, HIGH);
  delay(1000);
}

void sequence4() {
  digitalWrite(RED1, LOW);
  digitalWrite(AMBER1, HIGH);
  digitalWrite(GREEN1, LOW);
  delay(1000);
}
