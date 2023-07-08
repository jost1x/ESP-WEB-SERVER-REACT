#include <Arduino.h>
#include <main.h>

#include <FS.h>

#include <WiFi.h>
#include <SPIFFS.h>

#include <Communication.h>
#include <webserver.h>
#include <ESPAsyncWebServer.h>

FS *filesystem = &SPIFFS;

void setup()
{
    Serial.begin(115200);
    communitacion_connect();

    if (!SPIFFS.begin())
    {
        Serial.println("[SPIFFS] Error montando la memoria.");
        return;
    }

    setupServer();
}

void loop()
{
}
