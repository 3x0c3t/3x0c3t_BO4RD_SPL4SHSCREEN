#ifndef PAGE_WEB_JS_H
#define PAGE_WEB_JS_H

const char PAGE_WEB_JS[] PROGMEM = R"rawliteral(

let selectedSSID = "";
let savedNetworksCache = [];

async function updateStatus() {
  try {
    const response = await fetch("/api/status");
    const data = await response.json();

    document.getElementById("board").textContent =
      data.board || "---";

    document.getElementById("connectedSSID").textContent =
      data.ssid || "---";

    document.getElementById("ip").textContent =
      data.ip || "---";

    document.getElementById("footerIP").textContent =
      data.ip || "---";

    document.getElementById("rssi").textContent =
      data.connected
        ? data.rssi + " dBm"
        : "---";

    const status =
      document.getElementById("connectionStatus");

    if (data.connected) {

      status.textContent = "CONNECTED";

      status.classList.add("online");

    } else if (data.setupAP) {

      status.textContent = "SETUP AP";

      status.classList.remove("online");

    } else {

      status.textContent = "OFFLINE";

      status.classList.remove("online");

    }

  } catch (error) {

    console.error(error);

  }
}

async function loadSavedNetworks() {

  try {

    const response =
      await fetch("/api/wifi");

    const networks =
      await response.json();

    savedNetworksCache = networks;

    const container =
      document.getElementById("savedNetworks");

    container.innerHTML = "";

    if (!networks.length) {

      container.innerHTML =
        '<div class="empty-network">NO NETWORK SAVED</div>';

      return;
    }

    networks.forEach((network) => {

      const row =
        document.createElement("div");

      row.className =
        "network-item";

      const priority =
        network.priority
          ? '<span class="network-priority">PRIMARY</span>'
          : "";

      row.innerHTML =
        '<div class="network-name">' +
        escapeHTML(network.ssid) +
        "</div>" +

        '<div class="network-rssi">' +
        priority +
        "</div>" +

        '<button class="network-delete" onclick="deleteNetwork(' +
        network.index +
        ')">DELETE</button>';

      container.appendChild(row);

    });

  } catch (error) {

    console.error(error);

  }
}

async function scanWiFi() {

  const container =
    document.getElementById("availableNetworks");

  container.innerHTML =
    '<div class="empty-network">SCANNING...</div>';

  try {

    const response =
      await fetch("/api/wifi/scan");

    const networks =
      await response.json();

    container.innerHTML = "";

    if (!networks.length) {

      container.innerHTML =
        '<div class="empty-network">NO NETWORK FOUND</div>';

      return;
    }

    networks.forEach((network) => {

      const row =
        document.createElement("div");

      row.className =
        "network-item";

      row.innerHTML =
        '<div class="network-name">' +
        escapeHTML(network.ssid) +
        "</div>" +

        '<div class="network-rssi">' +
        network.rssi +
        " dBm</div>" +

        '<button class="network-save" onclick="openPasswordPanel(' +
        JSON.stringify(network.ssid) +
        ')">SAVE</button>';

      container.appendChild(row);

    });

  } catch (error) {

    container.innerHTML =
      '<div class="empty-network">SCAN ERROR</div>';

    console.error(error);

  }
}

function openPasswordPanel(ssid) {

  selectedSSID = ssid;

  document.getElementById("selectedSSID").textContent =
    ssid;

  document.getElementById("networkPassword").value =
    "";

  document.getElementById("passwordPanel")
    .classList.remove("hidden");

  document.getElementById("networkPassword")
    .focus();
}

function closePasswordPanel() {

  document.getElementById("passwordPanel")
    .classList.add("hidden");

  selectedSSID = "";

}

async function saveSelectedNetwork() {

  if (!selectedSSID) {
    return;
  }

  const password =
    document.getElementById("networkPassword").value;

  if (savedNetworksCache.length >= 5) {

    alert("MAXIMUM 5 NETWORKS");

    return;
  }

  const index =
    savedNetworksCache.length;

  const body =
    new URLSearchParams();

  body.append(
    "index",
    index
  );

  body.append(
    "ssid",
    selectedSSID
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

    closePasswordPanel();

    await loadSavedNetworks();

    await updateStatus();

  } catch (error) {

    alert("SAVE ERROR");

    console.error(error);

  }
}

async function deleteNetwork(index) {

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

  } catch (error) {

    alert("DELETE ERROR");

    console.error(error);

  }
}

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

  } catch (error) {

    console.error(error);

  }
}

async function rebootBoard() {

  try {

    await fetch(
      "/api/reboot",
      {
        method: "POST"
      }
    );

  } catch (error) {

    console.error(error);

  }
}

function escapeHTML(value) {

  return String(value)
    .replaceAll("&", "&amp;")
    .replaceAll("<", "&lt;")
    .replaceAll(">", "&gt;")
    .replaceAll('"', "&quot;")
    .replaceAll("'", "&#039;");

}

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