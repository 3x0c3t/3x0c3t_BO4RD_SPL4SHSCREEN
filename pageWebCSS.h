#ifndef PAGE_WEB_CSS_H
#define PAGE_WEB_CSS_H

const char PAGE_WEB_CSS[] PROGMEM = R"rawliteral(

:root {
--bg:#020607;
--panel:#071014;
--panel2:#050c10;
--cyan:#00eaff;
--green:#00ff99;
--red:#ff304f;
--yellow:#ffe600;
--text:#d9ffff;
--muted:#62888d;
--line:#153b43;
}

* {
  box-sizing:border-box;
  margin:0;
  padding:0;
  }

html,
body {
width:100%;
height:100%;
overflow:hidden;
}

body {
background:
radial-gradient(
circle at center,
#071820 0%,
#020607 70%
);
color:var(--text);
font-family:"Courier New",monospace;
font-size:13px;
}

header {
height:62px;
display:flex;
align-items:center;
justify-content:space-between;
padding:0 24px;
border-bottom:1px solid var(--cyan);
background:rgba(2,8,11,.96);
}

.brand {
display:flex;
align-items:baseline;
gap:10px;
}

.logo {
color:var(--cyan);
font-size:22px;
font-weight:bold;
}

.separator {
color:var(--muted);
}

.board-title {
color:var(--text);
font-size:24px;
font-weight:bold;
letter-spacing:4px;
}

.subtitle {
color:var(--green);
font-size:11px;
letter-spacing:3px;
}

main {
height:calc(100vh - 94px);
padding:12px;
display:grid;
grid-template-columns:
minmax(240px,.75fr)
minmax(360px,1.5fr)
minmax(220px,.75fr);
grid-template-rows:
minmax(0,1fr)
minmax(0,1fr);
gap:12px;
}

.panel {
min-width:0;
min-height:0;
padding:14px;
border:1px solid var(--line);
background:rgba(4,14,18,.94);
box-shadow:
inset 0 0 20px rgba(0,234,255,.025);
}

.panel-title {
color:var(--cyan);
font-size:14px;
font-weight:bold;
letter-spacing:3px;
padding-bottom:8px;
border-bottom:1px solid var(--line);
}

.status-panel {
grid-column:1;
grid-row:1;
display:flex;
flex-direction:column;
}

.status-grid {
display:grid;
grid-template-columns:1fr 1fr;
gap:8px;
margin-top:10px;
}

.info-box {
min-width:0;
padding:9px;
border:1px solid var(--line);
background:rgba(0,0,0,.25);
}

.info-box span {
display:block;
color:var(--muted);
font-size:9px;
letter-spacing:1px;
margin-bottom:4px;
}

.info-box strong {
display:block;
color:var(--text);
font-size:12px;
overflow:hidden;
text-overflow:ellipsis;
white-space:nowrap;
}

.connection {
margin-top:auto;
padding:10px;
text-align:center;
border:1px solid;
font-weight:bold;
letter-spacing:2px;
}

.connection.online {
color:var(--green);
border-color:var(--green);
}

.connection.setup {
color:var(--yellow);
border-color:var(--yellow);
}

.connection.offline {
color:var(--red);
border-color:var(--red);
}

.wifi-panel {
grid-column:2;
grid-row:1 / 3;
display:flex;
flex-direction:column;
}

.panel-head {
display:flex;
align-items:center;
justify-content:space-between;
gap:10px;
}

.scan-button {
min-width:80px;
}

.section-label {
color:var(--green);
font-size:10px;
letter-spacing:2px;
margin:10px 0 6px;
}

.scan-label {
margin-top:10px;
}

.saved-list,
.scan-list {
min-height:0;
overflow:hidden;
}

.saved-list {
flex:0 0 auto;
}

.scan-list {
flex:1 1 auto;
}

.wifi-row {
display:grid;
grid-template-columns:minmax(0,1fr) auto auto;
align-items:center;
gap:7px;
min-height:34px;
padding:6px 8px;
margin-bottom:5px;
border:1px solid var(--line);
}

.wifi-row.priority {
border-color:var(--green);
}

.wifi-name {
min-width:0;
overflow:hidden;
text-overflow:ellipsis;
white-space:nowrap;
}

.wifi-meta {
color:var(--muted);
font-size:9px;
}

.priority {
color:var(--green);
}

.small-button {
padding:5px 8px;
font-size:10px;
}

.scan-row {
display:grid;
grid-template-columns:
minmax(100px,1fr)
55px
minmax(100px,1fr)
auto;
align-items:center;
gap:6px;
min-height:38px;
padding:5px 7px;
margin-bottom:5px;
border:1px solid #194650;
}

