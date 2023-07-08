#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <webserver.h>

AsyncWebServer server(80);

String links[] = {
    "/",
    "/settings"};

int numLinks = sizeof(links) / sizeof(links[0]);

void setupServer()
{
  server.onNotFound(handleNotFoundRequest); // Static Files

  // API END POINT
  server.on("/scan", HTTP_GET, handleScanRequest);



  // 
  server.begin();
}

void handleNotFoundRequest(AsyncWebServerRequest *request)
{
  String filename = request->url();
  bool isReactRouterLink = ReactRouterLink(filename);
  String contentType = isReactRouterLink ? "text/html" : getContentType(request->url());
  if (isReactRouterLink)
  {
    filename = "/index.html";
  }

  if (!existFile(filename) || protectFiles(filename))
  {
    
    request->send(404, "text/plain", "FileNotFound");
    return;
  }

  if (filename.endsWith("/"))
  {
    filename += "index.html";
  }
  if (filename.indexOf(".") == -1)
  {
    filename += ".html";
  }
  if (isGzipFile(filename))
  {
    filename += ".gz";
  }

  AsyncWebServerResponse *response = request->beginResponse(SPIFFS, filename, contentType);
  if (filename.endsWith(".gz"))
  {
    response->addHeader("content-encoding", "gzip");
  }
  request->send(response);
}

void handleScanRequest(AsyncWebServerRequest *request)
{
  int n = WiFi.scanComplete();
  if (n == -2)
  {
    WiFi.scanNetworks(true);
    request->send(200, "application/json", "[]");
    return;
  }
  else if (n)
  {
    String responsePayload;
    responsePayload.reserve(n * 100);

    responsePayload += "[";

    for (int i = 0; i < n; ++i)
    {
      if (i != 0)
        responsePayload += ",";

      responsePayload += "{\"rssi\":";
      responsePayload += WiFi.RSSI(i);
      responsePayload += ",\"ssid\":\"";
      responsePayload += WiFi.SSID(i);
      responsePayload += "\",\"bssid\":\"";
      responsePayload += WiFi.BSSIDstr(i);
      responsePayload += "\",\"channel\":";
      responsePayload += WiFi.channel(i);
      responsePayload += ",\"secure\":";
      responsePayload += WiFi.encryptionType(i);
      responsePayload += "}";
    }

    responsePayload += "]";

    request->send(200, "application/json", responsePayload);
  }
  else
  {
    request->send(200, "application/json", "[]");
  }
}

String getContentType(String filename)
{
  static const struct
  {
    const char *extension;
    const char *contentType;
  } contentTypeMap[] = {
      {"/", "text/html"},
      {".htm", "text/html"},
      {".html", "text/html"},
      {".css", "text/css"},
      {".js", "application/javascript"},
      {".png", "image/png"},
      {".gif", "image/gif"},
      {".jpg", "image/jpeg"},
      {".ico", "image/x-icon"},
      {".xml", "text/xml"},
      {".pdf", "application/x-pdf"},
      {".zip", "application/x-zip"},
      {".svg", "image/svg+xml"},
      {".gz", "application/x-gzip"},
      {NULL, "text/plain"}};

  String contentType;

  for (int i = 0; contentTypeMap[i].extension != NULL; ++i)
  {
    if (filename.endsWith(contentTypeMap[i].extension))
    {
      contentType = contentTypeMap[i].contentType;
      break;
    }
  }

  return contentType;
}

bool existFile(String path)
{
  if (path.endsWith("/"))
  {
    path += "index.html";
  }
  else if (path.indexOf(".") == -1)
  {
    path += ".html";
  }

  return (filesystem->exists(path) || filesystem->exists(path + ".gz"));
}

bool isGzipFile(String path)
{
  if (path.endsWith("/"))
  {
    path += "index.html";
  }
  else if (path.indexOf(".") == -1)
  {
    path += ".html";
  }

  return filesystem->exists(path + ".gz");
}

bool protectFiles(String path)
{
  // if(path == "/config/wifi.json") return true;
  return false;
}

bool ReactRouterLink(const String &link)
{
  for (const auto &l : links)
  {
    if (l == link)
    {
      return true;
    }
  }
  return false;
}

