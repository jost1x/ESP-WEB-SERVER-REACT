#include <Communication.h>

WiFiCredential wifi_sec;

void communitacion_connect()
{

    wifi_sec.SSID = "HwPlus7370";
    wifi_sec.Pass = "psuareZ2511";

    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_sec.SSID, wifi_sec.Pass);

    Serial.print("Connecting to WiFi ..");

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(1000);
    }

    Serial.println(WiFi.localIP());
}
