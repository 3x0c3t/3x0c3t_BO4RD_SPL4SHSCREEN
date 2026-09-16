#ifndef PAGE_WEB_JS_H
#define PAGE_WEB_JS_H

// ==================================================
// WEB PAGE JAVASCRIPT
// ==================================================

const char PAGE_WEB_JS[] PROGMEM = R"rawliteral(

async function api(
  url,
  options = {}
) {

  const response =
    await fetch(
      url,
      options
    );

  if (!response.ok) {

    throw new Error(
      "HTTP " +
      response.status
    );
  }

  return response;
}

// ==================================================
// STATUS
// ==================================================

async function updateStatus() {

  try {

    const response =
      await api(
        "/api/status"
      );

    const data =
      await response.json();

    document.getElementById(
      "board"
    ).textContent =
      data.board;

    document.getElementById(
      "boardID"
    ).textContent =
      data.board;

    document.getElementById(
      "connectedSSID"
    ).textContent =
      data.ssid || "---";

    document.getElementById(
      "ip"
    ).textContent =
      data.ip;

    document.getElementById(
      "footerIP"
    ).textContent =
      data.ip;

    document.getElementById(
      "rssi"
    ).textContent =
      data.rssi +
      " dBm";

    const status =
      document.getElementById(
        "connectionStatus"
      );

    if (data.connected) {

      status.textContent =
        "CONNECTED";

      status.className =
        "status online";

    } else {

      status.textContent =
        "OFFLINE";

      status.className =
        "status offline";
    }

  } catch (error) {

    console.error(
      error
    );
  }
}

// ==================================================
// WIFI LIST
// ==================================================

async function loadWiFi() {

  try {

    const response =
      await api(
        "/api/wifi"
      );

    const networks =
      await response.json();

    const container =
      document.getElementById(
        "wifiList"
      );

    container.innerHTML =
      "";

    networks.forEach(
      network => {

        const item =
          document.createElement(
            "div"
          );

        item.className =
          "wifi-item";

        if (
          network.priority
        ) {

          item.classList.add(
            "priority"
          );
        }

        const name =
          document.createElement(
            "div"
          );

        name.className =
          "wifi-name";

        name.textContent =
          network.ssid;

        const priority =
          document.createElement(
            "div"
          );

        priority.className =
          "priority-label";

        priority.textContent =
          network.priority
            ? "PRIORITY"
            : "BACKUP";

        const actions =
          document.createElement(
            "div"
          );

        if (
          !network.priority
        ) {

          const remove =
            document.createElement(
              "button"
            );

          remove.textContent =
            "DELETE";

          remove.onclick =
            () =>
              deleteNetwork(
                network.index
              );

          actions.appendChild(
            remove
          );
        }

        item.appendChild(
          name
        );

        item.appendChild(
          priority
        );

        item.appendChild(
          actions
        );

        container.appendChild(
          item
        );
      });

  } catch (error) {

    console.error(
      error
    );
  }
}

// ==================================================
// ADD NETWORK
// ==================================================

async function addNetwork() {

  const ssid =
    document.getElementById(
      "newSSID"
    ).value.trim();

  const password =
    document.getElementById(
      "newPassword"
    ).value;

  if (!ssid) {

    alert(
      "SSID required"
    );

    return;
  }

  try {

    const response =
      await api(
        "/api/wifi"
      );

    const networks =
      await response.json();

    if (
      networks.length >= 5
    ) {

      alert(
        "Maximum 5 networks"
      );

      return;
    }

    const index =
      networks.length;

    const body =
      new URLSearchParams();

    body.append(
      "index",
      index
    );

    body.append(
      "ssid",
      ssid
    );

    body.append(
      "password",
      password
    );

    await api(
      "/api/wifi/save",
      {
        method: "POST",
        body: body
      }
    );

    document.getElementById(
      "newSSID"
    ).value = "";

    document.getElementById(
      "newPassword"
    ).value = "";

    await loadWiFi();

  } catch (error) {

    console.error(
      error
    );

    alert(
      "Save failed"
    );
  }
}

// ==================================================
// DELETE NETWORK
// ==================================================

async function deleteNetwork(
  index
) {

  if (
    !confirm(
      "Delete this network?"
    )
  ) {

    return;
  }

  const body =
    new URLSearchParams();

  body.append(
    "index",
    index
  );

  try {

    await api(
      "/api/wifi/delete",
      {
        method: "POST",
        body: body
      }
    );

    await loadWiFi();

  } catch (error) {

    console.error(
      error
    );
  }
}

// ==================================================
// SCAN WIFI
// ==================================================

async function scanWiFi() {

  try {

    const response =
      await api(
        "/api/wifi/scan"
      );

    const networks =
      await response.json();

    let message =
      "AVAILABLE NETWORKS\n\n";

    networks.forEach(
      network => {

        message +=
          network.ssid +
          " (" +
          network.rssi +
          " dBm)\n";
      }
    );

    alert(
      message
    );

  } catch (error) {

    console.error(
      error
    );

    alert(
      "WiFi scan failed"
    );
  }
}

// ==================================================
// RECONNECT
// ==================================================

async function reconnectWiFi() {

  try {

    await api(
      "/api/wifi/reconnect",
      {
        method: "POST"
      }
    );

    setTimeout(
      updateStatus,
      2000
    );

  } catch (error) {

    console.error(
      error
    );
  }
}

// ==================================================
// REBOOT
// ==================================================

async function rebootBoard() {

  if (
    !confirm(
      "Restart BO4RD?"
    )
  ) {

    return;
  }

  try {

    await api(
      "/api/reboot",
      {
        method: "POST"
      }
    );

    document.body.innerHTML =
      "<main style=\"padding:40px;text-align:center\">" +
      "<h1>BO4RD RESTARTING...</h1>" +
      "</main>";

  } catch (error) {

    console.error(
      error
    );
  }
}

// ==================================================
// INIT
// ==================================================

async function init() {

  await updateStatus();

  await loadWiFi();

}

init();

setInterval(
  updateStatus,
  5000
);

)rawliteral";

#endif