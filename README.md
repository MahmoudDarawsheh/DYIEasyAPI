<h1>DIYEasyAPI Arduino Library</h1>

<p><strong>DIYEasyAPI</strong> is an Arduino library that simplifies interfacing with APIs on ESP8266-based NodeMCU boards. It provides an easy-to-use interface for quick prototyping of network and IoT applications, enabling seamless communication over the internet. With DIYEasyAPI, you can easily command your devices, read data from them, and exchange information with third-party services.</p>

<h2>Table of Contents</h2>

<ul>
  <li><a href="#description">Description</a></li>
  <li><a href="#installation">Installation</a></li>
  <li><a href="#dependencies">Dependencies</a></li>
  <li><a href="#usage">Usage</a></li>
  <li><a href="#compatibility">Compatibility</a></li>
  <li><a href="#troubleshooting">Troubleshooting</a></li>
  <li><a href="#credits">Credits</a></li>
</ul>

<h2>Description:</h2>

<p>Develop Your Interface with easy APIs! The <strong>DIYEasyAPI</strong> library includes functions commonly used in personal projects with ESP8266 on NodeMCU boards. The purpose is to simplify network and IoT application development, abstracting communication technicalities from logical functionalities. Use this library to achieve quick communication over the network and internet, such as commanding devices, reading data, and exchanging information with third-party services.</p>

<h2>Installation:</h2>

<ol>
  <li><strong>Download the Library:</strong>
    <ul>
      <li>Go to the releases section of the DIYEasyAPI repository on GitHub: <a href="https://github.com/yourusername/diyeasyapi">Link to Repository</a>.</li>
      <li>Download the latest release version of the library by clicking on the "DIYEasyAPI.zip" file.</li>
    </ul>
  </li>
  <li><strong>Install the Library in Arduino IDE:</strong>
    <ul>
      <li>Open the Arduino IDE.</li>
      <li>Go to <strong>Sketch</strong> &gt; <strong>Include Library</strong> &gt; <strong>Add .ZIP Library...</strong></li>
      <li>Browse to the location where you stored the "DIYEasyAPI.zip" file and select it.</li>
      <li>Click on the "Open" button.</li>
    </ul>
  </li>
  <li><strong>Verify Installation:</strong>
    <ul>
      <li>After successful installation, you should see "DIYEasyAPI" listed under <strong>Sketch</strong> &gt; <strong>Include Library</strong>.</li>
    </ul>
  </li>
</ol>

<h2>Dependencies:</h2>

<p>The DIYEasyAPI library has no additional dependencies other than the ESP8266 library, which is essential for using NodeMCU boards.</p>

<h2>Usage:</h2>

<p>The DIYEasyAPI library consists of three modules: Wifi, Webserver, and SendRequest. Here's a brief overview of each module and its important functions:</p>

<h3>Wifi Module:</h3>

<p>This module handles WiFi connectivity and network configuration. It provides the following functions:</p>

<ul>
  <li><code>bool ConnectToWifi(String ssid, String password, int WaitToConnect, bool Debug)</code>:
    <ul>
      <li>Connects to the WiFi network using the provided SSID and password.</li>
      <li><code>WaitToConnect</code>: Time to wait for WiFi connection (in milliseconds).</li>
      <li><code>Debug</code>: Set to <code>true</code> to enable debug mode for WiFi connection.</li>
    </ul>
  </li>
  <li><code>bool ConnectToWifi(int WaitToConnect, bool Debug, bool UseStaticConfig)</code>:
    <ul>
      <li>Used in projects that use EEPROM to store and read SSID, password, and IP sent via serial for easy setup.</li>
      <li><code>UseStaticConfig</code>: Set to <code>true</code> to use static IP configuration.</li>
    </ul>
  </li>
  <li><code>void PrepareWifiAddress()</code>:
    <ul>
      <li>Reads static IP from EEPROM and returns it after calculating the subnet mask and default gateway.</li>
    </ul>
  </li>
  <li><code>void PrepareWifiAddress(IPAddress selectedIp)</code>:
    <ul>
      <li>Calculates the subnet mask and gateway based on the selected IP.</li>
    </ul>
  </li>
  <li><code>IPAddress calculateSubnetMask(const IPAddress&amp; ip, const IPAddress&amp; gateway)</code>:
    <ul>
      <li>Used internally to calculate the subnet mask.</li>
    </ul>
  </li>
  <li><code>bool RestoreNetworkCreds()</code>:
    <ul>
      <li>Restores network configuration from EEPROM (called internally).</li>
    </ul>
  </li>
  <li><code>void clearEEPROM()</code>:
    <ul>
      <li>Clears the entire EEPROM (use with caution).</li>
    </ul>
  </li>
  <li><code>void storeIPAddress(const String&amp; ipString)</code>:
    <ul>
      <li>Used internally to store the received IP in EEPROM.</li>
    </ul>
  </li>
  <li><code>IPAddress readIPAddressFromEEPROM()</code>:
    <ul>
      <li>Used internally to read the IP from EEPROM.</li>
    </ul>
  </li>
  <li><code>void CheckIfUserChangedNetworkCreds()</code>:
    <ul>
      <li>Must be called in the loop to check if commands were sent to change SSID, password, or IP using the Serial interface.</li>
      <li>Commands allowed: "ssid=YourWifiSSID", "pwd=YourWifiPassword", "ip=YourStaticIp".</li>
    </ul>
  </li>
  <li><code>bool IsWifiConnected()</code>:
    <ul>
      <li>Returns <code>true</code> if WiFi is connected.</li>
    </ul>
  </li>
