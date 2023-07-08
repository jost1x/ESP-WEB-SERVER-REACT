#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
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
