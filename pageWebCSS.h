#ifndef PAGE_WEB_CSS_H
#define PAGE_WEB_CSS_H

// ==================================================
// WEB PAGE CSS
// ==================================================

const char PAGE_WEB_CSS[] PROGMEM = R"rawliteral(

:root {

  --bg: #020607;
  --panel: #071014;
  --border: #00eaff;
  --text: #d9ffff;
  --muted: #6d9999;
  --green: #00ff99;
  --red: #ff304f;

}

* {

  box-sizing: border-box;

}

html,
body {

  margin: 0;
  padding: 0;

  min-height: 100%;

  background:
    radial-gradient(
      circle at center,
      #071820 0%,
      var(--bg) 70%
    );

  color: var(--text);

  font-family:
    monospace;

}

body {

  min-height: 100vh;

  display: flex;

  flex-direction: column;

}

header {

  padding: 22px;

  border-bottom:
    1px solid var(--border);

  text-align: center;

}

.logo {

  color: var(--border);

  font-size: 28px;

  font-weight: bold;

}

.title {

  margin-top: 5px;

  font-size: 32px;

  letter-spacing: 5px;

}

.subtitle {

  margin-top: 4px;

  color: var(--green);

  font-size: 12px;

  letter-spacing: 3px;

}

main {

  width: min(
    900px,
    calc(100% - 30px)
  );

  margin: 20px auto;

  flex: 1;

}

.panel {

  margin-bottom: 18px;

  padding: 18px;

  border:
    1px solid #12404a;

  background:
    rgba(4, 14, 18, 0.92);

}

h2 {

  margin-top: 0;

  color: var(--border);

  font-size: 17px;

  letter-spacing: 3px;

}

h3 {

  color: var(--green);

  font-size: 14px;

}

.status-grid {

  display: grid;

  grid-template-columns:
    repeat(2, 1fr);

  gap: 12px;

}

.status-grid div,
.board-info div {

  padding: 12px;

  border:
    1px solid #153b43;

}

span {

  display: block;

  color: var(--muted);

  font-size: 11px;

  margin-bottom: 6px;

}

strong {

  display: block;

  word-break: break-word;

}

.status {

  margin-top: 15px;

  padding: 12px;

  text-align: center;

  border: 1px solid;

}

.online {

  color: var(--green);

  border-color: var(--green);

}

.offline {

  color: var(--red);

  border-color: var(--red);

}

.panel-header {

  display: flex;

  align-items: center;

  justify-content: space-between;

}

.wifi-list {

  display: flex;

  flex-direction: column;

  gap: 8px;

}

.wifi-item {

  display: grid;

  grid-template-columns:
    1fr
    auto
    auto;

  gap: 10px;

  align-items: center;

  padding: 12px;

  border:
    1px solid #153b43;

}

.wifi-item.priority {

  border-color:
    var(--green);

}

.wifi-name {

  color: var(--text);

}

.priority-label {

  color: var(--green);

  font-size: 11px;

}

button {

  padding: 10px 15px;

  border:
    1px solid var(--border);

  background: transparent;

  color: var(--border);

  font-family: monospace;

  cursor: pointer;

}

button:hover {

  background: var(--border);

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

.network-add {

  margin-top: 20px;

  padding-top: 15px;

  border-top:
    1px solid #153b43;

}

label {

  display: block;

  margin: 10px 0 5px;

  color: var(--muted);

  font-size: 12px;

}

input {

  width: 100%;

  padding: 11px;

  border:
    1px solid #22505a;

  outline: none;

  background: #010708;

  color: var(--text);

  font-family: monospace;

}

input:focus {

  border-color:
    var(--border);

}

.board-info {

  display: grid;

  grid-template-columns:
    repeat(2, 1fr);

  gap: 12px;

}

.controls {

  display: flex;

  gap: 10px;

  flex-wrap: wrap;

}

footer {

  padding: 15px;

  text-align: center;

  border-top:
    1px solid #12343b;

  color: var(--muted);

  font-size: 11px;

}

@media (max-width: 600px) {

  .status-grid,
  .board-info {

    grid-template-columns: 1fr;

  }

  .wifi-item {

    grid-template-columns:
      1fr auto;

  }

}

)rawliteral";

#endif