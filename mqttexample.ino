#include <ESP8266WiFi.h>          // ESP8266 Core WiFi Library (already in Board libraries)
#include <DNSServer.h>            // Redirect all requests to configuration portal
#include <ESP8266WebServer.h>     // Serves the configuration portal
#include <WiFiManager.h>          // WifiManager from tzapu https://github.com/tzapu/WiFiManager Web based WiFi Configuration
#include <PubSubClient.h>         // Send or receive MQTT messages

WiFiManager wifiManager;
WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
  Serial.begin(115200);
  Serial.println();
  WiFiManagerParameter custom_mqtt_server("server", "mqtt server", "192.168.0.126", 40);
  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.autoConnect("CO2Ampel");
  WiFi.begin();

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  const char* mqtt_server = custom_mqtt_server.getValue();
  Serial.print("MQTT server: ");
  Serial.println(mqtt_server);
  client.setServer(mqtt_server, 1883);
  reconnect();
}

void loop() {
  client.publish("/co2ampel/10a", "test");
  Serial.println("published message");
  delay(2000);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT server...");
    String clientId = "CO2Ampel-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("connect failure, error code=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}