</ul>

<h3>Webserver Module:</h3>

<p>This module allows you to generate a mini web server with an easy-to-use approach for handling request routes and actions. Important functions include:</p>

<ul>
  <li><code>void InitServer()</code>:
    <ul>
      <li>Call this function after WiFi is connected to initialize the web server.</li>
    </ul>
  </li>
  <li><code>void ListenToServer()</code>:
    <ul>
      <li>Call this function in the loop method to accept requests and handle them.</li>
    </ul>
  </li>
  <li><code>String getQueryParamValue(String qry, String param)</code>:
    <ul>
      <li>Parses a parameter from the query string (called inside the action).</li>
    </ul>
  </li>
  <li><code>dicAction</code>:
    <ul>
      <li>A dictionary of routes and corresponding actions.</li>
      <li>You define the route and the function to be called.</li>
    </ul>
  </li>
</ul>

<h3>SendRequest Module:</h3>

<p>This module contains a function for making HTTP requests. The primary function is:</p>

<ul>
  <li><code>String SendRequest(String url)</code>:
    <ul>
      <li>Pass the URL as a parameter and receive the output as a string.</li>
    </ul>
  </li>
</ul>

<h2>Example 1: WiFi and Web Server Configuration</h2>
<pre><code>#include &lt;DYIEasyAPI.h&gt;
#define RELAY_PIN D8

void turnOn(WiFiClient client, String header) {
  digitalWrite(RELAY_PIN, HIGH);
  client.println("{\"state\":\"on\"}");
}

