#include <ESP8266WiFi.h>
#include <DHT.h>

// Define the DHT11 sensor pin and type
#define DHTPIN D1 // GPIO pin where DHT11 is connected, for this example is D1
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

// WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";      // Replace with your WiFi SSID
const char* password = "YOUR_WIFI_PASSWORD"; // Replace with your WiFi password

// Server settings
const char* server = "YOUR_SERVER_IP"; // IP address of the Python server
const int serverPort = "YOUR_SERVER_PORT";          // Port number for server

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to WiFi
  Serial.println();
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  
  Serial.println("Connected to WiFi!");
}

void loop() {
  delay(2000); // Wait between readings, for this example, 2 secs

  // Read temperature and humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any readings failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Send data to server
  sendToServer(temperature, humidity);
}

void sendToServer(float temp, float hum) {
  WiFiClient client;
  if (!client.connect(server, serverPort)) {
    Serial.println("Connection to server failed");
    return;
  }

  // Create data string
  String postData = "temperature=" + String(temp) + "&humidity=" + String(hum);
  // JSON example below
  // String postData = "{\"temperature\": " + String(temperature) + ", \"humidity\": " + String(humidity) + "}";

  // Send HTTP POST request to the Python server
  client.println("POST /data HTTP/1.1");
  client.println("Host: " + String(server));
  client.println("Content-Type: application/x-www-form-urlencoded");
  // If you want JSON data, comment above and uncomment below
  // client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(postData.length());
  client.println();
  client.print(postData);

  // Wait for the server's response
  while (client.connected() || client.available()) {
    if (client.available()) {
      String line = client.readStringUntil('\n');
      Serial.println(line);
    }
  }

  client.stop();
}
