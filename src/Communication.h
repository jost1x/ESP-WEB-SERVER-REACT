#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif
#ifdef ESP32
#include <WiFi.h>
#endif

struct WiFiCredential
{
    char *SSID;
    char *Pass;
};

extern WiFiCredential wifi_sec;

void communitacion_connect();