void turnOff(WiFiClient client, String header) {
  digitalWrite(RELAY_PIN, LOW);
  client.println("{\"state\":\"off\"}");
}

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);

  if (ConnectToWifi(60, true, true)) {
    Serial.println("Connected");

    dicActions["/on"] = turnOn; 
    dicActions["/off"] = turnOff;

    InitServer(); // Start the server
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
</code></pre>

<h2>Example 2: Send HTTP Request</h2>
<pre><code>#include &lt;DYIEasyAPI.h&gt;

void setup() {
  Serial.begin(9600);

  if (ConnectToWifi(60, true, true)) {
    Serial.println("Connected");

    String url = "https://api.example.com/data";
    String response = SendRequest(url);

    Serial.print("API Response: ");
    Serial.println(response);
  } else {
    Serial.println("Not Connected");
  }
}

void loop() {
  // Your loop code here...
  delay(500);
}
</code></pre>

<h2>Example 3: Web Server with HTML and JSON Responses</h2>
<pre><code>#include &lt;DYIEasyAPI.h&gt;
#define RELAY_PIN D8

void turnOn(WiFiClient client, String header) {
  digitalWrite(RELAY_PIN, HIGH);
  client.println("{\"state\":\"on\"}");
}

void turnOff(WiFiClient client, String header) {
  digitalWrite(RELAY_PIN, LOW);
  client.println("{\"state\":\"off\"}");
}

void pulse(WiFiClient client, String header) {
  digitalWrite(RELAY_PIN, HIGH);
  String inchingString = getQueryParamValue(header, "i");
  int inching = inchingString.toInt();
  delay(inching * 1000);
  digitalWrite(RELAY_PIN, LOW);
  String output = "{\"state\":\"on,wait(";
  output.concat(inching);
  output.concat("),off\"}");
  client.println(output);
}

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);

  if (ConnectToWifi(60, true, true)) {
    Serial.println("Connected");

    dicActions["/on"] = turnOn; 
    dicActions["/off"] = turnOff;
    dicActions["/pulse"] = pulse;

    InitServer(); // Start the server
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
</code></pre>

<h2>Example 4: Advanced WiFi Configuration</h2>
<pre><code>#include &lt;DYIEasyAPI.h&gt;

bool UseEEPROMConfig = true;

void setup() {
  Serial.begin(9600);

  int Timeout = 120;
  bool PrintLogsToSerial = true;
  bool UseStaticIp = true;

  bool IsConnectedToWifi = false;

  if (UseEEPROMConfig) {
    IsConnectedToWifi = ConnectToWifi(Timeout, PrintLogsToSerial, UseStaticIp);
  } else {
    String SSID = "YOURNETWORK";
    String Password = "YOURPASSWORD";

    if (UseStaticIp) {
      IPAddress IPstatic(192, 168, 0, 1);
      PrepareWifiAddress(IPstatic);
    }

    IsConnectedToWifi = ConnectToWifi(SSID, Password, Timeout, PrintLogsToSerial);
  }

  if (IsConnectedToWifi) {
    Serial.println("Connected");
  } else {
    Serial.println("Not Connected");
  }
}

void loop() {
  if (!UseEEPROMConfig) {
    CheckIfUserChangedNetworkCreds();
  }

  // Your loop code here...
  delay(500);
}
</code></pre>

<h2>Using Serial to Configure EEPROM:</h2>

<p>To configure the WiFi credentials and static IP in the EEPROM, send the following commands via the Serial interface:</p>

<ol>
  <li>To set the WiFi SSID:
    <pre><code>ssid=YourWifiSSID</code></pre>
  </li>
  <li>To set the WiFi password:
    <pre><code>pwd=YourWifiPassword</code></pre>
  </li>
  <li>To set the static IP (if <code>UseStaticIp</code> is set to <code>true</code> in the <code>setup</code> function):
    <pre><code>ip=YourStaticIp</code></pre>
  </li>
</ol>

<p>Replace <code>YourWifiSSID</code>, <code>YourWifiPassword</code>, and <code>YourStaticIp</code> with your actual WiFi network credentials and desired static IP address (if applicable). The library will store these values in the EEPROM and use them for WiFi configuration during future runs.</p>


<h2>Using Serial to Configure EEPROM:</h2>

<p>To configure the WiFi credentials and static IP in the EEPROM, send the following commands via the Serial interface:</p>

<ol>
  <li>To set the WiFi SSID:
    <pre><code>ssid=YourWifiSSID</code></pre>
  </li>
  <li>To set the WiFi password:
    <pre><code>pwd=YourWifiPassword</code></pre>
  </li>
  <li>To set the static IP (if <code>UseStaticIp</code> is set to <code>true</code> in the <code>setup</code> function):
    <pre><code>ip=YourStaticIp</code></pre>
  </li>
</ol>

<p>Replace <code>YourWifiSSID</code>, <code>YourWifiPassword</code>, and <code>YourStaticIp</code> with your actual WiFi network credentials and desired static IP address (if applicable). The library will store these values in the EEPROM and use them for WiFi configuration during future runs.</p>

<p><strong>Note</strong>: Ensure that you upload the sketch to your Arduino board before sending the configuration commands via Serial.</p>

<h2>Compatibility:</h2>

<p>DIYEasyAPI is specifically designed for ESP8266 boards, particularly NodeMCU. It is tested with Arduino IDE version 1.8.13.</p>

<h2>Troubleshooting:</h2>

<ol>
  <li><strong>No Response from the API</strong>:
    <ul>
      <li>Ensure that your NodeMCU is correctly connected to the internet.</li>
      <li>Double-check the correctness of the API endpoint you are using.</li>
    </ul>
  </li>
  <li><strong>JSON Parsing Errors</strong>:
    <ul>
      <li>Verify that the API response is in valid JSON format.</li>
      <li>Ensure that you are accessing the correct JSON keys in your code.</li>
    </ul>
  </li>
</ol>

<h2>Credits:</h2>

<p>This Library was generated by Eng. Mahmoud Darawsheh while doing some IoT projects, with the aim of making it closer to standard MVC (Model-View-Controller) routes used in many programming languages. By abstracting communication technicalities from logical functionalities, the DIYEasyAPI library provides an efficient and easy-to-use solution for API communication and networking tasks on ESP8266-based NodeMCU boards.</p>
