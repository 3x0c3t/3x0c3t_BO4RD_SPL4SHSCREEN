#ifndef PAGE_WEB_HTML_H
#define PAGE_WEB_HTML_H

// ==================================================
// WEB PAGE HTML
// ==================================================

const char PAGE_WEB_HTML[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html lang="fr">

<head>

<meta charset="UTF-8">

<meta
  name="viewport"
  content="width=device-width, initial-scale=1.0"
>

<title>3x0c3t BO4RD</title>

<link
  rel="stylesheet"
  href="/style.css"
>

</head>

<body>

<header>

<div class="logo">
-3xØc3t-
</div>

<div class="title">
BO4RD
</div>

<div class="subtitle">
CONTROL PANEL
</div>

</header>

<main>

<section class="panel">

<h2>STATUS</h2>

<div class="status-grid">

<div>
<span>BOARD</span>
<strong id="board">---</strong>
</div>

<div>
<span>SSID</span>
<strong id="connectedSSID">---</strong>
</div>

<div>
<span>IP</span>
<strong id="ip">---</strong>
</div>

<div>
<span>RSSI</span>
<strong id="rssi">---</strong>
</div>

</div>

<div
id="connectionStatus"
class="status offline"
>
OFFLINE
</div>

</section>

<section class="panel">

<div class="panel-header">

<h2>WIFI NETWORKS</h2>

<button onclick="scanWiFi()">
SCAN
</button>

</div>

<div
id="wifiList"
class="wifi-list"
>
</div>

<div class="network-add">

<h3>ADD NETWORK</h3>

<label>
SSID
</label>

<input
id="newSSID"
type="text"
autocomplete="off"
>

<label>
PASSWORD
</label>

<input
id="newPassword"
type="password"
autocomplete="off"
>

<button onclick="addNetwork()">
ADD NETWORK
</button>

</div>

</section>

<section class="panel">

<h2>BOARD</h2>

<div class="board-info">

<div>
<span>BOARD ID</span>
<strong id="boardID">---</strong>
</div>

<div>
<span>BOARD PASSWORD</span>
<strong>********</strong>
</div>

</div>

</section>

<section class="panel controls">

<button onclick="reconnectWiFi()">
RECONNECT WIFI
</button>

<button
class="danger"
onclick="rebootBoard()"
>
RESTART BOARD
</button>

</section>

</main>

<footer>

3x0c3t BO4RD //
ESP8266 //

<span id="footerIP">
---
</span>

</footer>

<script src="/script.js"></script>

</body>

</html>

)rawliteral";

#endif