#include <HTTPClient.h>
#include <string>

class HTTPClientWrapper
{
public:
  HTTPClientWrapper(const char *url) : http{}, dest{url} {}
  bool send(String content)
  {

    http.begin(dest);
    http.addHeader("Content-Type", "Content-Type: application/json");
    int httpResponseCode = http.POST(content); // Send the actual POST request
    if (httpResponseCode == 200)
    // TODO: add a repeater if it fails.
    {
      Serial.println("Success; response 200");
      return true;
    }
    else
    {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();
    return false;
  }

private:
  HTTPClient http;
  const char *dest;
};