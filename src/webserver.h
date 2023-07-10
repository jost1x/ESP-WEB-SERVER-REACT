#include <Arduino.h>
#include <FS.h>

#ifdef ESP8266
#include <LittleFS.h>
#endif
#ifdef ESP32
#include <SPIFFS.h>
#endif


#ifdef ESP8266
#define FS_S LittleFS
#endif
#ifdef ESP32
#define FS_S SPIFFS
#endif


#include <ESPAsyncWebServer.h>

extern FS *filesystem;

String getContentType(String filename);

void setupServer();

bool protectFiles(String path);
bool isGzipFile(String path);
bool existFile(String path);
bool ReactRouterLink(const String &link);

void handleNotFoundRequest(AsyncWebServerRequest *request);
void handleScanRequest(AsyncWebServerRequest *request);
