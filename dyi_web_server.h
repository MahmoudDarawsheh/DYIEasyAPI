#ifndef DYI_WEB_SERVER_H
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#define ServerName "dyiserver-01"


 extern std::map<String, void (*)(WiFiClient, String)> dicActions;
 extern  std::map<String, String> dicMemeType;

  String getQueryParamValue(String qry, String param);
  void HttpRequestHandlers(WiFiClient client, String reqHeader, std::map<String, void (*)(WiFiClient, String)> requestHandler);
 void HttpMimeTypeHandler(WiFiClient client,String reqHeader, std::map<String,String> dicMemeType);
  void ListenToServer();
 
  void SetHostNameToDNS(bool Debug);
  void InitServer();
  void UpdateMDNS();
  void UseHTML(String route);
  void UseJSON(String route);
  void UseTEXT(String route);
  void UseCustom(String route,String contenType);
  void SetDefaultRoute(String Route);
  void SetDefaultMemeType(String meme);
#endif