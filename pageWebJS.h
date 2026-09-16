#ifndef PAGE_WEB_JS_H
#define PAGE_WEB_JS_H

const char PAGE_WEB_JS[] PROGMEM = R"rawliteral(

let savedNetworksCache = [];


/* =========================================================
   STATUS
   ========================================================= */

async function updateStatus() {

  try {

    const response =
      await fetch("/api/status");

    const data =
      await response.json();


    document.getElementById(
      "board"
    ).textContent =
      data.board || "---";


    document.getElementById(
      "connectedSSID"
    ).textContent =
      data.ssid || "---";


    document.getElementById(
      "ip"
    ).textContent =
      data.ip || "---";


    document.getElementById(
      "footerIP"
    ).textContent =
      data.ip || "---";


    document.getElementById(
      "rssi"
    ).textContent =
      data.connected
        ? data.rssi + " dBm"
        : "---";


    const status =
      document.getElementById(
        "connectionStatus"
      );


    if (data.connected) {

      status.textContent =
        "CONNECTED";

      status.classList.add(
        "online"
      );

    }

    else if (data.setupAP) {

      status.textContent =
        "SETUP AP";

      status.classList.remove(
        "online"
      );

    }

    else {

      status.textContent =
        "OFFLINE";

      status.classList.remove(
        "online"
      );

    }

  }

  catch (error) {

    console.error(error);

  }

}


/* =========================================================
   SAVED NETWORKS
   ========================================================= */

async function loadSavedNetworks() {

  try {

    const response =
      await fetch("/api/wifi");

    const networks =
      await response.json();


    savedNetworksCache =
      networks;


    const container =
      document.getElementById(
        "savedNetworks"
      );


    container.innerHTML = "";


    if (!networks.length) {

      container.innerHTML =
        '<div class="empty-network">' +
        'NO NETWORK SAVED' +
        '</div>';

      return;

    }


    networks.forEach(
      function(network) {

        const row =
          document.createElement(
            "div"
          );


        row.className =
          "network-item";


        const priority =
          network.priority
            ? "PRIMARY"
            : "";


        row.innerHTML =

          '<div class="network-name">' +

          escapeHTML(
            network.ssid
          ) +

          '<br>' +

          '<span class="network-priority">' +

          priority +

          '</span>' +

          '</div>' +

          '<div class="network-rssi">' +

          '</div>' +

          '<input ' +

          'class="network-password" ' +

          'type="password" ' +

          'placeholder="PWD" ' +

          'data-index="' +

          network.index +

          '">' +

          '<button ' +

          'class="network-delete" ' +

          'onclick="deleteNetwork(' +

          network.index +

          ')">' +

          'DELETE' +

          '</button>';


        container.appendChild(
          row
        );

      }
    );

  }

  catch (error) {

    console.error(error);

  }

}


/* =========================================================
   WIFI SCAN
   ========================================================= */

async function scanWiFi() {

  const container =
    document.getElementById(
      "availableNetworks"
    );


  container.innerHTML =
    '<div class="empty-network">' +
    'SCANNING...' +
    '</div>';


  try {

    const response =
      await fetch(
        "/api/wifi/scan"
      );


    const networks =
      await response.json();


    container.innerHTML = "";


    if (!networks.length) {

      container.innerHTML =
        '<div class="empty-network">' +
        'NO NETWORK FOUND' +
        '</div>';

      return;

    }


    networks.forEach(
      function(network, index) {

        const row =
          document.createElement(
            "div"
          );


        row.className =
          "network-item";


        row.innerHTML =

          '<div class="network-name">' +

          escapeHTML(
            network.ssid
          ) +

          '</div>' +

          '<div class="network-rssi">' +

          network.rssi +

          ' dBm' +

          '</div>' +

          '<input ' +

          'class="network-password" ' +

          'type="password" ' +

          'id="password-' +

          index +

          '" ' +

          'placeholder="PWD">' +

          '<button ' +

          'class="network-save" ' +

          'onclick="saveScannedNetwork(' +

          index +

          ')">' +

          'SAVE' +

          '</button>';


        row.dataset.ssid =
          network.ssid;


        container.appendChild(
          row
        );

      }
    );

  }

  catch (error) {

    container.innerHTML =
      '<div class="empty-network">' +
      'SCAN ERROR' +
      '</div>';


    console.error(error);

  }

}


