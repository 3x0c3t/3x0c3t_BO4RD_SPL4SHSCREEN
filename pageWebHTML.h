#ifndef PAGE_WEB_HTML_H
#define PAGE_WEB_HTML_H

const char PAGE_WEB_HTML[] PROGMEM = R"rawliteral(

<!DOCTYPE html>

<html lang="fr">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1.0,maximum-scale=1.0,user-scalable=no">
<title>3x0c3t BO4RD</title>
<link rel="stylesheet" href="/style.css">
</head>

<body>

<header>
  <div class="brand">
    <span class="logo">-3xØc3t-</span>
    <span class="separator">/</span>
    <span class="board-title">BO4RD</span>
  </div>
  <div class="subtitle">CONTROL PANEL</div>
</header>

<main>

  <section class="panel status-panel">
    <div class="panel-title">STATUS</div>

<div class="status-grid">

  <div class="info-box">
    <span>BOARD</span>
    <strong id="board">---</strong>
  </div>

  <div class="info-box">
    <span>SSID</span>
    <strong id="connectedSSID">---</strong>
  </div>

  <div class="info-box">
    <span>IP</span>
    <strong id="ip">---</strong>
  </div>

  <div class="info-box">
    <span>RSSI</span>
    <strong id="rssi">---</strong>
  </div>

</div>

<div id="connectionStatus" class="connection offline">
  OFFLINE
</div>

  </section>

  <section class="panel wifi-panel">

<div class="panel-head">
  <div class="panel-title">WIFI</div>

  <button
    id="scanButton"
    class="scan-button"
    onclick="scanWiFi()">
    SCAN
  </button>
</div>

<div class="section-label">
  SAVED NETWORKS
</div>

<div id="wifiList" class="saved-list">
  <div class="empty">
    NO NETWORK
  </div>
</div>

<div class="section-label scan-label">
  AVAILABLE NETWORKS
</div>

<div id="scanList" class="scan-list">
  <div class="empty">
    PRESS SCAN
  </div>
</div>

  </section>

  <section class="panel board-panel">

<div class="panel-title">
  BOARD
</div>

<div class="board-grid">

  <div class="info-box">
    <span>BOARD ID</span>
    <strong id="boardID">---</strong>
  </div>

  <div class="info-box">
    <span>BOARD PASSWORD</span>
    <strong>********</strong>
  </div>

</div>

  </section>

  <section class="panel controls-panel">

<div class="panel-title">
  SYSTEM
</div>

<div class="controls">

  <button onclick="reconnectWiFi()">
    RECONNECT
  </button>

  <button
    class="danger"
    onclick="rebootBoard()">
    RESTART
  </button>

</div>

<div id="message" class="message"></div>

  </section>

</main>

<footer>
  <span>3x0c3t BO4RD</span>
  <span>//</span>
  <span>ESP8266</span>
  <span>//</span>
  <span id="footerIP">---</span>
</footer>

<script src="/script.js"></script>

</body>
</html>
)rawliteral";

#endif
