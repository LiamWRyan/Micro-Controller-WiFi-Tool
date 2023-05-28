#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <set>
#include<list>


#define DEBUG_MODE

#ifdef DEBUG_MODE
#define DEBUG_PRINT(fmt, args...) Serial.printf(fmt, ## args)
#else
#define DEBUG_PRINT(fmt, args...) ;
#endif

