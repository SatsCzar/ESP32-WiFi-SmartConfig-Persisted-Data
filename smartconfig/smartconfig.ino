#include "esp_wifi.h"
#include <WiFi.h>
#include <Preferences.h>
#include <string>
#include "esp_system.h"
#include <HTTPClient.h>

const char* MEMPOOL_URL = "https://mempool.space/api/blocks/tip/height";
const int WIFI_CONNECTION_TIMEOUT = 200;

Preferences preferences;
HTTPClient http;

void setup() {
  Serial.begin(115200);
  initWiFi();
}

void initWiFi() {
  WiFi.mode(WIFI_AP_STA);

  if (dontHaveWiFiDataInPrefs()) {
    initWiFiSmartConfig();
    delay(3000);
    ESP.restart();
  }

  Serial.println("have WiFi data, connecting");

  String ssid = getPrefsSsidPasswd("ssid");
  String passwd = getPrefsSsidPasswd("pass");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), passwd.c_str());

  Serial.println("Connecting");

  int count = 0;
  while (waitingWiFiConnection(WiFi.status(), count)) {
    count++;
    delay(100);
  }

  if (connectionFailed(WiFi.status())) {
    Serial.println("Connection failed");

    while (true) {
      delay(100);
    }
  }

  Serial.println("Connected");
}

void initWiFiSmartConfig() {
  WiFi.beginSmartConfig(SC_TYPE_ESPTOUCH);
  Serial.println("Waiting for Smartconfig");

  while (!WiFi.smartConfigDone()) {
    delay(500);
  }

  Serial.println("SmartConfig Recebido!");

  int count = 0;
  while (waitingWiFiConnection(WiFi.status(), count)) {
    count++;
    delay(100);
  }

  if (!connectionFailed(WiFi.status())) {
    Serial.println("Connected");

    String ssid = getSsidPasswd("ssid");
    String passwd = getSsidPasswd("pass");

    saveWiFiDataInPrefs(ssid, passwd);

    Serial.println("Restarting");
  }
}

boolean waitingWiFiConnection(wl_status_t status, int count) {
  if ((status != WL_CONNECTED && status != WL_CONNECT_FAILED && status != WL_NO_SSID_AVAIL) && count <= WIFI_CONNECTION_TIMEOUT) {
    return true;
  }

  return false;
}

boolean connectionFailed(wl_status_t status) {
  if (status == WL_NO_SSID_AVAIL || status == WL_IDLE_STATUS || status == WL_CONNECT_FAILED || status == WL_DISCONNECTED) {
    return true;
  }

  return false;
}

boolean dontHaveWiFiDataInPrefs() {
  String ssid = getPrefsSsidPasswd("ssid");

  if (ssid != "") {
    return false;
  }

  return true;
}

String getPrefsSsidPasswd(String selector) {
  preferences.begin("wifi");
  String value = "";

  if (selector == "ssid") {
    value = preferences.getString("ssid", "");
  }

  if (selector == "pass") {
    value = preferences.getString("passwd", "");
  }

  preferences.end();

  return value;
}

String getSsidPasswd(String selector) {
  wifi_config_t conf;
  esp_wifi_get_config(WIFI_IF_STA, &conf);

  if (selector == "ssid") {
    return String(reinterpret_cast<const char*>(conf.sta.ssid));
  }

  if (selector == "pass") {
    return String(reinterpret_cast<const char*>(conf.sta.password));
  }

  return "";
}

void saveWiFiDataInPrefs(String ssid, String passwd) {
  preferences.begin("wifi");
  preferences.putString("ssid", ssid);
  preferences.putString("passwd", passwd);
  preferences.end();
}

void loop() {
  http.begin(MEMPOOL_URL);

  int httpStatusCode = http.GET();
  if (httpStatusCode == 200) {
    Serial.println(http.getString());
  }
  else {
    Serial.println("ERR: " + httpStatusCode);
  }
  delay(1000);
}