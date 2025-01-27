#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h> // For ESP8266

// WiFi credentials
const char* ssid = "Vodafone-6251";         // Replace with your WiFi SSID
const char* password = "TepUauaumhrHHt7J"; // Replace with your WiFi Password

// Define the pin for the IR sensor
#define IR_SENSOR_PIN 12  // GPIO12 (D6) for the IR sensor input (use correct pin for your board)

// Create a web server instance on port 80
ESP8266WebServer server(80);

// HTML Code for the interface
const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<style>
.container {
  width: 300px;
  height: 300px;
}
.door {
  width: 150px;
  height: 300px;
  position: relative;
  transform-origin: left center;
  margin-left: 600px;
  margin-top: 150px;
  background-image: url('door_left.jpeg'); 
  background-size: cover;
}
.btn {
  margin-left: 650px;
}
</style>
</head>
<body>
<div class="container">
  <div class="door"></div>
</div>
<button class="btn" onclick="toggleDoor()">Toggle Door</button>
<script>
function toggleDoor() {
  fetch('/toggleDoor') // Send a request to the server to toggle the door
    .then(response => response.json())
    .then(data => {
      const door = document.querySelector('.door');
      if (data.state === 'open') {
        door.style.backgroundImage = "url('door_right.jpeg')"; // Door open image
      } else {
        door.style.backgroundImage = "url('door_left.jpeg')"; // Door closed image
      }
    });
}
</script>
</body>
</html>
)rawliteral";

// Variable to store the door state
bool isDoorOpen = false;

// Function to handle the root URL and serve the HTML page
void handleRoot() {
  server.send(200, "text/html", htmlPage); // Correct HTTP status code is 200
}

// Function to handle door toggle requests
void handleToggleDoor() {
  isDoorOpen = !isDoorOpen; // Toggle the door state

  // Respond with the current state
  String jsonResponse = "{\"state\":\"";
  jsonResponse += isDoorOpen ? "open" : "closed";
  jsonResponse += "\"}";
  server.send(200, "application/json", jsonResponse); // Correct HTTP status code is 200
}

// Function to handle IR sensor readings
void handleSensor() {
  int sensorValue = digitalRead(IR_SENSOR_PIN);
  String jsonResponse = "{\"sensor\":\"";
  jsonResponse += sensorValue == LOW ? "triggered" : "clear";
  jsonResponse += "\"}";
  server.send(200, "application/json", jsonResponse); // Correct HTTP status code is 200
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  delay(1000);

  // Configure pin modes
  pinMode(IR_SENSOR_PIN, INPUT); // Set the IR sensor pin as input

  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  // Print WiFi connection status
  Serial.println("\nWiFi connected!");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Display the local IP address

  // Configure web server routes
  server.on("/", handleRoot);          // Serve the HTML page
  server.on("/toggleDoor", handleToggleDoor); // Handle door toggle requests
  server.on("/sensor", handleSensor); // API for IR sensor status

  // Start the web server
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  // Handle client requests
  server.handleClient();

  // Optional: Log IR sensor status to Serial Monitor
  int sensorValue = digitalRead(IR_SENSOR_PIN);
  if (sensorValue == LOW) {
    Serial.println("Object detected!");
  } else {
    Serial.println("No object detected.");
  }
  delay(1000); // Adjust delay as needed
}
