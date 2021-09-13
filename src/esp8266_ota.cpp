#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <LittleFS.h>
#include <CertStoreBearSSL.h>
#include <ESP_OTA_GitHub.h>

// Include version as string, falling back to an empty string if undefined
#define STRINGIFY(s) STRINGIFY1(s)
#define STRINGIFY1(s) #s
#ifdef VERSION
const char *version = STRINGIFY(VERSION);
#else
const char *version = "";
#endif

/* Set up values for your repository and binary names */
#define GHOTA_USER "bertbaron"
#define GHOTA_REPO "esp8266_ota_update"
#define GHOTA_BIN_FILE "firmware.bin"
#define GHOTA_ACCEPT_PRERELEASE 0


BearSSL::CertStore certStore;

bool do_update_check = true;

void handle_upgade()
{
  // Initialise Update Code
  //We do this locally so that the memory used is freed when the function exists.
  ESPOTAGitHub ESPOTAGitHub(&certStore, GHOTA_USER, GHOTA_REPO, version, GHOTA_BIN_FILE, GHOTA_ACCEPT_PRERELEASE);

  Serial.println("Checking for update...");
  if (ESPOTAGitHub.checkUpgrade())
  {
    Serial.print("Upgrade found at: ");
    Serial.println(ESPOTAGitHub.getUpgradeURL());
    if (ESPOTAGitHub.doUpgrade())
    {
      Serial.println("Upgrade complete."); //This should never be seen as the device should restart on successful upgrade.
    }
    else
    {
      Serial.print("Unable to upgrade: ");
      Serial.println(ESPOTAGitHub.getLastError());
    }
  }
  else
  {
    Serial.print("Not proceeding to upgrade: ");
    Serial.println(ESPOTAGitHub.getLastError());
  }
}

void connect_wifi()
{
  WiFi.mode(WIFI_STA);
  File settings = LittleFS.open("/settings.json", "r");
  String json = settings.readString();
  StaticJsonDocument<1024> doc;
  deserializeJson(doc, json);
  const char* ssid = doc["ssid"];
  const char* password = doc["password"];

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void setup()
{
  Serial.begin(9600);
  Serial.println("");
  Serial.print("Version: ");
  Serial.println(version);

  LittleFS.begin();
  int numCerts = certStore.initCertStore(LittleFS, PSTR("/certs.idx"), PSTR("/certs.ar"));
  Serial.print(F("Number of CA certs read: "));
  Serial.println(numCerts);
  if (numCerts == 0)
  {
    Serial.println(F("No certs found. Did you run certs-from-mozill.py and upload the SPIFFS directory before running?"));
    return; // Can't connect to anything w/o certs!
  }

  connect_wifi();

  if (strlen(version) == 0) {
    Serial.println("Skipping update check because no version is set");
    do_update_check = false;
    return;
  }
}

long lastCheckMillis=0;
void loop()
{
  long currentMillis = millis();
  if (do_update_check && currentMillis - lastCheckMillis > 60000) {
    handle_upgade();
    lastCheckMillis = currentMillis;
  }
}
