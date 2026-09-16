#ifndef SCREEN_LOADING_H
#define SCREEN_LOADING_H

#include <TFT_eSPI.h>
#include <ESP8266WiFi.h>

#include "WiFi.h"
#include "WiFiManager.h"

// ==================================================
// SCREEN LOADING
// ==================================================

void drawScreenLoading(
  TFT_eSPI &tft
) {

  const int16_t width =
    tft.width();

  const int16_t height =
    tft.height();

  const int16_t centerX =
    width / 2;

  const int16_t centerY =
    height / 2;

  tft.fillScreen(
    TFT_BLACK
  );

  tft.setTextDatum(
    MC_DATUM
  );

  // ==================================================
  // TITLE
  // ==================================================

  tft.setTextColor(
    TFT_CYAN,
    TFT_BLACK
  );

  tft.drawString(
    "LOADING",
    centerX,
    centerY - 70,
    4
  );

  // ==================================================
  // WIFI
  // ==================================================

  tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  tft.drawString(
    "WIFI",
    centerX,
    centerY - 30,
    2
  );

  // ==================================================
  // LOAD CONFIGURATION
  // ==================================================

  loadWiFiConfiguration();

  // ==================================================
  // CONNECT
  // ==================================================

  bool connected =
    connectWiFi();

  // ==================================================
  // STATUS
  // ==================================================

  tft.fillRect(
    0,
    centerY,
    width,
    100,
    TFT_BLACK
  );

  if (connected) {

    tft.setTextColor(
      TFT_GREEN,
      TFT_BLACK
    );

    tft.drawString(
      "CONNECTE",
      centerX,
      centerY + 15,
      2
    );

    tft.setTextColor(
      TFT_WHITE,
      TFT_BLACK
    );

    tft.drawString(
      WiFi.localIP().toString(),
      centerX,
      centerY + 45,
      2
    );

  } else {

    tft.setTextColor(
      TFT_RED,
      TFT_BLACK
    );

    tft.drawString(
      "ECHEC WIFI",
      centerX,
      centerY + 15,
      2
    );

    tft.setTextColor(
      TFT_WHITE,
      TFT_BLACK
    );

    tft.drawString(
      "NO NETWORK",
      centerX,
      centerY + 45,
      2
    );
  }

  delay(2000);
}

#endif