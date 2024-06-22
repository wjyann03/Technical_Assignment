#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "TOKO MBAK KUM";
const char* password = "sekawan007";
const char* serverName = "http://192.168.1.3:5000/sensor/data";

const int touchPin = 2;  // Pin sensor sentuh terhubung ke GPIO 4 pada ESP32

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  pinMode(touchPin, INPUT);
}

void loop() {
  int touchValue = touchRead(touchPin);  // Menggunakan touchRead untuk sensor sentuh

  if (touchValue < 20) {  // Sesuaikan threshold sesuai dengan sensor Anda
    // Sensor sentuh terdeteksi sentuhan
    postData();
    delay(1000);  // Hindari pengiriman berulang dalam waktu singkat
  }
}

void postData() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String httpRequestData = "touch=detected";
    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }
}
