#include "dyi_http_request.h"
WiFiClient client;
HTTPClient httpClient;
String SendSecureRequest(String url, bool debug) {
  // Parse the URL to extract hostname, port, and path
  String protocol, hostname, path;
  int port;

  if (url.startsWith("http://")) {
    protocol = "http";
    url.remove(0, 7);
  } else if (url.startsWith("https://")) {
    protocol = "https";
    url.remove(0, 8);
  } else {
    if (debug) {
      //serial.println("Invalid URL protocol");
    }
    return "";
  }

  int pathIndex = url.indexOf('/');
  if (pathIndex != -1) {
    hostname = url.substring(0, pathIndex);
    path = url.substring(pathIndex);
  } else {
    hostname = url;
    path = "/";
  }

  int portIndex = hostname.indexOf(':');
  if (portIndex != -1) {
    port = hostname.substring(portIndex + 1).toInt();
    hostname = hostname.substring(0, portIndex);
  } else {
    port = (protocol == "https") ? 443 : 80;
  }

  // Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  if (debug) {
    //serial.print("Connecting to ");
    //serial.print(hostname);
    //serial.print(":");
    //serial.println(port);
  }

  client.setInsecure(); // Disable certificate verification

  if (!client.connect(hostname, port)) {
    if (debug) {
      //serial.println("Connection failed");
    }
    return "";
  }

  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: " + hostname + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n");

  if (debug) {
    //serial.println("Request sent");
  }

  String response;
  bool isBody = false; // Flag to start storing the body

  while (client.connected() || client.available()) {
    if (client.available()) {
      String line = client.readStringUntil('\n');
      if (!isBody) {
        // Check for the end of the response headers
        if (line == "\r") {
          isBody = true;
          if (debug) {
            //serial.println("Response headers received");
          }
        } else {
          if (debug) {
            //serial.println(line);
          }
        }
      } else {
        // Store the response body
        response += line;
      }
    }
  }

  if (debug) {
    //serial.println("Closing connection");
  }

  return response;
}
String SendRequest(String url, bool debug = false) {
  if (url.startsWith("https://")) {
    return SendSecureRequest(url, debug);
  }

  // HTTP Request
  digitalWrite(D3, LOW);
  if (WiFi.status() == WL_CONNECTED) {
    if (debug) {
      //serial.println("Trying to send HTTP request to ring the bell");
    }
    HTTPClient httpClient;
    httpClient.begin(client, url.c_str());

    httpClient.GET();
    String content = httpClient.getString();
    httpClient.end();

    if (debug) {
      //serial.println(content);
      //serial.println("Notifying Deaf users");
    }
    
    digitalWrite(D3, HIGH);
    return content;
  } else {
    if (debug) {
      //serial.println("WiFi connection fails");
    }
    digitalWrite(D3, LOW);
  }

  return "";
}
String SendRequest(String url)
{
return SendRequest(url,true);

}