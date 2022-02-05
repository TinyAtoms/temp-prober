#include <WiFi.h>

class WifiWrapper
{
public:
    WifiWrapper(){};
    WifiWrapper(const char *ssid, const char *password) : ssid{ssid}, pw{password}
    {
        WiFi.begin(ssid, pw);
        Serial.println("Connecting");
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }
        Serial.println("");
        Serial.print("Connected to WiFi network with IP Address: ");
        Serial.println(WiFi.localIP());
    };

    void ensure_connected()
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            return;
        }

        WiFi.begin(ssid, pw);
        Serial.print("Reconnecting  to wifi");
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.println(".");
        }
    };

private:
    const char *ssid;
    const char *pw;
};