#include <Arduino.h>
#include <sensor.h>

#ifdef ESP32
#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();
#endif





void setupSensor() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void setState(int pin, int state) {
    digitalWrite(pin, state);
}

int getState(int pin) {
    return digitalRead(pin);
}

void toggleState(int pin) {
    return setState(pin, !getState(pin));
}

uint8_t internalTempSensor() {
    return (temprature_sens_read() - 32) / 1.8;
}

#ifdef ESP8266
    int temprature_sens_read(){
        return 32;
    }
#endif