int REDLED = 13;
int BLUELED = 12;
int GREENLED = 11;
int JENNYLED = 10;
int CRAIGLED = 9;

int wait = 200;

void setup() {

  pinMode(REDLED, OUTPUT);
  pinMode(BLUELED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(JENNYLED, OUTPUT);
  pinMode(CRAIGLED, OUTPUT);
}

void loop() {

  digitalWrite(REDLED, HIGH);
  delay(wait);

  digitalWrite(JENNYLED, HIGH);
  digitalWrite(BLUELED, HIGH);
  delay(wait);
  
 
  digitalWrite(GREENLED, HIGH);
  digitalWrite(CRAIGLED, HIGH);
  delay(wait * 2);



  
  digitalWrite(GREENLED, LOW);
  digitalWrite(CRAIGLED, LOW);
  delay(wait);
  

  digitalWrite(JENNYLED, LOW);
  digitalWrite(BLUELED, LOW);
  delay(wait);
    
  digitalWrite(REDLED, LOW);
  
  delay(wait * 2);
  
  
}
