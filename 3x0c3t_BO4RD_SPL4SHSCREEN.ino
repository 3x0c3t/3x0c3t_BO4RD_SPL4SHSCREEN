#include <TFT_eSPI.h>
#include <ESP8266WiFi.h>
#include <LittleFS.h>

#include "WiFi.h"
#include "WiFiManager.h"

#include "ScreenSplash.h"
#include "ScreenBoard.h"
#include "ScreenLoading.h"

#include "WebServer.h"

// ==================================================
// TFT
// ==================================================

TFT_eSPI tft = TFT_eSPI();

// ==================================================
// SETUP
// ==================================================

void setup() {

  Serial.begin(115200);

  delay(100);

  Serial.println();
  Serial.println("================================");
  Serial.println("3x0c3t BO4RD");
  Serial.println("================================");

  // ==================================================
  // TFT
  // ==================================================

  tft.init();

  tft.setRotation(2);

  // ==================================================
  // LITTLEFS
  // ==================================================

  if (LittleFS.begin()) {

    Serial.println("LittleFS : OK");

  } else {

    Serial.println("LittleFS : ERROR");
  }

  // ==================================================
  // SCREEN SPLASH
  // ==================================================

  drawScreenSplash(tft);

  delay(1500);

  // ==================================================
  // SCREEN BOARD
  // ==================================================

  drawScreenBoard(tft);

  delay(5000);

  // ==================================================
  // SCREEN LOADING
  // ==================================================

  drawScreenLoading(tft);

  // ==================================================
  // WEB SERVER
  // ==================================================

  startWebServer();

  // ==================================================
  // SERIAL
  // ==================================================

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("================================");

    Serial.print("SSID : ");
    Serial.println(WiFi.SSID());

    Serial.print("IP   : ");
    Serial.println(WiFi.localIP());

    Serial.print("WEB  : http://");
    Serial.print(WiFi.localIP());
    Serial.println("/");

    Serial.println("================================");

  } else {

    Serial.println("================================");
    Serial.println("WIFI NOT CONNECTED");
    Serial.println("WEB SERVER NOT ACCESSIBLE");
    Serial.println("================================");
  }
}

// ==================================================
// LOOP
// ==================================================

void loop() {

  handleWebServer();

  delay(2);
}