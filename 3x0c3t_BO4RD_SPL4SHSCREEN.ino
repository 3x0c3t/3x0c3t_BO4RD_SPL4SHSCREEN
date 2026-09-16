#include <TFT_eSPI.h>

#include "WiFi.h"
#include "WiFiManager.h"

#include "ScreenSplash.h"
#include "ScreenBoard.h"
#include "ScreenLoading.h"
#include "WebServer.h"

// ==================================================
// TFT
// ==================================================

TFT_eSPI tft =
TFT_eSPI();

// ==================================================
// SETUP
// ==================================================

void setup() {

Serial.begin(
115200
);

delay(100);

Serial.println();
Serial.println(
"================================"
);
Serial.println(
"3x0c3t BO4RD"
);
Serial.println(
"SPL4SHSCREEN"
);
Serial.println(
"================================"
);

// ==================================================
// TFT
// ==================================================

tft.init();

// ROTATION 2
tft.setRotation(2);

// ==================================================
// SPLASH
// ==================================================

drawScreenSplash(
tft
);

delay(1500);

// ==================================================
// BOARD
// ==================================================

drawScreenBoard(
tft
);

delay(4000);

// ==================================================
// LITTLEFS
// ==================================================

initWiFiStorage();

// ==================================================
// LOAD WIFI CONFIGURATION
// ==================================================

loadWiFiConfiguration();

// ==================================================
// WIFI LOADING SCREEN
// ==================================================

drawScreenLoading(
tft
);

// ==================================================
// START CONFIGURATION AP
// ==================================================

if (
!isWiFiConfigured()
) {

startSetupAccessPoint();

// Update loading screen
drawScreenLoading(
  tft
);

}

// ==================================================
// START WEB SERVER
// ==================================================

startWebServer();

Serial.println();

if (
setupAPActive
) {

Serial.println(
  "================================"
);

Serial.println(
  "CONFIGURATION MODE ACTIVE"
);

Serial.print(
  "SSID: "
);

Serial.print(
  BOARD_ID
);

Serial.println(
  SETUP_AP_SUFFIX
);

Serial.println(
  "IP: 192.168.4.1"
);

Serial.println(
  "================================"
);

} else {

Serial.println(
  "================================"
);

Serial.println(
  "WIFI MODE ACTIVE"
);

Serial.print(
  "SSID: "
);

Serial.println(
  WiFi.SSID()
);

Serial.print(
  "IP: "
);

Serial.println(
  WiFi.localIP()
);

Serial.println(
  "================================"
);

}
}

// ==================================================
// LOOP
// ==================================================

void loop() {

handleWebServer();

delay(2);
}
