#include "dyi_web_server.h"


WiFiServer server(80);
String header;
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

 std::map<String, void (*)(WiFiClient, String)> dicActions;
 std::map<String, String> dicMemeType;
 String defaultRoute=""; 
 String defaultMemeType="";
void InitServer()
{

server.begin();
MDNS.addService("http", "tcp", 80);
}
String getQueryParamValue(String qry, String param) {
  // Find the starting index of the parameter in the query string
  int paramStartIndex = qry.indexOf(param + "=");
  if (paramStartIndex != -1) {
    // Skip the parameter name and "=" to extract the value
    int valueStartIndex = paramStartIndex + param.length() + 1;

    // Find the ending index of the parameter value
    int valueEndIndex = qry.indexOf('&', valueStartIndex);
    if (valueEndIndex == -1) {
      valueEndIndex = qry.length(); // In case there are no more parameters
    }

    // Extract the parameter value from the query string
    String value = qry.substring(valueStartIndex, valueEndIndex);

    // Handle URL encoding (replace %20 with space and + with space)
    value.replace("%20", " ");
    value.replace("+", " ");

    return value;
  }

  // Return an empty string if the parameter is not found in the query string
  return "";
}

void HttpMimeTypeHandler(WiFiClient client,String reqHeader, std::map<String,String> dicMemeType) {
  String header = reqHeader;
  header.trim();
  if (header.startsWith( "GET ")) {
    header = header.substring(4);
  }else{

   
  }

  bool anyRouteCalled = false;

  client.print("Content-Type: ");
  for (const auto& route : dicMemeType) {
    // route.first represents header
    if (header.startsWith( route.first)) {
      client.println(route.second);
      anyRouteCalled = true;
      break;
    }
  }

  if (!anyRouteCalled) {
    if(defaultMemeType=="")
    {

     client.println("text/json");
    }else{
      client.println(defaultMemeType.c_str());
    }
  }
}
void HttpRequestHandlers(WiFiClient client, String reqHeader, std::map<String, void (*)(WiFiClient, String)> requestHandler) {
  String header = reqHeader;
  header.trim();
  if (header.startsWith( "GET ")) {
    header = header.substring(4);
  }else{

   
  }

  bool anyRouteCalled = false;

  for (const auto& route : requestHandler) {
    // route.first represents header
    if (header.startsWith( route.first)) {
      route.second(client, header);
      anyRouteCalled = true;
      return;
    }
  }

  if (!anyRouteCalled) {
    // Handle a default response if no route matches
    if(defaultRoute==""){
      
    client.println("HTTP/1.1 404 Not Found");
    client.println("Content-Type: text/plain");
    client.println();
    client.println("404 Not Found");
    }else{
      requestHandler[defaultRoute](client,header);
    }
  }
}
void SetDefaultRoute(String Route)
{
    defaultRoute=Route;
}
void SetDefaultMemeType(String meme)
{
    defaultMemeType=meme;
}

  void UseHTML(String route){
  UseCustom(route,"text/html");
  }
  void UseJSON(String route){
  UseCustom(route,"text/json");
  }
  void UseTEXT(String route){
  UseCustom(route,"text/plain");
  }
  void UseJS(String route){
  UseCustom(route,"text/javascript");
  }
  void UseCSS(String route){
  UseCustom(route,"text/css");
  }
  void UseCustom(String route,String contenType){
     String ctype="Content-Type: ";
     ctype.concat(contenType);
     dicMemeType[route]=contenType;
  }
void SetHostNameToDNS(bool Debug)
 {
 if (!MDNS.begin(ServerName)) {
      if (Debug) {
        Serial.println("fail to set MDNS");
      }
    } else {

      if (Debug) {
        Serial.println("app is running on http://deafbell-01/");
      }
    }
 }


void ListenToServer() {

  WiFiClient client = server.available();
  if (client) {                     // If a new client connects,
    Serial.println("New Client.");  // print a message out in the serial port
    String currentLine = "";        // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {  // if there's bytes to read from the client,
        char c = client.read();  // read a byte, then
        Serial.write(c);         // print it out the serial monitor
        header += c;
        if (c == '\n') {  // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            HttpMimeTypeHandler(client,header,dicMemeType);
            client.println("Connection: close");
            client.println();
            HttpRequestHandlers(client, header, dicActions);
            client.println();
            // Break out of the while loop
            break;
          } else {  // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
void UpdateMDNS()
{
  MDNS.update();
}

