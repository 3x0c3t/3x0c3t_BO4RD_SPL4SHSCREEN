#ifndef PAGE_WEB_CSS_H
#define PAGE_WEB_CSS_H

const char PAGE_WEB_CSS[] PROGMEM = R"rawliteral(

:root {
  --bg: #020607;
  --panel: rgba(5, 15, 19, 0.94);
  --panel-light: rgba(7, 20, 25, 0.90);

  --cyan: #00eaff;
  --green: #00ff99;
  --red: #ff304f;

  --text: #d9ffff;
  --muted: #6d9999;

  --border: #12404a;

  --header-height: 58px;
  --footer-height: 34px;
}

* {
  box-sizing: border-box;
}

html,
body {
  width: 100%;
  height: 100%;
  margin: 0;
  padding: 0;
}

body {
  overflow: hidden;

  background:
    radial-gradient(
      circle at center,
      #09212a 0%,
      #031015 40%,
      #020607 80%
    );

  color: var(--text);

  font-family:
    "Courier New",
    monospace;

  font-size: 14px;
}

button,
input {
  font-family:
    "Courier New",
    monospace;
}

button {
  cursor: pointer;

  border: 1px solid var(--cyan);

  background:
    rgba(0, 234, 255, 0.03);

  color: var(--cyan);

  padding:
    8px 12px;

  font-size: 11px;

  letter-spacing: 1px;
}

button:hover {
  background: var(--cyan);
  color: #001014;
}

button.danger {
  border-color: var(--red);
  color: var(--red);
}

button.danger:hover {
  background: var(--red);
  color: #120006;
}

.header1 {
  position: fixed;

  top: 0;
  left: 0;

  width: 100%;
  height: var(--header-height);

  z-index: 100;

  display: grid;

  grid-template-columns:
    1fr
    auto
    1fr;

  align-items: center;

  padding:
    0 18px;

  border-bottom:
    1px solid var(--cyan);

  background:
    rgba(2, 8, 10, 0.96);

  box-shadow:
    0 0 18px
    rgba(0, 234, 255, 0.12);
}

.brand {
  display: flex;
  align-items: center;
  gap: 7px;
  white-space: nowrap;
}

.brand-main {
  color: var(--cyan);

  font-weight: bold;

  font-size:
    clamp(16px, 2vw, 24px);
}

.separator {
  color: var(--muted);
}

.brand-board {
  color: var(--text);

  font-weight: bold;

  font-size:
    clamp(14px, 1.8vw, 21px);
}

.control-title {
  color: var(--green);

  font-weight: bold;

  letter-spacing: 3px;

  text-align: center;

  white-space: nowrap;

  font-size:
    clamp(12px, 1.5vw, 17px);
}

.header-actions {
  display: flex;

  justify-content: flex-end;

  gap: 8px;
}

main {
  position: fixed;

  top: var(--header-height);
  left: 0;

  width: 100%;

  height:
    calc(
      100vh -
      var(--header-height) -
      var(--footer-height)
    );

  overflow: hidden;
}

.status-panel {
  position: absolute;

  z-index: 20;

  top: 4vh;
  left: 4vw;

  width:
    min(
      340px,
      30vw
    );

  padding: 18px;

  border:
    1px solid var(--cyan);

  background:
    var(--panel);

  box-shadow:
    0 0 25px
    rgba(0, 234, 255, 0.10);
}

.panel-title {
  margin-bottom: 15px;

  color: var(--cyan);

  font-size:
    clamp(15px, 1.5vw, 20px);

  font-weight: bold;

  letter-spacing: 4px;
}

.status-content {
  display: flex;

  flex-direction: column;

  gap: 8px;
}

.status-row {
  display: grid;

  grid-template-columns:
    60px
    1fr;

  gap: 12px;

  align-items: baseline;

  padding:
    7px 0;

  border-bottom:
    1px solid
    rgba(18, 64, 74, 0.65);
}

.status-label {
  color: var(--muted);

  font-size: 10px;

  letter-spacing: 1px;
}

.status-row strong {
  color: var(--text);

  font-size: 12px;

  overflow: hidden;

  text-overflow: ellipsis;

  white-space: nowrap;
}

.connection-status {
  margin-top: 14px;

  padding: 8px;

  text-align: center;

  border:
    1px solid var(--red);

  color: var(--red);

  font-size: 11px;

  letter-spacing: 2px;
}

.connection-status.online {
  color: var(--green);

  border-color:
    var(--green);
}

.wifi-panel {
  position: absolute;

  z-index: 10;

  top: 7vh;
  right: 5vw;

  width:
    min(
      720px,
      65vw
    );

  height: 78vh;

  padding: 22px;

  border:
    1px solid var(--cyan);

  background:
    var(--panel-light);

  overflow-y: auto;
  overflow-x: hidden;

  box-shadow:
    0 0 35px
    rgba(0, 234, 255, 0.08);
}

.scan-bar {
  position: absolute;

  top: 17px;
  right: 20px;
}

.scan-button {
  min-width: 90px;

  color: var(--green);

  border-color:
    var(--green);
}

.network-section {
  margin-top: 22px;
}

.section-title {
  margin-bottom: 9px;

  padding-bottom: 7px;

  border-bottom:
    1px solid var(--border);

  color: var(--green);

  font-size: 11px;

  letter-spacing: 2px;
}

.network-list {
  display: flex;

  flex-direction: column;

  gap: 7px;
}

