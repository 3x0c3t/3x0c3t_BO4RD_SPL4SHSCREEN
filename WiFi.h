#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H

#include <TFT_eSPI.h>
#include <ESP8266WiFi.h>

// === WIFI CONFIGURATION ===

const char* WIFI_SSID = "N0wifiHere";
const char* WIFI_PASSWORD = "@PassWeurd";

// === WIFI INITIALISATION ===

void initWiFi(TFT_eSPI &tft) {

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
    "WIFI",
    centerX,
    centerY - 50,
    4
  );

  // SSID
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.drawString(
    WIFI_SSID,
    centerX,
    centerY - 10,
    2
  );

  // Démarrage WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.println();
  Serial.print("Connexion WiFi : ");
  Serial.println(WIFI_SSID);

  // Tentatives
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
      centerY + 20,
      width,
      70,
      TFT_BLACK
    );

    // Animation
    String dots = "";

    for (int i = 0; i < (attempts % 4); i++) {
      dots += ".";
    }

    tft.setTextColor(TFT_YELLOW, TFT_BLACK);

    tft.drawString(
      "Connexion" + dots,
      centerX,
      centerY + 40,
      2
    );

    Serial.print(".");
  }

  Serial.println();

  // === WIFI CONNECTE ===

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("WiFi connecte !");
    Serial.print("Adresse IP : ");
    Serial.println(WiFi.localIP());

    // Nettoyage
    tft.fillRect(
      0,
      centerY + 20,
      width,
      100,
      TFT_BLACK
    );

    // Statut
    tft.setTextColor(TFT_GREEN, TFT_BLACK);

    tft.drawString(
      "CONNECTE",
      centerX,
      centerY + 30,
      2
    );

    // Adresse IP
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.drawString(
      WiFi.localIP().toString(),
      centerX,
      centerY + 60,
      2
    );

  } else {

    // === WIFI ECHEC ===

    Serial.println("Echec connexion WiFi");

    tft.fillRect(
      0,
      centerY + 20,
      width,
      100,
      TFT_BLACK
    );

    tft.setTextColor(TFT_RED, TFT_BLACK);

    tft.drawString(
      "ECHEC WIFI",
      centerX,
      centerY + 40,
      2
    );
  }

  delay(2000);
}

#endif
