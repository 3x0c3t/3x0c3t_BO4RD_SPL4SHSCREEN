#ifndef PAGE_WEB_CSS_H
#define PAGE_WEB_CSS_H

const char PAGE_WEB_CSS[] PROGMEM = R"rawliteral(

:root {

  --bg: #020607;

  --panel: rgba(5, 15, 19, 0.96);

  --panel-light: rgba(7, 20, 25, 0.96);

  --cyan: #00eaff;

  --green: #00ff99;

  --red: #ff304f;

  --text: #d9ffff;

  --muted: #6d9999;

  --border: #12404a;

  --header1-height: 58px;

  --header2-height: 108px;

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
      #031015 45%,
      #020607 100%
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

  border:
    1px solid var(--cyan);

  background:
    rgba(0, 234, 255, 0.03);

  color: var(--cyan);

  padding:
    8px 12px;

  cursor: pointer;

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


/* =========================================================
   HEADER 1
   ========================================================= */

.header1 {

  position: fixed;

  top: 0;

  left: 0;

  width: 100%;

  height: var(--header1-height);

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
    rgba(2, 8, 10, 0.98);

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


/* =========================================================
   HEADER 2
   ========================================================= */

.header2 {

  position: fixed;

  top: var(--header1-height);

  left: 0;

  width: 100%;

  height: var(--header2-height);

  z-index: 90;

  display: grid;

  grid-template-columns:
    100px
    1fr
    auto;

  align-items: center;

  gap: 20px;

  padding:
    12px 20px;

  border-bottom:
    1px solid var(--border);

  background:
    rgba(3, 12, 15, 0.98);

}


.status-title {

  color: var(--cyan);

  font-weight: bold;

  font-size: 16px;

  letter-spacing: 3px;

}


.status-grid {

  display: grid;

  grid-template-columns:
    repeat(
      4,
      minmax(
        120px,
        1fr
      )
    );

  gap: 10px;

  min-width: 0;

}


.status-item {

  display: flex;

  flex-direction: column;

  gap: 5px;

  min-width: 0;

  padding:
    7px 10px;

  border-left:
    1px solid var(--border);

}


.status-label {

  color: var(--muted);

  font-size: 9px;

  letter-spacing: 1px;

}


.status-item strong {

  color: var(--text);

  font-size: 12px;

  overflow: hidden;

  text-overflow: ellipsis;

  white-space: nowrap;

}


.connection-status {

  min-width: 90px;

  padding:
    8px 10px;

  text-align: center;

  border:
    1px solid var(--red);

  color: var(--red);

  font-size: 10px;

  letter-spacing: 1px;

}


.connection-status.online {

  color: var(--green);

  border-color: var(--green);

}


/* =========================================================
   MAIN
   ========================================================= */

main {

  position: fixed;

  top:
    calc(
      var(--header1-height)
      +
      var(--header2-height)
    );

  left: 0;

  width: 100%;

  height:
    calc(
      100vh
      -
      var(--header1-height)
      -
      var(--header2-height)
      -
      var(--footer-height)
    );

  padding: 18px;

  overflow: hidden;

  display: flex;

  justify-content: center;

  align-items: flex-start;

}


/* =========================================================
   WIFI
   ========================================================= */

.wifi-panel {

  position: relative;

  width:
    min(
      1100px,
      100%
    );

  height: 100%;

  padding: 20px;

  border:
    1px solid var(--cyan);

  background:
    var(--panel-light);

  box-shadow:
    0 0 30px
    rgba(
      0,
      234,
      255,
      0.08
    );

  overflow-y: auto;

  overflow-x: hidden;

}


.panel-header {

  display: flex;

  align-items: center;

  justify-content: space-between;

  gap: 20px;

  padding-bottom: 12px;

  border-bottom:
    1px solid var(--border);

}


.panel-title {

  color: var(--cyan);

  font-size: 17px;

  font-weight: bold;

  letter-spacing: 4px;

}


.scan-button {

  color: var(--green);

  border-color: var(--green);

  min-width: 90px;

}


/* =========================================================
   NETWORK SECTIONS
   ========================================================= */

.network-section {

  margin-top: 20px;

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


/* =========================================================
   NETWORK ROW
   ========================================================= */

.network-item {

  display: grid;

  grid-template-columns:
    minmax(160px, 1fr)
    90px
    minmax(180px, 240px)
    70px;

  gap: 10px;

  align-items: center;

  min-height: 48px;

  padding:
    7px 9px;

  border:
    1px solid var(--border);

  background:
    rgba(
      0,
      0,
      0,
      0.25
    );

}


.network-item:hover {

  border-color: var(--cyan);

  background:
    rgba(
      0,
      234,
      255,
      0.04
    );

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


.network-password {

  width: 100%;

  height: 32px;

  padding:
    6px 8px;

  border:
    1px solid var(--border);

  outline: none;

  background:
    #010708;

  color: var(--text);

  font-size: 11px;

}


.network-password:focus {

  border-color: var(--cyan);

}


.network-password::placeholder {

  color: var(--muted);

}


.network-save {

  min-width: 65px;

  padding:
    7px 8px;

  color: var(--green);

  border-color: var(--green);

}


.network-delete {

  min-width: 65px;

  padding:
    7px 8px;

  color: var(--red);

  border-color: var(--red);

}


.network-priority {

  color: var(--green);

  font-size: 9px;

  letter-spacing: 1px;

}


/* =========================================================
   FOOTER
   ========================================================= */

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
    rgba(
      2,
      8,
      10,
      0.98
    );

  color: var(--muted);

  font-size: 10px;

  letter-spacing: 1px;

}


/* =========================================================
   TABLET
   ========================================================= */

@media (max-width: 900px) {

  :root {

    --header1-height: 58px;

    --header2-height: 130px;

  }


  .header1 {

    grid-template-columns:
      1fr
      auto;

  }


  .control-title {

    display: none;

  }


  .header2 {

    grid-template-columns:
      80px
      1fr;

    grid-template-rows:
      1fr
      auto;

    gap:
      8px 15px;

  }


  .status-grid {

    grid-template-columns:
      repeat(
        4,
        minmax(
          90px,
          1fr
        )
      );

  }


  .connection-status {

    grid-column: 2;

    justify-self: start;

  }


  .network-item {

    grid-template-columns:
      minmax(130px, 1fr)
      75px
      minmax(140px, 1fr)
      65px;

  }

}


/* =========================================================
   MOBILE
   ========================================================= */

@media (max-width: 600px) {

  :root {

    --header1-height: 54px;

    --header2-height: 170px;

    --footer-height: 30px;

  }


  .header1 {

    padding:
      0 8px;

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

    padding:
      7px 5px;

    font-size: 8px;

    letter-spacing: 0;

  }


  .header2 {

    display: flex;

    flex-direction: column;

    align-items: stretch;

    justify-content: center;

    gap: 7px;

    padding:
      8px 10px;

  }


  .status-title {

    font-size: 12px;

    letter-spacing: 2px;

  }


  .status-grid {

    display: grid;

    grid-template-columns:
      1fr 1fr;

    gap: 5px;

  }


  .status-item {

    padding:
      4px 7px;

  }


  .status-label {

    font-size: 7px;

  }


  .status-item strong {

    font-size: 9px;

  }


  .connection-status {

    width: 100%;

    min-width: 0;

    padding: 5px;

    font-size: 8px;

  }


  main {

    padding: 10px;

  }


  .wifi-panel {

    width: 100%;

    height: 100%;

    padding: 12px;

  }


  .panel-title {

    font-size: 13px;

    letter-spacing: 2px;

  }


  .scan-button {

    min-width: 60px;

    padding: 6px;

    font-size: 8px;

  }


  .network-section {

    margin-top: 14px;

  }


  .network-item {

    grid-template-columns:
      minmax(100px, 1fr)
      55px;

    gap: 6px;

    padding: 7px;

  }


  .network-name {

    font-size: 10px;

  }


  .network-rssi {

    font-size: 8px;

    text-align: right;

  }


  .network-password {

    grid-column:
      1 / 2;

    width: 100%;

    height: 32px;

    font-size: 9px;

  }


  .network-save {

    grid-column:
      2;

    grid-row:
      2;

    min-width: 50px;

    padding: 6px;

    font-size: 8px;

  }


  .network-delete {

    grid-column:
      2;

    grid-row:
      1;

    min-width: 50px;

    padding: 5px;

    font-size: 8px;

  }


  footer {

    font-size: 7px;

    gap: 4px;

  }

}

)rawliteral";

#endif