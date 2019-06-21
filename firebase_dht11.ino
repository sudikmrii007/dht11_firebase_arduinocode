#include <ESP8266WiFi.h>                                                    // esp8266 library
#include <FirebaseArduino.h>                                                // firebase library
#include <DHT.h>                                                            // dht11 temperature and humidity sensor library

#define FIREBASE_HOST "dht11-5c363.firebaseio.com"                          // the project name address from firebase id
#define FIREBASE_AUTH "6H7PA4PEeulY3KGimXvu1qAfBr4fjP6yOzSkoFZs"           // the secret key generated from firebase

#define WIFI_SSID "My ASUS"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "sudipta123"                                    //password of wifi ssid
 
#define DHTPIN D4                                                           // what digital pin we're connected to
#define DHTTYPE DHT11                                                       // select dht type as DHT 11 or DHT22
DHT dht(DHTPIN, DHTTYPE);                                                     

void setup() {
  Serial.begin(9600);
  delay(1000);                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase
  dht.begin();                                                               //Start reading dht sensor
}

void loop() { 
  float h = dht.readHumidity();                                              // Reading temperature or humidity takes about 250 milliseconds!
  float t = dht.readTemperature();                                           // Read temperature as Celsius (the default)
    
  if (isnan(h) || isnan(t)) {                                                // Check if any reads failed and exit early (to try again).
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  Serial.print("Humidity: ");  Serial.print(h);
  String fireHumid = String(h) + String("%");                                         //convert integer humidity to string humidity 
  Serial.print("%  Temperature: ");  Serial.print(t);  Serial.println("Â°C ");
  String fireTemp = String(t) + String("Â°C");                                                     //convert integer temperature to string temperature
  delay(4000);
  
  Firebase.pushString("/DHT11/Humidity", fireHumid);                                  //setup path and send readings
  Firebase.pushString("/DHT11/Temperature", fireTemp);                                //setup path and send readings
   
}
