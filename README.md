# Zentrale Datenerfassung für CO2 Ampel

Der ESP8266 hat WLAN und unterstützt verschiedene Netzwerkprotokolle. Zusätzlich zur lokalen Anzeige könnten Messwerte auch zentral gesammelt und visalisiert werden.

![Context](context.drawio.svg)

Idee:

- CO2Ampel wird an Schul-WLAN angebunden
- CO2 Werte werden neben der lokalen Anzeige auch als MQTT Nachricht versendet
- Mit Node Red wird ein Listener auf MQTT Nachrichten der Ampeln eingerichtet
- Für jede Nachricht werden die Daten in die Zeitreihendatenbank InfluxDB gespeichert
- Mit Chronograph können die Daten aus InfluxDB visialisiert werden


### Verbinden mit WLAN

Die Bibliothek Wifimanager ermöglicht, WLAN SSID und Passwort über ein Webconfig einzugeben. Diese werden dann im EEPROM gespeichert.
So muss die Konfiguration nur einmal gemacht werden.

https://github.com/tzapu/WiFiManager

Zusätzlich zu den Wifidaten kann man auch weitere Parameter abfragen. Z.B.: MQTT Server und topic der Ampel.

### Senden der Daten per MQTT

PubSubClient ermöglicht senden und empfangen von MQTT Nachrichten.
Im Beispiel wird der Verbindungsaufbau in setup gamacht. Besser wäre noch, den Verbingungsaufbau asynchron im loop zu machen. 
Damit startet das System schneller und kann bei Verbindungsabbruch auch neu connecten.

## Server

### MQTT

Als MQTT Server eignet sich mosquito sehr gut. Es ist in Linux sehr einfach zu installieren und kann erst mal ohne weitere Konfiguration genutzt werden.

### InfluxDB

[InfluxDB](https://www.influxdata.com/) ist eine spezielle Zeitreihendatenbank. Die Installation sollte ebenfalls recht einfach per Paketmanager erfolgen.

### Chronograph

[Chronograph](https://www.influxdata.com/time-series-platform/chronograf/) ist eine Visualisierung für Zeitreihen und erlaubt, ansprechende Dashboards zu gestalten.

### Node Red

Mit [Node Red](https://nodered.org/) können die MQTT Nachrichten empfangen und in InfluxDB geschrieben werden.

## Cloud

Alternativ zur Installation auf dem eigenen Server könnte InfluxDB und Chronograph auch in der Cloud betrieben werden. 
Der Einstieg ist kostenlos und damit vielleicht die schnellste Lösung. 

## Alternative zu MQTT

Alternativ zu MQTT Nachrichten kann man die Messwerte auch direkt in InfluxDB hochladen. Das würde die Infrastruktur einfacher machen, aber auch weniger flexibel.
