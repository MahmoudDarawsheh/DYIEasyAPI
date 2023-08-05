#include <DYIEasyAPI.h>

/* DYIEasyAPI :Develop Your Interface with easy apis
 * in this example we will see how we can configure Wifi in different modes from memory or from EEPROM also how you can configure different settings with the Library
 * after you turn on the device you need to configure EEPROM to wifi which is very easy in this library following these steps
 * 1- connect device to any serial terminal such as serial monitor or on your phone with OTG Cable to the device.
 * 2- wait until the device fails to connect to wifi
 * 3- send to serial ssid=YOURWIFISSID then enter
 * 4- it will promote to you sending password enter pwd=YOURWIFIPASSWORD
 * 5- Device will restart enter ip=YOURIP
 *    Example if your networks ips are 192.168.0.2 then enter ip=192.168.0.220 or any ip fits your network // to know your ip on windows from cmd enter ipconfig, on linux ifconfig
 * 6- Now everything is ready to give it a try, on your computer ,phone or any other devices connected to the same SSID 
 *  the settings above if you want to connect using eeporm settings , in case you want to use a static ssid and password ignore the steps above only change the ssid and password variable based on your need , check configuration you need to change and deploy the code
*/
#include<DYIEasyAPI.h>

bool UseEEPROMConfig=true;

void setup() {
  Serial.begin(9600);

  int Timeout=120; //set the timeout  in seconds when to fail connection to wifi usually i use 120 or 300 the system will keep trying connect until output is shown
  bool PrintLogsToSerial=true;// this pa
  bool UseStaticIp=true;

  bool IsConnectedToWifi=false;
  if(UseEEPROMConfig){
    IsConnectedToWifi=ConnectToWifi( Timeout, PrintLogsToSerial,UseStaticIp);
  }else{
    String SSID="YOURNETWORK";//your network SSID
    String Password="YOURPASSWORD";
    if(UseStaticIp)
    {
      IPAddress IPstatic(192,168,0,1);// ip address
      PrepareWifiAddress(IPstatic); // request arduino to configure static ip configs
    }
    IsConnectedToWifi=ConnectToWifi(SSID,Password,Timeout,PrintLogsToSerial); //connect to wifi
  }
  if (IsConnectedToWifi) {// to see ConnectToWifi details check Wifi Examples
    Serial.println("Connected");
   
  } else {
    Serial.println("Not Connected");
  }

}

void loop() {
  if(!UseEEPROMConfig){
  CheckIfUserChangedNetworkCreds();//check if command was sent to change ssid,pwd or ip using serial
  }

  delay(500);
  
  // put your main code here, to run repeatedly:

}
