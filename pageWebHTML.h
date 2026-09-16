#ifndef PAGE_WEB_HTML_H
#define PAGE_WEB_HTML_H

const char PAGE_WEB_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">

  <title>-3xØc3t- / BO4RD</title>

  <link rel="stylesheet" href="/style.css">
</head>

<body>

<header class="header1">

  <div class="brand">
    <span class="brand-main">-3xØc3t-</span>
    <span class="separator">/</span>
    <span class="brand-board">BO4RD</span>
  </div>

  <div class="control-title">
    CONTROL PANEL
  </div>

  <div class="header-actions">

    <button onclick="reconnectWiFi()">
      RECONNECT
    </button>

    <button
      class="danger"
      onclick="rebootBoard()">
      RESTART
    </button>

  </div>

</header>


<header class="header2">

  <div class="status-title">
    STATUS
  </div>

  <div class="status-grid">

    <div class="status-item">

      <span class="status-label">
        BOARD
      </span>

      <strong id="board">
        3x0c3t_BO4RD
      </strong>

    </div>


    <div class="status-item">

      <span class="status-label">
        SSID
      </span>

      <strong id="connectedSSID">
        3x0c3t_BO4RD_SETUP
      </strong>

    </div>


    <div class="status-item">

      <span class="status-label">
        IP
      </span>

      <strong id="ip">
        192.168.4.1
      </strong>

    </div>


    <div class="status-item">

      <span class="status-label">
        RSSI
      </span>

      <strong id="rssi">
        ---
      </strong>

    </div>

  </div>


  <div
    id="connectionStatus"
    class="connection-status">

    SETUP AP

  </div>

</header>


<main>

  <section class="panel wifi-panel">

    <div class="panel-header">

      <div class="panel-title">
        WIFI
      </div>

      <button
        class="scan-button"
        onclick="scanWiFi()">

        SCAN

      </button>

    </div>


    <div class="network-section">

      <div class="section-title">
        SAVED NETWORKS
      </div>

      <div
        id="savedNetworks"
        class="network-list">

        <div class="empty-network">
          NO NETWORK SAVED
        </div>

      </div>

    </div>


    <div class="network-section">

      <div class="section-title">
        AVAILABLE NETWORKS
      </div>

      <div
        id="availableNetworks"
        class="network-list">

        <div class="empty-network">
          PRESS SCAN
        </div>

      </div>

    </div>

  </section>

</main>


<footer>

  <span>
    3x0c3t BO4RD
  </span>

  <span>
    //
  </span>

  <span>
    ESP8266
  </span>

  <span>
    //
  </span>

  <span id="footerIP">
    192.168.4.1
  </span>

</footer>


<script src="/script.js"></script>

</body>
</html>
)rawliteral";

#endif