.scan-row:hover {
border-color:var(--cyan);
}

.scan-ssid {
min-width:0;
overflow:hidden;
text-overflow:ellipsis;
white-space:nowrap;
}

.scan-rssi {
color:var(--muted);
text-align:right;
font-size:9px;
}

.scan-password {
width:100%;
min-width:0;
padding:7px;
}

.save-button {
padding:7px 9px;
font-size:10px;
}

.empty {
padding:12px;
text-align:center;
color:var(--muted);
border:1px dashed var(--line);
}

.board-panel {
grid-column:1;
grid-row:2;
}

.board-grid {
display:grid;
grid-template-columns:1fr;
gap:8px;
margin-top:10px;
}

.controls-panel {
grid-column:3;
grid-row:1 / 3;
display:flex;
flex-direction:column;
}

.controls {
display:flex;
flex-direction:column;
gap:8px;
margin-top:10px;
}

.message {
margin-top:auto;
min-height:24px;
padding:6px;
color:var(--green);
font-size:10px;
text-align:center;
}

button {
padding:9px 12px;
border:1px solid var(--cyan);
background:transparent;
color:var(--cyan);
font-family:"Courier New",monospace;
font-size:11px;
font-weight:bold;
cursor:pointer;
}

button:hover {
background:var(--cyan);
color:#001014;
}

button:disabled {
opacity:.35;
cursor:wait;
}

button.danger {
border-color:var(--red);
color:var(--red);
}

button.danger:hover {
background:var(--red);
color:#120006;
}

input {
width:100%;
padding:7px;
border:1px solid #22505a;
outline:none;
background:#010708;
color:var(--text);
font-family:"Courier New",monospace;
font-size:11px;
}

input:focus {
border-color:var(--cyan);
}

footer {
height:32px;
display:flex;
align-items:center;
justify-content:center;
gap:8px;
border-top:1px solid var(--line);
color:var(--muted);
font-size:9px;
}

@media (max-width:900px) {

header {
padding:0 14px;
}

.subtitle {
display:none;
}

main {
grid-template-columns:1fr 1fr;
grid-template-rows:
minmax(0,.8fr)
minmax(0,1.2fr);
}

.status-panel {
grid-column:1;
grid-row:1;
}

.wifi-panel {
grid-column:1 / 3;
grid-row:2;
}

.board-panel {
grid-column:2;
grid-row:1;
}

.controls-panel {
display:none;
}

.scan-row {
grid-template-columns:
minmax(90px,1fr)
50px
minmax(90px,1fr)
auto;
}
}

@media (max-width:600px) {

header {
height:50px;
padding:0 10px;
}

.logo {
font-size:17px;
}

.board-title {
font-size:19px;
letter-spacing:2px;
}

.separator {
display:none;
}

main {
height:calc(100vh - 76px);
padding:7px;
gap:7px;
grid-template-columns:1fr;
grid-template-rows:
105px
minmax(0,1fr)
72px;
}

.panel {
padding:9px;
}

.status-panel {
grid-column:1;
grid-row:1;
}

.status-grid {
grid-template-columns:repeat(4,1fr);
gap:4px;
margin-top:6px;
}

.info-box {
padding:5px;
}

.info-box span {
font-size:7px;
margin-bottom:2px;
}

.info-box strong {
font-size:9px;
}

.connection {
display:none;
}

.wifi-panel {
grid-column:1;
grid-row:2;
}

.board-panel {
grid-column:1;
grid-row:3;
}

.controls-panel {
display:none;
}

.panel-title {
font-size:11px;
padding-bottom:5px;
}

.section-label {
font-size:8px;
margin:5px 0 4px;
}

.wifi-row {
min-height:28px;
padding:4px 6px;
}

.scan-row {
grid-template-columns:
minmax(70px,1fr)
40px
minmax(70px,1fr)
auto;
min-height:32px;
gap:4px;
padding:4px;
}

.scan-password {
padding:5px;
}

.save-button {
padding:5px 6px;
font-size:8px;
}

footer {
height:26px;
font-size:7px;
}
}

@media (max-height:600px) {

header {
height:44px;
}

main {
height:calc(100vh - 68px);
}

footer {
height:24px;
}

.panel {
padding:7px;
}

.section-label {
margin:3px 0;
}

.scan-row {
min-height:29px;
}

.scan-password {
padding:4px;
}

button {
padding:6px 9px;
}
}

)rawliteral";

#endif
