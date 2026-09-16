#ifndef SCREEN_BOARD_H
#define SCREEN_BOARD_H

#include <TFT_eSPI.h>
#include <qrcode.h>

#include "WiFi.h"

// ==================================================
// SCREEN BOARD
// ==================================================

void drawScreenBoard(
  TFT_eSPI &tft
) {

  const int16_t width =
    tft.width();

  const int16_t centerX =
    width / 2;

  tft.fillScreen(
    TFT_BLACK
  );

  tft.setTextDatum(
    MC_DATUM
  );

  tft.setTextColor(
    TFT_CYAN,
    TFT_BLACK
  );

  tft.drawString(
    "BOARD",
    centerX,
    16,
    2
  );

  String qrData =
    "ID=" +
    String(BOARD_ID) +
    "\nPWD=" +
    String(BOARD_PASSWORD);

  const uint8_t QR_VERSION = 3;

  uint8_t qrcodeData[
    qrcode_getBufferSize(
      QR_VERSION
    )
  ];

  QRCode qrcode;

  qrcode_initText(
    &qrcode,
    qrcodeData,
    QR_VERSION,
    ECC_LOW,
    qrData.c_str()
  );

  const int16_t qrSize =
    qrcode.size;

  const int16_t maxQRSize =
    width - 30;

  int16_t scale =
    maxQRSize / qrSize;

  if (scale < 1) {

    scale = 1;
  }

  const int16_t displaySize =
    qrSize * scale;

  const int16_t qrX =
    (width - displaySize) / 2;

  const int16_t qrY =
    35;

  tft.fillRect(
    qrX - 4,
    qrY - 4,
    displaySize + 8,
    displaySize + 8,
    TFT_WHITE
  );

  for (
    uint8_t y = 0;
    y < qrSize;
    y++
  ) {

    for (
      uint8_t x = 0;
      x < qrSize;
      x++
    ) {

      if (
        qrcode_getModule(
          &qrcode,
          x,
          y
        )
      ) {

        tft.fillRect(
          qrX + x * scale,
          qrY + y * scale,
          scale,
          scale,
          TFT_BLACK
        );
      }
    }
  }

  const int16_t infoY =
    qrY +
    displaySize +
    18;

  tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
  );

  tft.drawString(
    "ID: " +
    String(BOARD_ID),
    centerX,
    infoY,
    2
  );

  tft.setTextColor(
    TFT_GREEN,
    TFT_BLACK
  );

  tft.drawString(
    "PWD: " +
    String(BOARD_PASSWORD),
    centerX,
    infoY + 22,
    2
  );
}

#endif