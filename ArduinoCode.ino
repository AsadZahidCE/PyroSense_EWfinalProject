const int smokePin = A0;
const int flamePin = 2;
const int buzzerPin = 8;
const int redLed = 4;   // Red for Danger
const int greenLed = 5; // Green for Safe

// If it triggers too easily, increase this to 500 or 600
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

  // Print values to Serial Monitor so you can calibrate
  Serial.print("Smoke: "); Serial.print(smokeValue);
  Serial.print(" | Flame: "); Serial.println(flameValue);

  // ALARM CONDITION (Smoke detected OR Flame detected)
  // Note: Flame sensors usually output LOW when they see fire
  if (smokeValue > smokeThreshold || flameValue == LOW) {
    digitalWrite(greenLed, LOW);    // Kill the green light immediately
    
    // Create a clear "Beep-Flash" pattern
    digitalWrite(redLed, HIGH); 
    digitalWrite(buzzerPin, HIGH);
    delay(150);                     // Quick flash on
    
    digitalWrite(redLed, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(150);                     // Quick flash off
  } 
  
  // SAFE CONDITION
  else {
    digitalWrite(greenLed, HIGH);   // Solid Green = All Clear
    digitalWrite(redLed, LOW);      // Red stays off
    digitalWrite(buzzerPin, LOW);   // Buzzer stays quiet
  }

  delay(50); // Small pause for stability
}
