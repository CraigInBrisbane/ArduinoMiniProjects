#define echoPin 7
#define trigPin 8
#define redLED 5
#define greenLED 3
#define buzzerPin 2

long duration;
long distance;

void setup() {
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;

  Serial.println(distance);

  if(distance <= 30) {
    digitalWrite(greenLED, HIGH);
    if(distance <= 12) {
      digitalWrite(redLED, HIGH);
      if(distance <= 4) {
        tone(buzzerPin, 500);        
      } else {
        noTone(buzzerPin);        
      }
    } else {
      digitalWrite(redLED, LOW);
    }
  } else {
    digitalWrite(greenLED, LOW);
  }

  delay(50);
}
