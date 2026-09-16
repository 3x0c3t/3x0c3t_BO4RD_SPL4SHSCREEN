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

  tft.fillScreen(TFT_BLACK);

  tft.setTextDatum(MC_DATUM);

  // ==================================================
  // TITLE
  // ==================================================

  tft.setTextColor(
    TFT_CYAN,
    TFT_BLACK
  );

  tft.drawString(
    "WIFI",
    centerX,
    35,
    4
  );

  // ==================================================
  // NO CONFIGURATION
  // ==================================================

  if (!isWiFiConfigured()) {

    tft.setTextColor(
      TFT_WHITE,
      TFT_BLACK
    );

    tft.drawString(
      "CONFIGURATION",
      centerX,
      80,
      2
    );

    tft.setTextColor(
      TFT_GREEN,
      TFT_BLACK
    );

    tft.drawString(
      "CONNECT TO",
      centerX,
      120,
      2
    );

    String apSSID =
      String(BOARD_ID) +
      String(SETUP_AP_SUFFIX);

    tft.drawString(
      apSSID,
      centerX,
      150,
      2
    );

    tft.setTextColor(
      TFT_WHITE,
      TFT_BLACK
    );

    tft.drawString(
      "OPEN",
      centerX,
      190,
      2
    );

    tft.setTextColor(
      TFT_CYAN,
      TFT_BLACK
    );

    tft.drawString(
      "192.168.4.1",
      centerX,
      220,
      2
    );

    tft.setTextColor(
      TFT_YELLOW,
      TFT_BLACK
    );

    tft.drawString(
      "ENTER WIFI SSID/PWD",
      centerX,
      270,
      1
    );

    return;
  }

  // ==================================================
  // CONNECTING
  // ==================================================

  tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  tft.drawString(
    "CONNECTING",
    centerX,
    90,
    2
  );

  bool connected =
    connectWiFi();

  // ==================================================
  // CONNECTED
  // ==================================================

  if (connected) {

    tft.setTextColor(
      TFT_GREEN,
      TFT_BLACK
    );

    tft.drawString(
      "CONNECTED",
      centerX,
      140,
      2
    );

    tft.setTextColor(
      TFT_WHITE,
      TFT_BLACK
    );

    tft.drawString(
      WiFi.SSID(),
      centerX,
      175,
      2
    );

    tft.setTextColor(
      TFT_CYAN,
      TFT_BLACK
    );

    tft.drawString(
      WiFi.localIP().toString(),
      centerX,
      215,
      2
    );

    return;
  }

  // ==================================================
  // FAILED
  // ==================================================

  tft.setTextColor(
    TFT_RED,
    TFT_BLACK
  );

  tft.drawString(
    "CONNECTION FAILED",
    centerX,
    145,
    2
  );

  tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  tft.drawString(
    "CHECK WIFI SETTINGS",
    centerX,
    185,
    1
  );
}

#endif
