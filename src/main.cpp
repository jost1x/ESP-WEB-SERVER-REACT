#include <Arduino.h>
#include <main.h>

#include <FS.h>

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <LittleFS.h>
#endif
#ifdef ESP32
#include <WiFi.h>
#include <SPIFFS.h>
#endif


#include <Communication.h>
#include <webserver.h>
#include <ESPAsyncWebServer.h>
#include <sensor.h>


#ifdef ESP8266
#define FS_S LittleFS
#endif
#ifdef ESP32
#define FS_S SPIFFS
#endif

FS *filesystem = &FS_S;


void setup()
{
    Serial.begin(115200);
    communitacion_connect();
    if (!FS_S.begin())
    {
        Serial.println("[SPIFFS] Error montando la memoria.");
        return;
    }
    setupSensor();
    setupServer();
}

void loop()
{
}
