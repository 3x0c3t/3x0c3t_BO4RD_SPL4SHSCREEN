#ifndef SCREEN_LOADING_H
#define SCREEN_LOADING_H

#include <TFT_eSPI.h>
#include <ESP8266WiFi.h>

// === WIFI CONFIGURATION ===

const char* WIFI_SSID = "TON_SSID";
const char* WIFI_PASSWORD = "TON_MOT_DE_PASSE";

// === SCREEN LOADING ===

void drawScreenLoading(TFT_eSPI &tft) {

  const int16_t width = tft.width();
  const int16_t height = tft.height();

  const int16_t centerX = width / 2;
  const int16_t centerY = height / 2;

  // Nettoyage écran
  tft.fillScreen(TFT_BLACK);

  // Configuration texte
  tft.setTextDatum(MC_DATUM);

  // Titre
  tft.setTextColor(TFT_CYAN, TFT_BLACK);

  tft.drawString(
    "LOADING",
    centerX,
    centerY - 55,
    4
  );

  // Sous-titre
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.drawString(
    "WIFI",
    centerX,
    centerY - 15,
    2
  );

  // Démarrage WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(
    WIFI_SSID,
    WIFI_PASSWORD
  );

  Serial.println();
  Serial.print("Connexion WiFi : ");
  Serial.println(WIFI_SSID);

  // Nombre de tentatives
  int attempts = 0;

  const int maxAttempts = 30;

  while (
    WiFi.status() != WL_CONNECTED &&
    attempts < maxAttempts
  ) {

    delay(500);

    attempts++;

    // Zone statut
    tft.fillRect(
      0,
      centerY + 10,
      width,
      90,
      TFT_BLACK
    );

    // Animation points
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

    // Barre de progression
    int16_t barWidth =
      map(
        attempts,
        0,
        maxAttempts,
        0,
        width - 44
      );

    tft.drawRect(
      20,
      centerY + 60,
      width - 40,
      10,
      TFT_WHITE
    );

    if (barWidth > 0) {

      tft.fillRect(
        22,
        centerY + 62,
        barWidth,
        6,
        TFT_YELLOW
      );
    }

    Serial.print(".");
  }

  Serial.println();

  // === CONNEXION REUSSIE ===

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("WiFi connecte !");
    Serial.print("Adresse IP : ");
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

    // Adresse IP
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

  // === ECHEC CONNEXION ===

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