.empty-network {
  padding: 13px;

  border:
    1px dashed var(--border);

  color: var(--muted);

  font-size: 11px;

  text-align: center;
}

.network-item {
  display: grid;

  grid-template-columns:
    minmax(0, 1fr)
    90px
    auto;

  gap: 10px;

  align-items: center;

  min-height: 46px;

  padding:
    7px 9px;

  border:
    1px solid var(--border);

  background:
    rgba(0, 0, 0, 0.25);
}

.network-item:hover {
  border-color: var(--cyan);

  background:
    rgba(0, 234, 255, 0.04);
}

.network-name {
  overflow: hidden;

  text-overflow: ellipsis;

  white-space: nowrap;

  color: var(--text);

  font-size: 12px;
}

.network-rssi {
  color: var(--muted);

  text-align: right;

  font-size: 11px;
}

.network-save {
  min-width: 60px;

  padding:
    6px 9px;

  color: var(--green);

  border-color:
    var(--green);
}

.network-delete {
  min-width: 60px;

  padding:
    6px 9px;

  color: var(--red);

  border-color:
    var(--red);
}

.network-priority {
  color: var(--green);

  font-size: 9px;

  letter-spacing: 1px;
}

.password-panel {
  position: absolute;

  z-index: 50;

  top: 50%;
  left: 50%;

  transform:
    translate(-50%, -50%);

  width:
    min(
      420px,
      85vw
    );

  padding: 22px;

  border:
    1px solid var(--green);

  background:
    rgba(2, 9, 12, 0.98);

  box-shadow:
    0 0 40px
    rgba(0, 255, 153, 0.15);
}

.hidden {
  display: none;
}

.selected-network {
  display: flex;

  justify-content: space-between;

  gap: 15px;

  padding: 10px;

  margin-bottom: 15px;

  border:
    1px solid var(--border);
}

.selected-network span {
  color: var(--muted);

  font-size: 10px;
}

.selected-network strong {
  color: var(--green);

  overflow: hidden;

  text-overflow: ellipsis;

  white-space: nowrap;
}

label {
  display: block;

  margin-bottom: 6px;

  color: var(--muted);

  font-size: 10px;

  letter-spacing: 1px;
}

input {
  width: 100%;

  padding: 11px;

  border:
    1px solid var(--border);

  outline: none;

  background: #010708;

  color: var(--text);

  font-size: 13px;
}

input:focus {
  border-color:
    var(--cyan);
}

.save-button {
  margin-top: 14px;

  color: var(--green);

  border-color:
    var(--green);
}

.cancel-button {
  margin-top: 14px;

  margin-left: 7px;

  color: var(--muted);

  border-color:
    var(--border);
}

footer {
  position: fixed;

  z-index: 100;

  bottom: 0;
  left: 0;

  width: 100%;
  height: var(--footer-height);

  display: flex;

  align-items: center;

  justify-content: center;

  gap: 9px;

  border-top:
    1px solid var(--border);

  background:
    rgba(2, 8, 10, 0.96);

  color: var(--muted);

  font-size: 10px;

  letter-spacing: 1px;
}

@media (max-width: 900px) {

  .header1 {
    grid-template-columns:
      1fr
      auto;

    height: 62px;
  }

  .control-title {
    display: none;
  }

  .status-panel {
    top: 3vh;
    left: 3vw;

    width: 38vw;
  }

  .wifi-panel {
    top: 5vh;
    right: 3vw;

    width: 63vw;
  }

}

@media (max-width: 600px) {

  :root {
    --header-height: 54px;
    --footer-height: 30px;
  }

  .header1 {
    padding: 0 8px;

    grid-template-columns:
      1fr
      auto;

    gap: 5px;
  }

  .brand-main {
    font-size: 14px;
  }

  .brand-board {
    font-size: 12px;
  }

  .header-actions {
    gap: 3px;
  }

  .header-actions button {
    padding: 7px 5px;

    font-size: 8px;

    letter-spacing: 0;
  }

  .status-panel {
    top: 2vh;
    left: 3vw;

    width: 57vw;

    padding: 11px;
  }

  .panel-title {
    margin-bottom: 9px;

    font-size: 12px;

    letter-spacing: 2px;
  }

  .status-row {
    grid-template-columns:
      42px
      1fr;

    gap: 6px;

    padding: 5px 0;
  }

  .status-label {
    font-size: 8px;
  }

  .status-row strong {
    font-size: 9px;
  }

  .connection-status {
    margin-top: 8px;

    padding: 6px;

    font-size: 8px;
  }

  .wifi-panel {
    top: 10vh;

    left: 6vw;

    right: auto;

    width: 91vw;

    height: 77vh;

    padding: 13px;
  }

  .scan-bar {
    top: 9px;

    right: 11px;
  }

  .scan-button {
    min-width: 60px;

    padding: 6px;

    font-size: 8px;
  }

  .network-section {
    margin-top: 16px;
  }

  .network-item {
    grid-template-columns:
      minmax(0, 1fr)
      58px
      auto;

    gap: 5px;

    min-height: 41px;

    padding: 5px;
  }

  .network-name {
    font-size: 10px;
  }

  .network-rssi {
    font-size: 9px;
  }

  .network-save,
  .network-delete {
    min-width: 48px;

    padding: 5px;

    font-size: 8px;
  }

  .password-panel {
    width: 84vw;

    padding: 15px;
  }

  footer {
    font-size: 7px;

    gap: 4px;
  }

}

)rawliteral";

#endif