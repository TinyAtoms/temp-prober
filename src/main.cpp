
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <string>


const char* ssid = "telew_f2b";
const char* password = "";
const char* server = "https://webhook.site/55fe7c5b-a0be-40da-a694-b3dae02d94e2";
const int DELAY = 30000; // 30 sec


#define ONE_WIRE_BUS 25
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);
HTTPClient http{};

void setup(void)
{
  // Start serial communication for debugging purposes
  Serial.begin(9600  );
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
    // Start up the sensor library
  sensors.begin();
}

void loop(void){
  if(WiFi.status()== WL_CONNECTED){

  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);
  sensors.getTempFByIndex(0);
  Serial.print("Celsius temperature: ");
  Serial.print(temp);
  Serial.print("\n");
  String jsonBody = "{'temp' : " + String(temp) + "}";
  http.begin(server);
  http.addHeader("Content-Type", "Content-Type: application/json");
  int httpResponseCode = http.POST(jsonBody); //Send the actual POST request

   if(httpResponseCode>0){
    String response = http.getString();  //Get the response to the request
    Serial.println("code:");
    Serial.println(httpResponseCode);   //Print return code
  } else {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
   }
   http.end();
   delay(DELAY/ 5);
  }
   else {
      Serial.println("WiFi Disconnected");
    }
}