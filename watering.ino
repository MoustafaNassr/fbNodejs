#include <SPI.h>
#include <WiFi101.h>

char ssid[] = "ApexRoom"; // your network SSID (name)
char pass[] = "20106262";  // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;

String s = "";

int status = WL_IDLE_STATUS;
char server[] = "192.168.70.89"; // from google cloud

int moistureSensorPin = A0; // Analog pin for the moisture sensor

WiFiClient client;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(5000);
  }
  Serial.println("Connected to wifi");
  printWiFiStatus();
}

void loop() {
  int moistureValue = analogRead(moistureSensorPin);
  Serial.print("Moisture Value: ");
  Serial.println(moistureValue);

  if (client.connect(server, 8080)) {
    s = "GET /?moisture=";
    s += String(moistureValue);
    s += " HTTP/1.1\r\nHost: 192.168.70.89:8080\r\nConnection: close\r\n\r\n";

    Serial.println("Connected to server");
    client.println(s);
    client.println("Connection: close");
    client.println();
    Serial.println("Moisture value sent to server");
  }

  delay(30000); // Wait for 1 minute before sending the next moisture value
}

void printWiFiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
