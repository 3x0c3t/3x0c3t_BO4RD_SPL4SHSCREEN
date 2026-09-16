#ifndef SCREEN_SPLASH_H
#define SCREEN_SPLASH_H

#include <TFT_eSPI.h>

// === SCREEN SPLASH ===

void drawScreenSplash(TFT_eSPI &tft) {

  const int16_t width = tft.width();
  const int16_t height = tft.height();

  const int16_t centerX = width / 2;
  const int16_t centerY = height / 2;

  // Fond
  tft.fillScreen(TFT_BLACK);

  // Texte centré
  tft.setTextDatum(MC_DATUM);

  // Logo
  tft.setTextColor(TFT_CYAN, TFT_BLACK);

  tft.drawString(
    "-3xØc3t-",
    centerX,
    centerY - 45,
    4
  );

  // Nom carte
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.drawString(
    "BO4RD",
    centerX,
    centerY,
    2
  );

  // Nom écran
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  tft.drawString(
    "SPL4SHSCREEN",
    centerX,
    centerY + 30,
    2
  );

  // Barre de progression
  tft.drawRect(
    20,
    height - 35,
    width - 40,
    10,
    TFT_CYAN
  );

  // Animation
  for (
    int16_t x = 22;
    x < width - 42;
    x += 4
  ) {

    tft.fillRect(
      x,
      height - 33,
      3,
      6,
      TFT_CYAN
    );

    delay(8);
  }
}

#endif
