#ifndef WIFI_MANAGER_CUSTOM_H
#define WIFI_MANAGER_CUSTOM_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <LittleFS.h>

#include "WiFi.h"

#define MAX_WIFI_NETWORKS 5
#define WIFI_CONFIG_FILE "/wifi.cfg"
#define WIFI_CONNECT_TIMEOUT 10000

struct WiFiNetwork {
  String ssid;
  String password;
};

WiFiNetwork wifiNetworks[MAX_WIFI_NETWORKS];
int wifiNetworkCount = 0;

bool setupAPActive = false;

// ==================================================
// RSSI
// ==================================================

int getWiFiRSSI() {

  if (WiFi.status() != WL_CONNECTED) {
    return 0;
  }

  return WiFi.RSSI();
}

// ==================================================
// LITTLEFS
// ==================================================

bool initWiFiStorage() {

  if (LittleFS.begin()) {
    Serial.println("LittleFS ready");
    return true;
  }

  Serial.println("LittleFS mount failed");
  return false;
}

// ==================================================
// LOAD WIFI CONFIGURATION
// ==================================================

bool loadWiFiConfiguration() {

  wifiNetworkCount = 0;

  if (!LittleFS.exists(WIFI_CONFIG_FILE)) {

    Serial.println("No WiFi configuration found");
    return false;
  }

  File file = LittleFS.open(
    WIFI_CONFIG_FILE,
    "r"
  );

  if (!file) {

    Serial.println("Unable to open WiFi configuration");
    return false;
  }

  while (
    file.available() &&
    wifiNetworkCount < MAX_WIFI_NETWORKS
  ) {

    String ssid =
      file.readStringUntil('\n');

    String password =
      file.readStringUntil('\n');

    ssid.trim();
    password.trim();

    if (ssid.length() > 0) {

      wifiNetworks[wifiNetworkCount].ssid =
        ssid;

      wifiNetworks[wifiNetworkCount].password =
        password;

      wifiNetworkCount++;
    }
  }

  file.close();

  Serial.print("Loaded WiFi networks: ");
  Serial.println(wifiNetworkCount);

  return wifiNetworkCount > 0;
}

// ==================================================
// SAVE WIFI CONFIGURATION
// ==================================================

bool saveWiFiConfiguration() {

  File file = LittleFS.open(
    WIFI_CONFIG_FILE,
    "w"
  );

  if (!file) {

    Serial.println("Unable to save WiFi configuration");
    return false;
  }

  for (
    int i = 0;
    i < wifiNetworkCount;
    i++
  ) {

    file.println(
      wifiNetworks[i].ssid
    );

    file.println(
      wifiNetworks[i].password
    );
  }

  file.close();

  Serial.println("WiFi configuration saved");

  return true;
}

// ==================================================
// SET WIFI NETWORK
// ==================================================

bool setWiFiNetwork(
  int index,
  const String &ssid,
  const String &password
) {

  if (
    index < 0 ||
    index >= MAX_WIFI_NETWORKS
  ) {
    return false;
  }

  if (ssid.length() == 0) {
    return false;
  }

  wifiNetworks[index].ssid =
    ssid;

  wifiNetworks[index].password =
    password;

  if (
    index >= wifiNetworkCount
  ) {

    wifiNetworkCount =
      index + 1;
  }

  return true;
}

// ==================================================
// DELETE WIFI NETWORK
// ==================================================

bool deleteWiFiNetwork(
  int index
) {

  if (
    index < 0 ||
    index >= wifiNetworkCount
  ) {
    return false;
  }

  for (
    int i = index;
    i < wifiNetworkCount - 1;
    i++
  ) {

    wifiNetworks[i] =
      wifiNetworks[i + 1];
  }

  wifiNetworks[
    wifiNetworkCount - 1
  ].ssid = "";

  wifiNetworks[
    wifiNetworkCount - 1
  ].password = "";

  wifiNetworkCount--;

  return saveWiFiConfiguration();
}

// ==================================================
// START SETUP ACCESS POINT
// ==================================================

void startSetupAccessPoint() {

  String apSSID =
    String(BOARD_ID) +
    String(SETUP_AP_SUFFIX);

  Serial.println();
  Serial.println("================================");
  Serial.println("WIFI CONFIGURATION MODE");
  Serial.println("================================");

  WiFi.mode(WIFI_AP);

  WiFi.softAP(
    apSSID.c_str(),
    BOARD_PASSWORD
  );

  setupAPActive = true;

  Serial.print("AP SSID: ");
  Serial.println(apSSID);

  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());
}

// ==================================================
// STOP SETUP ACCESS POINT
// ==================================================

void stopSetupAccessPoint() {

  if (!setupAPActive) {
    return;
  }

  WiFi.softAPdisconnect(true);

  setupAPActive = false;

  Serial.println("Setup AP stopped");
}

// ==================================================
// CONNECT TO SAVED WIFI
// ==================================================

bool connectWiFi() {

  if (wifiNetworkCount <= 0) {

    Serial.println("No WiFi network configured");
    return false;
  }

  WiFi.mode(WIFI_STA);

  for (
    int i = 0;
    i < wifiNetworkCount;
    i++
  ) {

    Serial.println();
    Serial.print("Trying WiFi: ");
    Serial.println(
      wifiNetworks[i].ssid
    );

    WiFi.disconnect();

    delay(300);

    WiFi.begin(
      wifiNetworks[i].ssid.c_str(),
      wifiNetworks[i].password.c_str()
    );

    unsigned long start =
      millis();

    while (
      WiFi.status() != WL_CONNECTED &&
      millis() - start < WIFI_CONNECT_TIMEOUT
    ) {

      delay(250);

      Serial.print(".");
    }

    Serial.println();

    if (
      WiFi.status() == WL_CONNECTED
    ) {

      Serial.println("WiFi connected");

      Serial.print("SSID: ");
      Serial.println(WiFi.SSID());

      Serial.print("IP: ");
      Serial.println(WiFi.localIP());

      setupAPActive = false;

      return true;
    }

    Serial.println("Connection failed");
  }

  Serial.println("All WiFi networks failed");

  return false;
}

// ==================================================
// WIFI CONFIGURED?
// ==================================================

bool isWiFiConfigured() {

  return wifiNetworkCount > 0;
}

#endif
