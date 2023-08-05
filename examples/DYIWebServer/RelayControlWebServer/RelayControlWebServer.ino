/* DYIEasyAPI :Develop Your Interface with easy apis
 * in this example we will connect a relay module to pin D8 on NodeMCU put you can change it on any other pin that fits your application
 * you can connect to the relay any electrical device you want to control such as Lamp, TV ..etc , just make sure that the device can handle the Amps of the device and voltage to not break the device.
 * send the relay will be triggered by hitting a request to http://{NODMCUIP}/on to turn the relay on ,http://{NODMCUIP}/off to turn it off, http://{NODMCUIP}/pulse?i=1 to open it for as {1} secs then close it 
 * where i will represents the time to reclose
 * after you turn on the device you need to configure EEPROM to wifi which is very easy in this library following these steps
 * 1- connect device to any serial terminal such as serial monitor or on your phone with OTG Cable to the device.
 * 2- wait until the device fails to connect to wifi
 * 3- send to serial ssid=YOURWIFISSID then enter
 * 4- it will promote to you sending password enter pwd=YOURWIFIPASSWORD
 * 5- Device will restart enter ip=YOURIP
 *    Example if your networks ips are 192.168.0.2 then enter ip=192.168.0.220 or any ip fits your network // to know your ip on windows from cmd enter ipconfig, on linux ifconfig
 * 6- Now everything is ready to give it a try, on your computer ,phone or any other devices connected to the same SSID 
 *  try  to enter the following on your browser assuming you chose 192.168.0.220
 * a.http://192.168.0.220/on  //Notice the relay will turn on 
 * b.http://192.168.0.220/off //Notice the relay will turn off
 * c.http://192.168.0.220/pulse?i=1 //Notice the relay will turn on for 1 seconds then will turn off
 * d.http://192.168.0.220/pulse?i=2 //Notice the relay will turn on for 2 seconds then will turn off
 */
#include<DYIEasyAPI.h>
#define RELAY_PIN D8
void turnOn(WiFiClient client, String header) {
 digitalWrite(RELAY_PIN, HIGH);//turn on the relay
 client.println("{\"state\":\"on\"}");
}
void turnOff(WiFiClient client, String header) {
 digitalWrite(RELAY_PIN, LOW);//turn on the relay
 client.println("{\"state\":\"off\"}");
}
void pulse(WiFiClient client, String header) {
 digitalWrite(RELAY_PIN, HIGH);//turn on the relay
 String inchingString=getQueryParamValue(header,"i");
 int inching=inchingString.toInt();
 delay(inching *1000);
 digitalWrite(RELAY_PIN, LOW);//turn on the relay
String output="{\"state\":\"on,wait(";
output.concat(inching);
output.concat("),off\"}");
client.println(output);
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
pinMode(RELAY_PIN,OUTPUT);
  if (ConnectToWifi( 60, true,true)) {// to see ConnectToWifi details check Wifi Examples
    Serial.println("Connected");
    SetHostNameToDNS(true);//if you want to start mDNS use this
    dicActions["/on"] = turnOn; //define http://IP/on route to call turnOn
    dicActions["/off"] = turnOff;//define http://IP/off route to call turnOn
    dicActions["/pulse"] = pulse;//define http://IP/pulse route to call turnOn

    InitServer();//start server 

  } else {
    Serial.println("Not Connected");
  }

}

void loop() {
  CheckIfUserChangedNetworkCreds();//check if command was sent to change ssid,pwd or ip using serial
  UpdateMDNS();//update DNS
  ListenToServer();//listen to http requests

  delay(500);
  
  // put your main code here, to run repeatedly:

}
