const int smokePin = A0;
const int flamePin = 2;
const int buzzerPin = 8;
const int redLed = 4;   // Red for Danger
const int greenLed = 5; // Green for Safe

int smokeThreshold = 300; 

void setup() {
  pinMode(flamePin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int smokeValue = analogRead(smokePin);
  int flameValue = digitalRead(flamePin);

  Serial.print("Smoke: "); Serial.print(smokeValue);
  Serial.print(" | Flame: "); Serial.println(flameValue);

  if (smokeValue > smokeThreshold || flameValue == LOW) {
    digitalWrite(greenLed, LOW);    

    digitalWrite(redLed, HIGH); 
    digitalWrite(buzzerPin, HIGH);
    delay(150);                    
    
    digitalWrite(redLed, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(150);                    
  } 

  else {
    digitalWrite(greenLed, HIGH);   
    digitalWrite(redLed, LOW);      
    digitalWrite(buzzerPin, LOW);   
  }

  delay(50);
}
