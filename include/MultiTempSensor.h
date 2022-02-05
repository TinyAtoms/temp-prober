#include <DallasTemperature.h>
#include <OneWire.h>
#include <vector>

class MultiTempSensor {
public:
  MultiTempSensor(){};
  MultiTempSensor(int pin) : onewire(pin) {
    sensors = DallasTemperature{&onewire};
    sensors.begin();
    n = sensors.getDeviceCount();
    for (int i = 0; i < n; i++) {
      if(!sensors.getAddress(dev_addr, i)){
        Serial.print("Ghost device at");
        Serial.println(i);
      };
    }
  }
  std::vector<float> get_temps() {
    std::vector<float> temps;
      sensors.requestTemperatures();
    for (int i = 0; i < n; i++) {
      if(sensors.getAddress(dev_addr, i)){
        temps.push_back(sensors.getTempC(dev_addr));
      }
      else {
        Serial.println("Something happened");
      }


    }
    return temps;
  }

  float get_temp(int id) {
    sensors.getAddress(dev_addr, id);
    return sensors.getTempC(dev_addr);
  }

private:
  OneWire onewire;
  DallasTemperature sensors;
  int n;
  DeviceAddress dev_addr;
};