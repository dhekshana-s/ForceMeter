#include <WiFi.h>
#include <WebServer.h>
#include "HX711.h"

// ---------------- PIN CONNECTIONS ----------------
#define DT 18
#define SCK 19

// ---------------- LOAD CELL ----------------
HX711 scale;

// Your experimentally determined calibration
const float COUNTS_PER_GRAM = 189.51;

long zeroRaw = 0;

// ---------------- WIFI ----------------
const char* ssid = "ForceMeter";
const char* password = "12345678";

// Create web server on port 80
WebServer server(80);

// ---------------- VARIABLES ----------------
float currentMass = 0;
float currentForce = 0;


// =================================================
// WEBPAGE
// =================================================

void handleRoot() {

  String webpage = R"rawliteral(
<!DOCTYPE html>
<html>

<head>

<meta name="viewport" content="width=device-width, initial-scale=1">

<title>Force Measurement</title>

<style>

body {
  font-family: Arial, sans-serif;
  text-align: center;
  background: #f2f7f4;
  margin: 0;
  padding: 30px 15px;
}

.container {
  max-width: 500px;
  margin: auto;
  background: white;
  padding: 30px;
  border-radius: 20px;
  box-shadow: 0px 4px 15px rgba(0,0,0,0.15);
}

h1 {
  margin-bottom: 30px;
}

.force {
  font-size: 60px;
  font-weight: bold;
  margin: 20px 0;
}

.unit {
  font-size: 24px;
}

.mass {
  font-size: 25px;
  margin-top: 25px;
}

.status {
  margin-top: 25px;
  color: #555;
}

</style>

</head>

<body>

<div class="container">

<h1>FORCE MEASUREMENT</h1>

<div class="force">
<span id="force">0.000</span>
<span class="unit">N</span>
</div>

<div class="mass">
Mass: <span id="mass">0.0</span> g
</div>

<div class="status">
ESP32 Connected
</div>

</div>

<script>

function updateData() {

  fetch("/data")
  .then(response => response.json())
  .then(data => {

    document.getElementById("force").innerHTML =
      data.force.toFixed(3);

    document.getElementById("mass").innerHTML =
      data.mass.toFixed(1);

  });

}

setInterval(updateData, 500);

updateData();

</script>

</body>

</html>
)rawliteral";

  server.send(200, "text/html", webpage);
}


// =================================================
// SEND MEASUREMENT DATA
// =================================================

void handleData() {

  String json = "{";
  json += "\"mass\":";
  json += String(currentMass, 1);
  json += ",";
  json += "\"force\":";
  json += String(currentForce, 3);
  json += "}";

  server.send(200, "application/json", json);
}


// =================================================
// SETUP
// =================================================

void setup() {

  Serial.begin(115200);

  delay(1000);

  // Start HX711
  scale.begin(DT, SCK);

  Serial.println();
  Serial.println("================================");
  Serial.println("     FORCE MEASUREMENT SYSTEM");
  Serial.println("================================");

  delay(2000);

  // ---------------- TARE ----------------

  Serial.println();
  Serial.println("Remove all load.");
  Serial.println("Taking zero reading in 5 seconds...");

  delay(5000);

  zeroRaw = scale.read_average(20);

  Serial.print("ZERO RAW = ");
  Serial.println(zeroRaw);

  // ---------------- WIFI ----------------

  Serial.println();
  Serial.println("Starting Wi-Fi...");

  WiFi.softAP(ssid, password);

  Serial.println("Wi-Fi started!");
  Serial.print("Network name: ");
  Serial.println(ssid);

  Serial.print("Password: ");
  Serial.println(password);

  Serial.print("Webpage address: ");
  Serial.println(WiFi.softAPIP());

  // ---------------- WEB SERVER ----------------

  server.on("/", handleRoot);
  server.on("/data", handleData);

  server.begin();

  Serial.println("Web server started!");
  Serial.println();
  Serial.println("System ready.");
}


// =================================================
// LOOP
// =================================================

void loop() {

  // Handle webpage requests
  server.handleClient();

  // Read load cell
  if (scale.is_ready()) {

    long raw = scale.read_average(10);

    currentMass = (raw - zeroRaw) / COUNTS_PER_GRAM;

    // Remove small zero drift
    if (currentMass > -5 && currentMass < 5) {
      currentMass = 0;
    }

    // Convert grams to kg and calculate force
    currentForce = (currentMass / 1000.0) * 9.81;

    // Prevent tiny negative values
    if (currentMass < 0) {
      currentMass = 0;
      currentForce = 0;
    }

    // Serial Monitor
    Serial.print("Mass: ");
    Serial.print(currentMass, 1);

    Serial.print(" g | Force: ");
    Serial.print(currentForce, 3);

    Serial.println(" N");

  }

  delay(100);
}