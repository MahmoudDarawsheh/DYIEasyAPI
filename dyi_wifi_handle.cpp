#include "dyi_wifi_handle.h"

IPAddress local_IP(192, 168, 2, 249);
IPAddress gateway(192, 168, 2, 1);
IPAddress subnet(255, 255, 255, 0);
String ssid;
String password;
String storedSSID;
String storedPassword;
void clearEEPROM() {
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
}

bool ConnectToWifi(int WaitToConnect, bool Debug, bool UseStaticConfig) {
  if (RestoreNetworkCreds()) {
    if (UseStaticConfig) {
      PrepareWifiAddress();
    }
    if (ConnectToWifi(ssid,password,WaitToConnect, Debug)) {
        return true;
    } else {
      Serial.println("Couldn't connect to WIFI,try again in minutes if that happens again please reenter your creids");
    }
  } else {
    Serial.println("Network ssid and password was not defined please define them with ssid=YOURNETWORK then pwd=YOURPASSWORD");
  }
  return false;
}
bool IsWifiConnected(){

  return  WiFi.status() == WL_CONNECTED;
}
bool ConnectToWifi(String ssid, String password ,int WaitToConnect, bool Debug) {
  pinMode(D3, OUTPUT);
  digitalWrite(D3, LOW);
  if (Debug) {

    Serial.print("Connecting to ");
    Serial.println(ssid);
  }

  WiFi.begin(ssid.c_str(), password.c_str());
  int CurrentWait = 0;
  while (WiFi.status() != WL_CONNECTED && WaitToConnect != -1 && CurrentWait < WaitToConnect) {
    digitalWrite(D3, HIGH);
    delay(500);
    digitalWrite(D3, LOW);
    delay(500);
    if (Debug) {
      Serial.print(".");
    }
    CurrentWait++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    if (Debug) {
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      Serial.println(WiFi.getHostname());
    }
    digitalWrite(D3, HIGH);



    return true;
  } else {
    if (Debug) {
      Serial.println("WiFi connection fails");
      Serial.println("Ignore Wifi");
    }
    digitalWrite(D3, LOW);
    return false;
  }
}


void storeIPAddress(const String& ipString) {
  IPAddress ip;
  if (ip.fromString(ipString)) {
    // IP address parsing successful
    for (int i = 0; i < 4; i++) {
      EEPROM.write(IP_EEPROM_ADDRESS + i, ip[i]);
    }
    // Commit the EEPROM changes
    EEPROM.commit();

    Serial.println("IP address stored successfully in EEPROM.");
  } else {
    // Invalid IP address format
    Serial.println("Invalid IP address format. Please use xxx.xxx.xxx.xxx format.");
  }
}


IPAddress readIPAddressFromEEPROM() {
  byte octets[4];
  for (int i = 0; i < 4; i++) {
    octets[i] = EEPROM.read(IP_EEPROM_ADDRESS + i);
  }
  IPAddress ip(octets);
  return ip;
}

void PrepareWifiAddress() {
  IPAddress storedIP = readIPAddressFromEEPROM();
  if (storedIP[0] != 0 && storedIP[1] != 0) {
    local_IP = storedIP;
    gateway = IPAddress(local_IP[0], storedIP[1], storedIP[2], 1);
    subnet = calculateSubnetMask(local_IP, gateway);
  }
  WiFi.config(local_IP, gateway, subnet);
}
void PrepareWifiAddress(IPAddress selectedIp ) {
  if (selectedIp[0] != 0 && selectedIp[1] != 0) {
    local_IP = selectedIp;
    gateway = IPAddress(local_IP[0], selectedIp[1], selectedIp[2], 1);
    subnet = calculateSubnetMask(local_IP, gateway);
  }
  WiFi.config(local_IP, gateway, subnet);
}
bool RestoreNetworkCreds() {
  // Read SSID and Password from EEPROM
  EEPROM.begin(512);

  byte flag=EEPROM.read(SettingsWrittenFlag);
  if(flag!=69)
  {
    return false;
  }
  // Read SSID from EEPROM
  for (int i = 0; i < 32; i++) {
    char c = EEPROM.read(0 + i);
    if (c == '\0') {
      break;  // Stop reading if null-terminated
    }
    storedSSID += c;
  }

  // Read Password from EEPROM
  for (int i = 0; i < 64; i++) {
    char c = EEPROM.read(32 + i);
    if (c == '\0') {
      break;  // Stop reading if null-terminated
    }
    storedPassword += c;
  }

  // Trim the strings
  storedSSID.trim();
  storedPassword.trim();

  // Print the trimmed strings

  if (storedPassword.length() == 0 || storedSSID == 0) {
    return false;
  }
  ssid = storedSSID.c_str();
  password = storedPassword.c_str();
  return true;
}

void CheckIfUserChangedNetworkCreds() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');  // Read the input until a newline character is received

    // Check if the input starts with "ssid="
    if (input.startsWith("ssid=")) {
      // Extract the SSID from the input
      String ssidValue = input.substring(5);

      // Store the SSID in EEPROM
      for (int i = 0; i < ssidValue.length(); i++) {
        EEPROM.write(i, ssidValue[i]);
      }
      EEPROM.write(ssidValue.length(), '\0');  // Null-terminate the string in EEPROM

      Serial.println("SSID stored, please send the password.");
    } else if (input.startsWith("pwd=")) {
      // Extract the password from the input
      String passwordValue = input.substring(4);

      // Store the password in EEPROM
      int pwdStartIndex = MAX_SSID_LENGTH;
      for (int i = 0; i < passwordValue.length(); i++) {
        EEPROM.write(pwdStartIndex + i, passwordValue[i]);
      }
      EEPROM.write(pwdStartIndex + passwordValue.length(), '\0');  // Null-terminate the string in EEPROM
      EEPROM.write(SettingsWrittenFlag,69);
      EEPROM.commit();
      Serial.println("Password stored. Restarting the program.");
      delay(1000);    // Optional delay for better visibility on Serial monitor
      ESP.restart();  // Restart the NodeMCU program
    } else if (input.startsWith("forgetNetwork")) {
      clearEEPROM();
      Serial.print("network Creids was forgotten");
      ESP.restart();
    } else if (input.startsWith("ip=")) {
      String IpString = input.substring(3);
      storeIPAddress(IpString);
      Serial.println("Ip address has been changed successfully to");
      Serial.println(IpString);
      ESP.restart();
    }
  }
}

IPAddress calculateSubnetMask(const IPAddress& ip, const IPAddress& gateway) {
  return IPAddress(
    (ip[0] & gateway[0]),
    (ip[1] & gateway[1]),
    (ip[2] & gateway[2]),
    (ip[3] & gateway[3]));
}
