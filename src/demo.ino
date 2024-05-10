#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <ImprovWiFiLibrary.h>

void onImprovWiFiErrorCb(ImprovTypes::Error err) {
}

void onImprovWiFiConnectedCb(const char *ssid, const char *password) {
}

bool connectWifi(const char *ssid, const char *password) {
  /*WiFi.begin(ssid, password);

  while (!improvSerial.isConnected())
  {
    blink_led(500, 1);
  }*/

  return true;
}

void setup() {
  Serial.begin(115200);

  WiFiManager wm;
  wm.setConfigPortalBlocking(false);
  wm.erase(true);

  ImprovWiFi improvSerial(&Serial);

  improvSerial.setDeviceInfo(ImprovTypes::ChipFamily::CF_ESP32, "ImprovWiFiLib", "1.0.0", "ImprovWiFiManager", "http://{LOCAL_IPV4}?name=Guest");
  improvSerial.onImprovError(onImprovWiFiErrorCb);
  improvSerial.onImprovConnected(onImprovWiFiConnectedCb);
  improvSerial.setCustomConnectWiFi(connectWifi);


  if(!wm.autoConnect("demo", "demo4711")) {
    while(!wm.process()) {
      improvSerial.handleSerial();
    }
  }

  Serial.println("Setup done");
}

void loop() {   

}