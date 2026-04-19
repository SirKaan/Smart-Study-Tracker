#include <WiFi.h>
#include <HTTPClient.h>

void sendToServer(String data);
void reconnectToWifi();

void setup() {
  Serial.begin(115200); //Naar laptop
  delay(2000);

  //UART-verbinding met STM32
  Serial1.begin(9600, SERIAL_8N1, 4, 5); //D4=RX D5=TX

  //Wifi
  char ssid[] = "kaanesp";
  char password[] = "projectdatacom";

  WiFi.disconnect(true);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  Serial.print("\nVerbinden met wifi");

  char counter = 0; 

  while(WiFi.status() != WL_CONNECTED) {
    if(counter > 15) { //15 seconden timout tijd
      Serial.println("\nWifi Connection failed.");
      return;
    }
    Serial.print(".");
    delay(1000);
    counter++;
  }

  Serial.println("Wifi Connected.");

}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status() != WL_CONNECTED){
    reconnectToWifi();
  }

  if(Serial1.available()) {
    String data = Serial1.readStringUntil('\n');
    Serial.print("Received data: ");
    Serial.println(data);
  }
    
}

//Data versturen naar Server
void sendToServer(String data){
  
}

//Terug met Wifi proberen te verbinden indien verbinding verbroken
void reconnectToWifi(){
  char ssid[] = "kaanesp";
  char password[] = "projectdatacom";

  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Trying to connect to Wifi."); 
    WiFi.begin(ssid, password);
    for(int i = 0; i < 14; i++){
      delay(1000);
      if(WiFi.status() == WL_CONNECTED){
        Serial.println("Wifi connected.");
        return;
      } else {
        Serial.print(".");
      }
    }
    Serial.println("Connection could not be established"); 
  }
}