

#include "MultiTempSensor.h"
#include "HTTPClientWrapper.h"
#include "WifiWrapper.h"

// Make sure you use the patched Onewire Lib mentioned
// https://github.com/PaulStoffregen/OneWire/pull/106
// https://github.com/PaulStoffregen/OneWire/issues/57#issuecomment-450151098


// const char *ssid = "";
// const char *password = "";
// const char *server = "";

const int MINUTE = 60000;

MultiTempSensor sensors{25};
HTTPClientWrapper http{server};
WifiWrapper wifi;
String jsonify(std::vector<float> data);

void setup(void)
{
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  wifi = WifiWrapper{ssid, password};
}

void loop(void)
{
  wifi.ensure_connected();
  String body = jsonify(sensors.get_temps());
  Serial.println(body);
  http.send(body);
  delay(MINUTE);
}


String jsonify(std::vector<float> data){
  String json = "{ 'temperatures' : [";
  for (int i = 0; i < data.size() - 1; i++){
    json = json + String(data[i]) + ", ";
  }
  json = json + String( data[data.size()-1]) + "]}";
  return json;
}