#ifndef SCREEN_LOADING_H
#define SCREEN_LOADING_H

#include <TFT_eSPI.h>
#include <ESP8266WiFi.h>

#include "WiFi.h"

// === SCREEN LOADING ===

void drawScreenLoading(TFT_eSPI &tft) {

  const int16_t width = tft.width();
  const int16_t height = tft.height();

  const int16_t centerX = width / 2;
  const int16_t centerY = height / 2;

  // === BACKGROUND ===

  tft.fillScreen(TFT_BLACK);

  // === TEXT CONFIGURATION ===

  tft.setTextDatum(MC_DATUM);

  // === TITLE ===

  tft.setTextColor(
    TFT_CYAN,
    TFT_BLACK
  );

  tft.drawString(
    "LOADING",
    centerX,
    centerY - 55,
    4
  );

  // === WIFI ===

  tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  tft.drawString(
    "WIFI",
    centerX,
    centerY - 15,
    2
  );

  // === WIFI START ===

  WiFi.mode(WIFI_STA);

  WiFi.begin(
    WIFI_SSID,
    WIFI_PASSWORD
  );

  Serial.println();
  Serial.print("Connexion WiFi : ");
  Serial.println(WIFI_SSID);

  // === CONNECTION ATTEMPTS ===

  int attempts = 0;

  const int maxAttempts = 30;

  while (
    WiFi.status() != WL_CONNECTED &&
    attempts < maxAttempts
  ) {

    delay(500);

    attempts++;

    // Nettoyage zone statut
    tft.fillRect(
      0,
      centerY + 10,
      width,
      90,
      TFT_BLACK
    );

    // === ANIMATION DOTS ===

    String dots = "";

    for (
      int i = 0;
      i < (attempts % 4);
      i++
    ) {
      dots += ".";
    }

    tft.setTextColor(
      TFT_YELLOW,
      TFT_BLACK
    );

    tft.drawString(
      "Connexion" + dots,
      centerX,
      centerY + 35,
      2
    );

    // === PROGRESS BAR ===

    const int16_t barX = 20;
    const int16_t barY = centerY + 60;
    const int16_t barWidth = width - 40;
    const int16_t barHeight = 10;

    tft.drawRect(
      barX,
      barY,
      barWidth,
      barHeight,
      TFT_WHITE
    );

    int16_t progressWidth = map(
      attempts,
      0,
      maxAttempts,
      0,
      barWidth - 4
    );

    if (progressWidth > 0) {

      tft.fillRect(
        barX + 2,
        barY + 2,
        progressWidth,
        6,
        TFT_YELLOW
      );
    }

    // === SERIAL DEBUG ===

    Serial.print(".");
  }

  Serial.println();

  // === WIFI CONNECTED ===

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println(
      "WiFi connecte !"
    );

    Serial.print(
      "Adresse IP : "
    );

    Serial.println(
      WiFi.localIP()
    );

    // Nettoyage
    tft.fillRect(
      0,
      centerY + 10,
      width,
      110,
      TFT_BLACK
    );

    // Statut
    tft.setTextColor(
      TFT_GREEN,
      TFT_BLACK
    );

    tft.drawString(
      "CONNECTE",
      centerX,
      centerY + 25,
      2
    );

    // IP
    tft.setTextColor(
      TFT_WHITE,
      TFT_BLACK
    );

    tft.drawString(
      WiFi.localIP().toString(),
      centerX,
      centerY + 55,
      2
    );
  }

  // === WIFI ERROR ===

  else {

    Serial.println(
      "Echec connexion WiFi"
    );

    // Nettoyage
    tft.fillRect(
      0,
      centerY + 10,
      width,
      110,
      TFT_BLACK
    );

    // Erreur
    tft.setTextColor(
      TFT_RED,
      TFT_BLACK
    );

    tft.drawString(
      "ECHEC WIFI",
      centerX,
      centerY + 35,
      2
    );
  }

  delay(2000);
}

#endif