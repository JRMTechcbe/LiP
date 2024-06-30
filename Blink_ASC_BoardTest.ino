// Test Program for IETE IoT Board
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(33, OUTPUT); // LED1 at GPIO33
  pinMode(4, OUTPUT); // LED2 at GPIO4
  pinMode(32,INPUT); // Button Switch at GPIO 32
  pinMode(0,INPUT); // Button Switch at GPIO 0 Boot Button
  Serial.begin(9600); // Serial Output at 9600 baud rate
  Serial.println("Jai Sri Ram Jai Sita Ram"); // Test message
}

// the loop function runs over and over again forever
void loop() {
  int s1 = 0; // Button status S1
  int s2 = 0; // Button status S2
  s1 = digitalRead(32); // Read the status of User Button at GPIO 32
  s2 = digitalRead(0); // Read the status of Boot Button at GPIO 0
  if(s1 == HIGH && s2 == LOW){ // If User button is pressed
  digitalWrite(33, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(4, LOW); 
  int potvalue = analogRead(36); // POT Value from GPIO 36
  Serial.print("POT:");
  Serial.println(potvalue);
  }
   if(s1 == LOW && s2 == HIGH ){
  digitalWrite(33, LOW);
  digitalWrite(LED_BUILTIN, LOW); 
  digitalWrite(4, HIGH);  
  int LDRvalue = analogRead(39); // LDR Value from GPIO 39
  Serial.print("LIGHT:");
  Serial.println(LDRvalue);
   }
  
}
