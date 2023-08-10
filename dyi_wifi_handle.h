#ifndef DYI_WIFI_HANDLE
#include <arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
#define MAX_SSID_LENGTH 32
#define MAX_PASSWORD_LENGTH 64
#define IP_EEPROM_ADDRESS 96
#define SettingsWrittenFlag 107



bool ConnectToWifi(String ssid, String password ,int WaitToConnect, bool Debug);
bool ConnectToWifi( int WaitToConnect, bool Debug,bool UseStaticConfig );
void PrepareWifiAddress();
void PrepareWifiAddress(IPAddress selectedIp );
IPAddress calculateSubnetMask(const IPAddress& ip, const IPAddress& gateway);
bool RestoreNetworkCreds();
void clearEEPROM();
void storeIPAddress(const String& ipString);
IPAddress readIPAddressFromEEPROM();
void CheckIfUserChangedNetworkCreds();
bool IsWifiConnected();
void SetLEDIndecator(int LEDPin);
#endif