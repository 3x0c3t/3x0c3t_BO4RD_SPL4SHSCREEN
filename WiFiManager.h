#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <LittleFS.h>

#include "WiFi.h"

// ==================================================
// WIFI STRUCTURE
// ==================================================

struct WiFiNetwork {

  String ssid;
  String password;
};

// ==================================================
// WIFI STORAGE
// ==================================================

WiFiNetwork wifiNetworks[MAX_WIFI_NETWORKS];

int wifiNetworkCount = 0;

// ==================================================
// LOAD CONFIGURATION
// ==================================================

void loadWiFiConfiguration() {

  wifiNetworkCount = 0;

  // ------------------------------------------------
  // DEFAULT NETWORK
  // ------------------------------------------------

  wifiNetworks[0].ssid =
    String(WIFI_SSID);

  wifiNetworks[0].password =
    String(WIFI_PASSWORD);

  wifiNetworkCount = 1;

  // ------------------------------------------------
  // CONFIG FILE
  // ------------------------------------------------

  if (!LittleFS.exists("/wifi.cfg")) {

    return;
  }

  File file =
    LittleFS.open(
      "/wifi.cfg",
      "r"
    );

  if (!file) {

    return;
  }

  while (
    file.available() &&
    wifiNetworkCount < MAX_WIFI_NETWORKS
  ) {

    String line =
      file.readStringUntil('\n');

    line.trim();

    if (line.length() == 0) {

      continue;
    }

    int separator =
      line.indexOf('|');

    if (separator <= 0) {

      continue;
    }

    String ssid =
      line.substring(
        0,
        separator
      );

    String password =
      line.substring(
        separator + 1
      );

    ssid.trim();
    password.trim();

    if (ssid.length() == 0) {

      continue;
    }

    bool duplicate = false;

    for (
      int i = 0;
      i < wifiNetworkCount;
      i++
    ) {

      if (
        wifiNetworks[i].ssid ==
        ssid
      ) {

        duplicate = true;

        break;
      }
    }

    if (!duplicate) {

      wifiNetworks[
        wifiNetworkCount
      ].ssid = ssid;

      wifiNetworks[
        wifiNetworkCount
      ].password = password;

      wifiNetworkCount++;
    }
  }

  file.close();
}

// ==================================================
// SAVE CONFIGURATION
// ==================================================

bool saveWiFiConfiguration() {

  File file =
    LittleFS.open(
      "/wifi.cfg",
      "w"
    );

  if (!file) {

    return false;
  }

  // Network 0 comes from WiFi.h.
  // Additional networks are stored here.

  for (
    int i = 1;
    i < wifiNetworkCount;
    i++
  ) {

    file.print(
      wifiNetworks[i].ssid
    );

    file.print("|");

    file.println(
      wifiNetworks[i].password
    );
  }

  file.close();

  return true;
}

// ==================================================
// SET NETWORK
// ==================================================

bool setWiFiNetwork(
  int index,
  const String &ssid,
  const String &password
) {

  if (
    index < 1 ||
    index >= MAX_WIFI_NETWORKS
  ) {

    return false;
  }

  if (
    ssid.length() == 0
  ) {

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
// DELETE NETWORK
// ==================================================

bool deleteWiFiNetwork(
  int index
) {

  if (
    index <= 0 ||
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

  wifiNetworkCount--;

  return saveWiFiConfiguration();
}

// ==================================================
// WIFI RSSI
// ==================================================

int getWiFiRSSI() {

  if (
    WiFi.status() != WL_CONNECTED
  ) {

    return 0;
  }

  return WiFi.RSSI();
}

// ==================================================
// CONNECT
// ==================================================

bool connectWiFi() {

  Serial.println();
  Serial.println(
    "=== WIFI CONNECTION ==="
  );

  WiFi.mode(
    WIFI_STA
  );

  WiFi.disconnect();

  delay(250);

  // ------------------------------------------------
  // SCAN
  // ------------------------------------------------

  int found =
    WiFi.scanNetworks();

  Serial.print(
    "Networks found: "
  );

  Serial.println(
    found
  );

  // ------------------------------------------------
  // PRIORITY ORDER
  // ------------------------------------------------

  for (
    int priority = 0;
    priority < wifiNetworkCount;
    priority++
  ) {

    String targetSSID =
      wifiNetworks[
        priority
      ].ssid;

    String targetPassword =
      wifiNetworks[
        priority
      ].password;

    Serial.print(
      "Trying: "
    );

    Serial.println(
      targetSSID
    );

    bool networkFound =
      false;

    for (
      int i = 0;
      i < found;
      i++
    ) {

      if (
        WiFi.SSID(i) ==
        targetSSID
      ) {

        networkFound = true;

        break;
      }
    }

    if (!networkFound) {

      Serial.println(
        "  Not found"
      );

      continue;
    }

    WiFi.begin(
      targetSSID.c_str(),
      targetPassword.c_str()
    );

    unsigned long start =
      millis();

    while (
      WiFi.status() != WL_CONNECTED &&
      millis() - start < 10000
    ) {

      delay(250);

      Serial.print(".");
    }

    Serial.println();

    if (
      WiFi.status() ==
      WL_CONNECTED
    ) {

      Serial.println(
        "WiFi connected"
      );

      Serial.print(
        "SSID: "
      );

      Serial.println(
        WiFi.SSID()
      );

      Serial.print(
        "IP: "
      );

      Serial.println(
        WiFi.localIP()
      );

      WiFi.scanDelete();

      return true;
    }

    Serial.println(
      "Connection failed"
    );

    WiFi.disconnect();

    delay(250);
  }

  WiFi.scanDelete();

  Serial.println(
    "No WiFi network available"
  );

  return false;
}

#endif