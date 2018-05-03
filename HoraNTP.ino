// change next line to use with another board/shield
#include <NTPClient.h>//Biblioteca do NTP.
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
 
const char *ssid     = "saeg";
const char *password = "semsenha";
 
WiFiUDP ntpUDP;
#define led5 D5 // Led digital 5
 
int16_t utc = -2; //UTC -3:00 Brazil
uint32_t currentMillis = 0;
uint32_t previousMillis = 0;
 
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", utc*3600, 60000);
 
void setup(){
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  pinMode(ledTop1, OUTPUT);
  digitalWrite(ledTop1, LOW);
 
  timeClient.begin();
  timeClient.update();
}
 
void forceUpdate(void) {
  timeClient.forceUpdate();
}
 
void checkOST(void) {
  
  currentMillis = millis();//Tempo atual em ms
  //Lógica de verificação do tempo
  if (currentMillis - previousMillis > 1000) {
    previousMillis = currentMillis;    // Salva o tempo atual
    printf("Time Epoch: %d: ", timeClient.getEpochTime());
    Serial.println(timeClient.getFormattedTime());
  }
}
 
void loop() {
  //Chama a verificacao de tempo
  checkOST();
  if(timeClient.getFormattedTime()== "16:38:00"){
   
    digitalWrite(ledTop1, HIGH);
  }
  if(timeClient.getFormattedTime()=="16:39:00"){
   
    digitalWrite(ledTop1, LOW);
  }
}
