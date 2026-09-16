#ifndef SCREEN_LOADING_H
#define SCREEN_LOADING_H

#include <TFT_eSPI.h>
#include <ESP8266WiFi.h>

#include "WiFi.h"
#include "WiFiManager.h"


void drawScreenLoading(
  TFT_eSPI &tft,
  const String &state
) {
  const int16_t width =
    tft.width();

  const int16_t height =
    tft.height();

  const int16_t centerX =
    width / 2;

  tft.fillScreen(TFT_BLACK);

  tft.setTextDatum(MC_DATUM);


  // ==========================================================
  // WIFI
  // ==========================================================

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


  // ==========================================================
  // CONNECTING
  // ==========================================================

  if (state == "CONNECTING") {

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

    tft.setTextColor(
      TFT_YELLOW,
      TFT_BLACK
    );

    tft.drawString(
      "PLEASE WAIT",
      centerX,
      130,
      2
    );

    return;
  }


  // ==========================================================
  // CONNECTED
  // ==========================================================

  if (state == "CONNECTED") {

    tft.setTextColor(
      TFT_GREEN,
      TFT_BLACK
    );

    tft.drawString(
      "CONNECTED",
      centerX,
      90,
      2
    );

    tft.setTextColor(
      TFT_WHITE,
      TFT_BLACK
    );

    tft.drawString(
      WiFi.SSID(),
      centerX,
      135,
      2
    );

    tft.setTextColor(
      TFT_CYAN,
      TFT_BLACK
    );

    tft.drawString(
      WiFi.localIP().toString(),
      centerX,
      175,
      2
    );

    tft.setTextColor(
      TFT_YELLOW,
      TFT_BLACK
    );

    tft.drawString(
      String(WiFi.RSSI()) + " dBm",
      centerX,
      215,
      2
    );

    return;
  }


  // ==========================================================
  // SETUP AP
  // ==========================================================

  if (state == "SETUP_AP") {

    String apSSID =
      String(BOARD_ID) +
      String(SETUP_AP_SUFFIX);

    tft.setTextColor(
      TFT_YELLOW,
      TFT_BLACK
    );

    tft.drawString(
      "SETUP AP",
      centerX,
      85,
      2
    );

    tft.setTextColor(
      TFT_WHITE,
      TFT_BLACK
    );

    tft.drawString(
      apSSID,
      centerX,
      125,
      2
    );

    tft.setTextColor(
      TFT_CYAN,
      TFT_BLACK
    );

    tft.drawString(
      "192.168.4.1",
      centerX,
      165,
      2
    );

    tft.setTextColor(
      TFT_GREEN,
      TFT_BLACK
    );

    tft.drawString(
      "OPEN BROWSER",
      centerX,
      210,
      2
    );

    tft.setTextColor(
      TFT_WHITE,
      TFT_BLACK
    );

    tft.drawString(
      "CONFIGURE WIFI",
      centerX,
      245,
      1
    );

    return;
  }


  // ==========================================================
  // UNKNOWN STATE
  // ==========================================================

  tft.setTextColor(
    TFT_RED,
    TFT_BLACK
  );

  tft.drawString(
    "WIFI ERROR",
    centerX,
    120,
    2
  );
}

#endif