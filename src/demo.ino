#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <ImprovWiFiLibrary.h>

bool connectWifi(const char *ssid, const char *password) {
  WiFi.persistent(true);
  WiFi.begin(ssid, password);
  WiFi.persistent(false);

  return true;
}

void setup() {
  Serial.begin(115200);

  WiFiManager wm;
  wm.setConfigPortalBlocking(false);
  wm.erase(true);

  ImprovWiFi improvSerial(&Serial);

  improvSerial.setDeviceInfo(ImprovTypes::ChipFamily::CF_ESP32, "ImprovWiFiLib", "1.0.0", "ImprovWiFiManager", "http://{LOCAL_IPV4}");
  improvSerial.setCustomConnectWiFi(connectWifi);


  if(!wm.autoConnect("demo", "demo4711")) {
    while(!wm.process()) {
      improvSerial.handleSerial();
      if(improvSerial.isConnected()) {
        wm.stopConfigPortal();
      }
    }
  }

  Serial.println("Setup done");
}

void loop() {   
  Serial.println(WiFi.status());
  delay(5000);
}