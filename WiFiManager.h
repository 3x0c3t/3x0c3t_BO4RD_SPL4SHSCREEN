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


// ============================================================
// RSSI
// ============================================================

int getWiFiRSSI() {
  if (WiFi.status() != WL_CONNECTED) {
    return 0;
  }

  return WiFi.RSSI();
}


// ============================================================
// LITTLEFS
// ============================================================

bool initWiFiStorage() {
  if (LittleFS.begin()) {
    return true;
  }

  return false;
}


// ============================================================
// LOAD CONFIGURATION
// ============================================================

bool loadWiFiConfiguration() {
  wifiNetworkCount = 0;

  if (!LittleFS.exists(WIFI_CONFIG_FILE)) {
    return false;
  }

  File file = LittleFS.open(
    WIFI_CONFIG_FILE,
    "r"
  );

  if (!file) {
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

  return wifiNetworkCount > 0;
}


// ============================================================
// SAVE CONFIGURATION
// ============================================================

bool saveWiFiConfiguration() {
  File file = LittleFS.open(
    WIFI_CONFIG_FILE,
    "w"
  );

  if (!file) {
    return false;
  }

  for (int i = 0; i < wifiNetworkCount; i++) {
    file.println(
      wifiNetworks[i].ssid
    );

    file.println(
      wifiNetworks[i].password
    );
  }

  file.close();

  return true;
}


// ============================================================
// SET NETWORK
// ============================================================

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

  if (index >= wifiNetworkCount) {
    wifiNetworkCount =
      index + 1;
  }

  return true;
}


// ============================================================
// DELETE NETWORK
// ============================================================

bool deleteWiFiNetwork(int index) {
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

  wifiNetworks[wifiNetworkCount - 1].ssid =
    "";

  wifiNetworks[wifiNetworkCount - 1].password =
    "";

  wifiNetworkCount--;

  return saveWiFiConfiguration();
}


// ============================================================
// SETUP ACCESS POINT
// ============================================================

void startSetupAccessPoint() {
  String apSSID =
    String(BOARD_ID) +
    String(SETUP_AP_SUFFIX);

  WiFi.mode(WIFI_AP);

  WiFi.softAP(
    apSSID.c_str(),
    BOARD_PASSWORD
  );

  setupAPActive = true;

  Serial.print("WIFI | SETUP_AP | SSID=");
  Serial.print(apSSID);

  Serial.print(" | IP=");
  Serial.println(
    WiFi.softAPIP()
  );
}


// ============================================================
// STOP ACCESS POINT
// ============================================================

void stopSetupAccessPoint() {
  if (!setupAPActive) {
    return;
  }

  WiFi.softAPdisconnect(true);

  setupAPActive = false;

  Serial.println("WIFI | SETUP_AP | STOP");
}


// ============================================================
// CONNECT WIFI
// ============================================================

bool connectWiFi() {
  if (wifiNetworkCount <= 0) {
    Serial.println("WIFI | NO_CONFIG");
    return false;
  }

  WiFi.mode(WIFI_STA);

  for (
    int i = 0;
    i < wifiNetworkCount;
    i++
  ) {
    Serial.print("WIFI | TRY=");
    Serial.print(i + 1);

    Serial.print(" | SSID=");
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
      millis() - start <
        WIFI_CONNECT_TIMEOUT
    ) {
      delay(250);
    }

    if (
      WiFi.status() ==
      WL_CONNECTED
    ) {
      setupAPActive = false;

      Serial.print("WIFI | CONNECTED | SSID=");
      Serial.print(
        WiFi.SSID()
      );

      Serial.print(" | IP=");
      Serial.println(
        WiFi.localIP()
      );

      return true;
    }

    Serial.print("WIFI | FAIL | SSID=");
    Serial.println(
      wifiNetworks[i].ssid
    );
  }

  Serial.println("WIFI | ALL_FAIL");

  return false;
}


// ============================================================
// CONFIGURATION STATUS
// ============================================================

bool isWiFiConfigured() {
  return wifiNetworkCount > 0;
}

#endif