#include <Arduino.h>
#include <api.h>
#include <ESPAsyncWebServer.h>
#include <sensor.h>
#include <ArduinoJson.h>

void handleSensorData(AsyncWebServerRequest *request)
{
    DynamicJsonDocument doc(JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2));

    String responsePayload;

    JsonObject sensorObj = doc.createNestedObject("SENSOR");

    sensorObj["GPIO2"] = getState(LED_BUILTIN) ? "ON" : "OFF";
    sensorObj["TemperatureCPU"] = internalTempSensor();

    serializeJson(doc, responsePayload);

    request->send(200, "application/json", responsePayload);
}

void handlePostSensor(AsyncWebServerRequest *request)
{

    if (request->hasParam("GPIO2"))
    {
        String parametroValue = request->getParam("GPIO2")->value();

        if (parametroValue.equalsIgnoreCase("on"))
        {
            setState(LED_BUILTIN, HIGH);
        }
        else if (parametroValue.equalsIgnoreCase("off"))
        {
            setState(LED_BUILTIN, LOW);
        }
        else if (parametroValue.equalsIgnoreCase("toggle"))
        {
            toggleState(LED_BUILTIN);
        }

        request->send(200, "text/plain", "GPIO2_UPDATE");
    }
    else
    {
        request->send(400, "text/plain", "ParamsNotFound");
    }
}