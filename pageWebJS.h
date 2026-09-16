#ifndef PAGE_WEB_JS_H
#define PAGE_WEB_JS_H

const char PAGE_WEB_JS[] PROGMEM = R"rawliteral(

async function api(url, options = {}) {

const response = await fetch(
url,
options
);

if (!response.ok) {
throw new Error(
"HTTP " + response.status
);
}

return response;
}

function showMessage(text, error = false) {

const element =
document.getElementById("message");

if (!element) {
return;
}

element.textContent = text;

element.style.color =
error
? "#ff304f"
: "#00ff99";

setTimeout(() => {
element.textContent = "";
}, 3000);
}

async function updateStatus() {

try {

const response =
  await api("/api/status");

const data =
  await response.json();

document.getElementById(
  "board"
).textContent =
  data.board || "---";

document.getElementById(
  "boardID"
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

  status.className =
    "connection online";

} else if (data.setupAP) {

  status.textContent =
    "SETUP AP";

  status.className =
    "connection setup";

} else {

  status.textContent =
    "OFFLINE";

  status.className =
    "connection offline";
}

} catch (error) {

console.error(error);

}
}

async function loadWiFi() {

try {

const response =
  await api("/api/wifi");

const networks =
  await response.json();

const container =
  document.getElementById(
    "wifiList"
  );

container.innerHTML = "";

if (networks.length === 0) {

  container.innerHTML =
    '<div class="empty">NO NETWORK SAVED</div>';

  return;
}

networks.forEach(network => {

  const item =
    document.createElement("div");

  item.className =
    "wifi-row";

  if (network.priority) {
    item.classList.add("priority");
  }

  const name =
    document.createElement("div");

  name.className =
    "wifi-name";

  name.textContent =
    network.ssid;

  const meta =
    document.createElement("div");

  meta.className =
    "wifi-meta";

  meta.textContent =
    network.priority
      ? "PRIORITY"
      : "BACKUP";

  if (network.priority) {
    meta.classList.add("priority");
  }

  item.appendChild(name);
  item.appendChild(meta);

  if (!network.priority) {

    const remove =
      document.createElement("button");

    remove.className =
      "small-button";

    remove.textContent =
      "DEL";

    remove.onclick =
      () => deleteNetwork(
        network.index
      );

    item.appendChild(remove);

  } else {

    const spacer =
      document.createElement("div");

    item.appendChild(spacer);
  }

  container.appendChild(item);

});

} catch (error) {

console.error(error);

}
}

async function scanWiFi() {

const button =
document.getElementById(
"scanButton"
);

const container =
document.getElementById(
"scanList"
);

button.disabled = true;

button.textContent =
"SCAN...";

container.innerHTML =
'<div class="empty">SCANNING WIFI...</div>';

try {

const response =
  await api("/api/wifi/scan");

const networks =
  await response.json();

container.innerHTML = "";

if (networks.length === 0) {

  container.innerHTML =
    '<div class="empty">NO NETWORK FOUND</div>';

  return;
}

const unique =
  new Map();

networks.forEach(network => {

  if (!network.ssid) {
    return;
  }

  const existing =
    unique.get(network.ssid);

  if (
    !existing ||
    network.rssi > existing.rssi
  ) {

    unique.set(
      network.ssid,
      network
    );
  }

});

Array.from(unique.values())
  .sort(
    (a, b) =>
      b.rssi - a.rssi
  )
  .forEach(network => {

    createScanRow(network);

  });

} catch (error) {

console.error(error);

container.innerHTML =
  '<div class="empty">SCAN FAILED</div>';

} finally {

button.disabled = false;

button.textContent =
  "SCAN";

}
}

function createScanRow(network) {

const container =
document.getElementById(
"scanList"
);

const row =
document.createElement("div");

row.className =
"scan-row";

const ssid =
document.createElement("div");

ssid.className =
"scan-ssid";

ssid.textContent =
network.ssid;

const rssi =
document.createElement("div");

rssi.className =
"scan-rssi";

rssi.textContent =
network.rssi + " dBm";

const password =
document.createElement("input");

password.className =
"scan-password";

password.type =
"password";

password.placeholder =
"PASSWORD";

password.autocomplete =
"off";

const save =
document.createElement("button");

save.className =
"save-button";

save.textContent =
"SAVE";

save.onclick =
() => saveScannedNetwork(
network.ssid,
password,
save
);

row.appendChild(ssid);
row.appendChild(rssi);
row.appendChild(password);
row.appendChild(save);

container.appendChild(row);
}

async function saveScannedNetwork(
ssid,
passwordInput,
button
) {

const password =
passwordInput.value;

button.disabled = true;
button.textContent = "...";

try {

const response =
  await api("/api/wifi");

const networks =
  await response.json();

let index =
  networks.find(
    network =>
      network.ssid === ssid
  )?.index;

if (index === undefined) {

  if (networks.length >= 5) {

    showMessage(
      "MAXIMUM 5 NETWORKS",
      true
    );

    return;
  }

  index =
    networks.length;
}

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
    method:"POST",
    body:body
  }
);

showMessage(
  "WIFI SAVED: " + ssid
);

passwordInput.value = "";

await loadWiFi();

setTimeout(
  updateStatus,
  1500
);

} catch (error) {

console.error(error);

showMessage(
  "SAVE FAILED",
  true
);

} finally {

button.disabled = false;
button.textContent = "SAVE";

}
}

async function deleteNetwork(index) {

if (
!confirm(
"DELETE THIS NETWORK?"
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
    method:"POST",
    body:body
  }
);

showMessage(
  "NETWORK DELETED"
);

await loadWiFi();

} catch (error) {

console.error(error);

showMessage(
  "DELETE FAILED",
  true
);

}
}

async function reconnectWiFi() {

try {

showMessage(
  "RECONNECTING..."
);

await api(
  "/api/wifi/reconnect",
  {
    method:"POST"
  }
);

setTimeout(
  updateStatus,
  2000
);

} catch (error) {

console.error(error);

showMessage(
  "RECONNECT FAILED",
  true
);

}
}

async function rebootBoard() {

if (
!confirm(
"RESTART BO4RD?"
)
) {
return;
}

try {

await api(
  "/api/reboot",
  {
    method:"POST"
  }
);

document.body.innerHTML = `
  <div style="
    height:100vh;
    display:flex;
    align-items:center;
    justify-content:center;
    color:#00eaff;
    font-family:monospace;
    text-align:center;
  ">
    <div>
      <div style="font-size:24px;">
        BO4RD
      </div>
      <div style="
        margin-top:10px;
        color:#00ff99;
      ">
        RESTARTING...
      </div>
    </div>
  </div>
`;

} catch (error) {

console.error(error);

}
}

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
