#include <WiFi.h>
#include <HTTPClient.h>

void setup() {
  Serial.begin(115200); //Naar laptop

  

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial1.available()) {
    String test = Serial1.readStringUntil('\n');
    Serial.print("Ontvangen data: ");
    Serial.println(test);
  }
}
