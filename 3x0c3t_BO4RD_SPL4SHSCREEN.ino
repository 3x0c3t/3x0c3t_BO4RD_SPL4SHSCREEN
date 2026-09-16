#include <TFT_eSPI.h>

#include "ScreenSplash.h"
#include "ScreenBoard.h"
#include "ScreenLoading.h"

// === TFT ===

TFT_eSPI tft = TFT_eSPI();

// === SETUP ===

void setup() {

  Serial.begin(115200);
  delay(100);

  // Initialisation TFT
  tft.init();
  tft.setRotation(2);

  // === SCREEN SPLASH ===

  drawScreenSplash(tft);

  delay(1500);

  // === SCREEN BOARD ===

  drawScreenBoard(tft);

  delay(5000);

  // === SCREEN LOADING ===

  drawScreenLoading(tft);
}

// === LOOP ===

void loop() {
}