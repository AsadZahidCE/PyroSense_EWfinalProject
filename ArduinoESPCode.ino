#define BLYNK_TEMPLATE_ID "TMPL25fE8R6S1"
#define BLYNK_TEMPLATE_NAME "Fire and Gas Detector"
#define BLYNK_AUTH_TOKEN "Z84gB6rcSZ5eEGN7YN4ZxO2AncfE9eSv"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// --- Credentials ---
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Fast Faculty"; 
char pass[] = "Faculty@Fast987"; 

// --- Pins ---
const int smokePin = 34;    // Analog MQ-2
const int flamePin = 35;    // Digital Flame Sensor
const int buzzerPin = 32;   
const int redLed = 33;      
const int greenLed = 25;    

// Threshold for ESP32 (0 - 4095)
int smokeThreshold = 2000;  

void setup() {
  Serial.begin(115200);
  
  // Connect to Blynk
  Blynk.begin(auth, ssid, pass);

  pinMode(flamePin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  
  Serial.println("System Monitoring Online...");
}

void loop() {
  Blynk.run();

  int smokeValue = analogRead(smokePin);
  int flameValue = digitalRead(flamePin);

  // Monitor values in Serial Monitor
  Serial.print("Smoke Level: "); Serial.print(smokeValue);
  Serial.print(" | Flame Status: "); Serial.println(flameValue);

  // ALARM CONDITION
  if (smokeValue > smokeThreshold || flameValue == LOW) {
    digitalWrite(greenLed, LOW); // Turn off Green
    
    // Trigger Blynk Notification and Email
    Blynk.logEvent("fire_alert", "EMERGENCY: Smoke or Flame detected!");
    Blynk.virtualWrite(V1, 1); // Update Dashboard widget

    // Local Blinking Alarm
    digitalWrite(redLed, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(200); 
    
    digitalWrite(redLed, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(200);
  } 
  else {
    // SAFE CONDITION
    digitalWrite(greenLed, HIGH); 
    digitalWrite(redLed, LOW);
    digitalWrite(buzzerPin, LOW);
    Blynk.virtualWrite(V1, 0); // Dashboard safe status
  }

  delay(50); 
}
