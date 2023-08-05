#include <DYIEasyAPI.h>

/* DYIEasyAPI :Develop Your Interface with easy apis
 * in this example we will Send HTTP request to some of the public apis print the output to serial
 * the output is string always you can then replace the urls with your project urls to get strings such as commands or send data to web api and store it somewhere
 * 1- connect device to any serial terminal such as serial monitor or on your phone with OTG Cable to the device.
 * 2- wait until the device fails to connect to wifi
 * 3- send to serial ssid=YOURWIFISSID then enter
 * 4- it will promote to you sending password enter pwd=YOURWIFIPASSWORD
 * 5- Now check the output on serial monitor
 * note that these apis are referred to their owners and authors , we are just using them for demo purposes if you want to use them in your project check with their licenses
 * you can get more apis also  from this url https://github.com/davemachado/public-api some of them where known as free to use apis for non comercail use
 */
#include<DYIEasyAPI.h>

#define WaitTimeBetweenReq 20



void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  if (ConnectToWifi( 60, true,false)) {// to see ConnectToWifi details check Wifi Examples
    Serial.println("Connected");
  } else {
    Serial.println("Not Connected");
  }

}

void loop() {
  CheckIfUserChangedNetworkCreds();//check if command was sent to change ssid,pwd or ip using serial

  if( IsWifiConnected())
  {

    // getting weather in Amman based on longitude,latitude
  float Latitude=31.96315;
  float Longitude =35.930359;
  
  Serial.println("Weather in Amman info:");
  Serial.println( SendRequest("https://api.open-meteo.com/v1/forecast?latitude="+String(Latitude)+"&longitude="+String(Longitude)+"&current_weather=true",false)); 

  delay(WaitTimeBetweenReq *1000);

  Serial.println("Random activity  info:"); 
  Serial.println( SendRequest("https://www.boredapi.com/api/activity",false));

  
  delay(WaitTimeBetweenReq *1000);
  
  Serial.println("Get a random joke"); 
  Serial.println( SendRequest("https://official-joke-api.appspot.com/random_joke",false));

  delay(WaitTimeBetweenReq *1000);

  }
  delay(20000);
  
  // put your main code here, to run repeatedly:

}
