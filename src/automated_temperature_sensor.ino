/*
 * Project: Automated Temperature Sensor
 * Author: Jesus Aurelio Corpus
 * Date: November 15, 2026
 * 
 * Description: Reads TMP36 sensor and controls LEDs based on temperature thresholds.
 */

 //Pin Definitions
const int HEATER_PIN = 12; // Red LED
const int FAN_PIN = 13;	   // Green LED


 void setup() {
   Serial.begin(9600); //Start the serial monitor
   pinMode(HEATER_PIN, OUTPUT);
   pinMode(FAN_PIN, OUTPUT);   
}

void loop() {
  // 1. Read raw value from pin A0 (0-1023)
  int rawValue= analogRead(A0);
  
  // 2. Convert raw value to voltage (0 to 5V)
  float voltage = rawValue * (5.0 / 1023.0);
  
  // 3. Convert voltage to Celsius (TMP36 offset is 0.5V, 10mV per degree)
  float tempC= (voltage- 0.5) *100.0;
  
  
  // 4. Print to Serial Monitor
  Serial.print("Temp: ");
  Serial.print(tempC);
  Serial.println(" C");
  
  // 5. Temperature Logic
  if (tempC > 30) {
    Serial.println("WARNING: It is too hot in here!");
    digitalWrite(13, HIGH);   // Fan ON
    digitalWrite(12, LOW);    // Heater OFF
  } 
  else if (tempC < 20) {
    Serial.println("WARNING: It is too cold!");
    digitalWrite(12,HIGH);    // Heater ON
    digitalWrite(13, LOW);    // Fan OFF
  }
  else {
    digitalWrite(12, LOW);    // Heater OFF
    digitalWrite(13, LOW);    // Fan OFF
  }
  
  delay (2000);               // Wait 2 seconds before reading again
}
