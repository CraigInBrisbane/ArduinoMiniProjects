const int led_pin = 13;
const int ldr_pin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  pinMode(ldr_pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  int ldrStatus = analogRead(ldr_pin);
  Serial.println(ldrStatus);

  if(ldrStatus <= 600) {
    digitalWrite(led_pin, HIGH);
  } else {
    digitalWrite(led_pin, LOW);
  }
}
