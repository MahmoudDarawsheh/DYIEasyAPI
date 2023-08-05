#ifndef DYI_HTTP_REQUEST_H
#include<Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
extern int IndecatorLED;
String SendRequest(String URL);
String SendRequest(String URL,bool Debug);
String SendSecureRequest(String url, bool debug);

#endif