/* =========================================================
   SAVE SCANNED NETWORK
   ========================================================= */

async function saveScannedNetwork(
  index
) {

  const container =
    document.getElementById(
      "availableNetworks"
    );


  const rows =
    container.querySelectorAll(
      ".network-item"
    );


  if (
    index < 0 ||
    index >= rows.length
  ) {

    return;

  }


  const row =
    rows[index];


  const ssid =
    row.dataset.ssid;


  const passwordInput =
    document.getElementById(
      "password-" + index
    );


  const password =
    passwordInput
      ? passwordInput.value
      : "";


  if (!ssid) {

    alert(
      "SSID ERROR"
    );

    return;

  }


  if (
    savedNetworksCache.length >= 5
  ) {

    alert(
      "MAXIMUM 5 NETWORKS"
    );

    return;

  }


  const networkIndex =
    savedNetworksCache.length;


  const body =
    new URLSearchParams();


  body.append(
    "index",
    networkIndex
  );


  body.append(
    "ssid",
    ssid
  );


  body.append(
    "password",
    password
  );


  try {

    const response =
      await fetch(
        "/api/wifi/save",
        {
          method: "POST",

          headers: {
            "Content-Type":
              "application/x-www-form-urlencoded"
          },

          body:
            body.toString()
        }
      );


    if (!response.ok) {

      throw new Error(
        await response.text()
      );

    }


    await loadSavedNetworks();

    await updateStatus();

  }

  catch (error) {

    alert(
      "SAVE ERROR"
    );

    console.error(error);

  }

}


/* =========================================================
   DELETE NETWORK
   ========================================================= */

async function deleteNetwork(
  index
) {

  const body =
    new URLSearchParams();


  body.append(
    "index",
    index
  );


  try {

    const response =
      await fetch(
        "/api/wifi/delete",
        {
          method: "POST",

          headers: {
            "Content-Type":
              "application/x-www-form-urlencoded"
          },

          body:
            body.toString()
        }
      );


    if (!response.ok) {

      throw new Error(
        await response.text()
      );

    }


    await loadSavedNetworks();

    await updateStatus();

  }

  catch (error) {

    alert(
      "DELETE ERROR"
    );

    console.error(error);

  }

}


/* =========================================================
   RECONNECT
   ========================================================= */

async function reconnectWiFi() {

  try {

    await fetch(
      "/api/wifi/reconnect",
      {
        method: "POST"
      }
    );


    setTimeout(
      updateStatus,
      1000
    );


    setTimeout(
      updateStatus,
      3000
    );

  }

  catch (error) {

    console.error(error);

  }

}


/* =========================================================
   RESTART
   ========================================================= */

async function rebootBoard() {

  try {

    await fetch(
      "/api/reboot",
      {
        method: "POST"
      }
    );

  }

  catch (error) {

    console.error(error);

  }

}


/* =========================================================
   HTML ESCAPE
   ========================================================= */

function escapeHTML(
  value
) {

  return String(value)

    .replaceAll(
      "&",
      "&amp;"
    )

    .replaceAll(
      "<",
      "&lt;"
    )

    .replaceAll(
      ">",
      "&gt;"
    )

    .replaceAll(
      '"',
      "&quot;"
    )

    .replaceAll(
      "'",
      "&#039;"
    );

}


/* =========================================================
   INIT
   ========================================================= */

async function initPage() {

  await updateStatus();

  await loadSavedNetworks();

}


initPage();


setInterval(
  updateStatus,
  5000
);

)rawliteral";

#endif