#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <ImprovWiFiLibrary.h>

WiFiManager wm;

bool connectWifi(const char *ssid, const char *password) {
  wm.stopConfigPortal();

  WiFi.persistent(true);
  WiFi.begin(ssid, password, 0, NULL, true);
  WiFi.persistent(false);

  uint8_t count = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(DELAY_MS_WAIT_WIFI_CONNECTION);
    if (count > MAX_ATTEMPTS_WIFI_CONNECTION)
    {
      WiFi.disconnect();
      return false;
    }
    count++;
  }

  return true;
}

void setup() {
  Serial.begin(115200);

  wm.setConfigPortalBlocking(false);
  //wm.erase(true);

  ImprovWiFi improvSerial(&Serial);

  improvSerial.setDeviceInfo(ImprovTypes::ChipFamily::CF_ESP32, "ImprovWiFiLib", "1.0.0", "ImprovWiFiManager", "http://{LOCAL_IPV4}");
  improvSerial.setCustomConnectWiFi(connectWifi);


  if(!wm.autoConnect("demo", "demo4711")) {
    while(!wm.process()) {
      improvSerial.handleSerial();
      if(improvSerial.isConnected()) {
        break;
      }
    }
  }

  Serial.println("Setup done");
}


void loop() {   
  Serial.println(WiFi.status());
  delay(5000);
}