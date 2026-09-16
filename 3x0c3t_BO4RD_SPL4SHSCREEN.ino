#include <TFT_eSPI.h>
#include "SplashScreen.h"
#include "WiFi.h"

// === TFT ===

TFT_eSPI tft = TFT_eSPI();

// === SETUP ===

void setup() {

  Serial.begin(115200);
  delay(100);

  // Initialisation TFT
  tft.init();
  tft.setRotation(2);

  // Splash screen
  drawSplashScreen(tft);

  delay(1500);

  // WiFi
  initWiFi(tft);
}

// === LOOP ===

void loop() {
}