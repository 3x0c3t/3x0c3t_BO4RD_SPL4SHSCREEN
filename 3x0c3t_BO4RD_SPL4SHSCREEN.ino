#include <TFT_eSPI.h>

#include "WiFi.h"
#include "WiFiManager.h"

#include "ScreenSplash.h"
#include "ScreenBoard.h"
#include "ScreenLoading.h"
#include "WebServer.h"

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.println("BOOT | 3x0c3t BO4RD");

  // === TFT ===
  tft.init();
  tft.setRotation(2);

  Serial.println("TFT | READY | ROT=2");

  // === SPLASH ===
  drawScreenSplash(tft);
  Serial.println("SPLASH | READY");
  delay(1500);

  // === BOARD ===
  drawScreenBoard(tft);
  Serial.println("BOARD | READY");
  delay(4000);

  // === LITTLEFS ===
  if (initWiFiStorage()) {
    Serial.println("FS | READY");
  } else {
    Serial.println("FS | ERROR");
  }

  // === WIFI CONFIGURATION ===
  loadWiFiConfiguration();

  Serial.print("WIFI | CONFIG=");
  Serial.println(wifiNetworkCount);

  // === WIFI CONNECTION ===
  drawScreenLoading(tft, "CONNECTING");

  bool connected = false;

  if (isWiFiConfigured()) {
    connected = connectWiFi();
  }

  // === WIFI RESULT ===
  if (connected) {
    drawScreenLoading(tft, "CONNECTED");
  } else {
    startSetupAccessPoint();
    drawScreenLoading(tft, "SETUP_AP");
  }

  // === WEB SERVER ===
  startWebServer();

  Serial.println("HTTP | READY | PORT=80");
}

void loop() {
  handleWebServer();
  delay(2);
}