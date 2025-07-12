#include <WiFi.h>
#include <Firebase_ESP_Client.h>


#define WIFI_SSID "esp"
#define WIFI_PASSWORD "88888888"

#define API_KEY "AIzaSyDCPh8LX9sEVoOt7eKdPquE1pGAG-ltCaQ"
#define DATABASE_URL "https://restaurant-app-rs-default-rtdb.asia-southeast1.firebasedatabase.app/"

#define USER_EMAIL "naimkyau.cse@gmail.com"
#define USER_PASSWORD "123456789"


FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

const int ledPin = 4;

void setup()
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;

  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  config.database_url = DATABASE_URL;

  Firebase.reconnectNetwork(true);

  fbdo.setBSSLBufferSize(4096 

  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);

  Firebase.setDoubleDigits(5);

  config.timeout.serverResponse = 10 * 1000;
}

void loop()
{
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

  int val;
   if(Firebase.RTDB.getInt(&fbdo, "/val/val_1", &val)){
    Serial.println(val);
   }else{
    Serial.println(fbdo.errorReason().c_str());
   }
  }

  
    delay(5000);
}