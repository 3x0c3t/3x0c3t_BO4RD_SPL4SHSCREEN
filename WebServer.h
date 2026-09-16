#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "WiFi.h"
#include "WiFiManager.h"

#include "pageWebHTML.h"
#include "pageWebCSS.h"
#include "pageWebJS.h"

ESP8266WebServer server(80);

// ==================================================
// ROOT
// ==================================================

void handleRoot() {

  server.send_P(
    200,
    "text/html; charset=utf-8",
    PAGE_WEB_HTML
  );
}

// ==================================================
// CSS
// ==================================================

void handleCSS() {

  server.send_P(
    200,
    "text/css",
    PAGE_WEB_CSS
  );
}

// ==================================================
// JS
// ==================================================

void handleJS() {

  server.send_P(
    200,
    "application/javascript",
    PAGE_WEB_JS
  );
}

// ==================================================
// STATUS
// ==================================================

void handleStatus() {

  String json = "{";

  json += "\"board\":\"";
  json += BOARD_ID;
  json += "\",";

  json += "\"configured\":";
  json += (
    isWiFiConfigured()
      ? "true"
      : "false"
  );

  json += ",";

  json += "\"connected\":";
  json += (
    WiFi.status() == WL_CONNECTED
      ? "true"
      : "false"
  );

  json += ",";

  json += "\"setupAP\":";
  json += (
    setupAPActive
      ? "true"
      : "false"
  );

  json += ",";

  json += "\"ssid\":\"";

  if (
    WiFi.status() == WL_CONNECTED
  ) {

    json += WiFi.SSID();

  } else if (
    setupAPActive
  ) {

    json += String(BOARD_ID);
    json += SETUP_AP_SUFFIX;
  }

  json += "\",";

  json += "\"ip\":\"";

  if (
    WiFi.status() == WL_CONNECTED
  ) {

    json +=
      WiFi.localIP().toString();

  } else {

    json +=
      WiFi.softAPIP().toString();
  }

  json += "\",";

  json += "\"rssi\":";
  json += String(
    getWiFiRSSI()
  );

  json += "}";

  server.send(
    200,
    "application/json",
    json
  );
}

// ==================================================
// WIFI LIST
// ==================================================

void handleWiFiList() {

  String json = "[";

  for (
    int i = 0;
    i < wifiNetworkCount;
    i++
  ) {

    if (i > 0) {
      json += ",";
    }

    json += "{";

    json += "\"index\":";
    json += String(i);
    json += ",";

    json += "\"ssid\":\"";
    json += wifiNetworks[i].ssid;
    json += "\",";

    json += "\"priority\":";
    json += (
      i == 0
        ? "true"
        : "false"
    );

    json += "}";
  }

  json += "]";

  server.send(
    200,
    "application/json",
    json
  );
}

// ==================================================
// WIFI SAVE
// ==================================================

void handleWiFiSave() {

  if (
    !server.hasArg("index") ||
    !server.hasArg("ssid") ||
    !server.hasArg("password")
  ) {

    server.send(
      400,
      "text/plain",
      "Missing parameters"
    );

    return;
  }

  int index =
    server.arg("index").toInt();

  String ssid =
    server.arg("ssid");

  String password =
    server.arg("password");

  if (
    index < 0 ||
    index >= MAX_WIFI_NETWORKS
  ) {

    server.send(
      400,
      "text/plain",
      "Invalid network index"
    );

    return;
  }

  if (
    !setWiFiNetwork(
      index,
      ssid,
      password
    )
  ) {

    server.send(
      400,
      "text/plain",
      "Invalid network"
    );

    return;
  }

  if (
    !saveWiFiConfiguration()
  ) {

    server.send(
      500,
      "text/plain",
      "Save failed"
    );

    return;
  }

  server.send(
    200,
    "text/plain",
    "Saved"
  );
}

// ==================================================
// WIFI DELETE
// ==================================================

void handleWiFiDelete() {

  if (
    !server.hasArg("index")
  ) {

    server.send(
      400,
      "text/plain",
      "Missing index"
    );

    return;
  }

  int index =
    server.arg("index").toInt();

  if (
    !deleteWiFiNetwork(index)
  ) {

    server.send(
      400,
      "text/plain",
      "Delete failed"
    );

    return;
  }

  server.send(
    200,
    "text/plain",
    "Deleted"
  );
}

// ==================================================
// WIFI SCAN
// ==================================================

void handleWiFiScan() {

  int count =
    WiFi.scanNetworks();

  String json = "[";

  for (
    int i = 0;
    i < count;
    i++
  ) {

    if (i > 0) {
      json += ",";
    }

    json += "{";

    json += "\"ssid\":\"";
    json += WiFi.SSID(i);
    json += "\",";

    json += "\"rssi\":";
    json += String(
      WiFi.RSSI(i)
    );

    json += "}";
  }

  json += "]";

  WiFi.scanDelete();

  server.send(
    200,
    "application/json",
    json
  );
}

// ==================================================
// RECONNECT
// ==================================================

void handleReconnect() {

  server.send(
    200,
    "text/plain",
    "Reconnecting"
  );

  delay(100);

  connectWiFi();
}

// ==================================================
// REBOOT
// ==================================================

void handleReboot() {

  server.send(
    200,
    "text/plain",
    "Rebooting"
  );

  delay(500);

  ESP.restart();
}

// ==================================================
// START SERVER
// ==================================================

void startWebServer() {

  server.on(
    "/",
    HTTP_GET,
    handleRoot
  );

  server.on(
    "/index.html",
    HTTP_GET,
    handleRoot
  );

  server.on(
    "/style.css",
    HTTP_GET,
    handleCSS
  );

  server.on(
    "/script.js",
    HTTP_GET,
    handleJS
  );

  server.on(
    "/api/status",
    HTTP_GET,
    handleStatus
  );

  server.on(
    "/api/wifi",
    HTTP_GET,
    handleWiFiList
  );

  server.on(
    "/api/wifi/scan",
    HTTP_GET,
    handleWiFiScan
  );

  server.on(
    "/api/wifi/save",
    HTTP_POST,
    handleWiFiSave
  );

  server.on(
    "/api/wifi/delete",
    HTTP_POST,
    handleWiFiDelete
  );

  server.on(
    "/api/wifi/reconnect",
    HTTP_POST,
    handleReconnect
  );

  server.on(
    "/api/reboot",
    HTTP_POST,
    handleReboot
  );

  server.begin();

  Serial.println(
    "HTTP server started"
  );
}

// ==================================================
// LOOP
// ==================================================

void handleWebServer() {

  server.handleClient();
}

#endif
