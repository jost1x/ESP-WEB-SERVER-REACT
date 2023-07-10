void setupSensor();

void setState(int pin, int state);
int getState(int pin);
void toggleState(int pin);
uint8_t internalTempSensor();


#ifdef ESP8266
int temprature_sens_read();
#endif
