#include <DYIEasyAPI.h>

#include<DYIEasyAPI.h>
void Index(WiFiClient client, String header) {

 client.println("<html>");
 client.println("   <head>");
 client.println("       <title>Sample Page</title>");
 client.println("   </head>");
 client.println("   <body>");
 client.println("       <H1>");
 client.println("           <strong>Hello</strong> Wolrd");
 client.println("       </H1>");
 client.println("   </body>");
 client.println("</html>");
}
void Json(WiFiClient client, String header) {

 client.println("{");
 client.print("\"command\":");
 client.println("\"hello world\",");
 
 client.print("\"success\":");
 client.println("\"true\",");
 
 client.print("\"type\":");
 client.println("\"json\",");
 
 client.println("}");
}


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  if (ConnectToWifi( 60, true,true)) {// to see ConnectToWifi details check Wifi Examples
    Serial.println("Connected");
    SetHostNameToDNS(true);
   
    UseJSON("/json"); 
    dicActions["/json"] = Json; 
    
    UseHTML("/Index");             
    dicActions["/Index"] = Index;  

    SetDefaultRoute("/Index"); 
    SetDefaultMemeType("text/html");

    InitServer();

  } else {
    Serial.println("Not Connected");
  }

}

void loop() {
  CheckIfUserChangedNetworkCreds();
  UpdateMDNS();
  ListenToServer();

  delay(500);
  
}
