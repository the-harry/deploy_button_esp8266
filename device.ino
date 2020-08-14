#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define BUTTON D0

#define SSID "WIFI"
#define PASSWORD "PASS"
#define SERVER "http://192.168.0.17:6666/api/v1/deploy"
#define API_KEY "{~c[3^n3u7R-j/By"

void setup() {
  pinMode(BUTTON, INPUT);

  Serial.begin(9600);
  WiFi.begin(SSID, PASSWORD);

  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("disconnected");
    delay(500);
  }

  Serial.print("ip: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(SERVER);

      http.addHeader("Content-Type", "application/json");
      http.addHeader("API_KEY", API_KEY);
      int response = http.POST("{\"environment\":\"staging\"}");

      if (response == 201) {
        Serial.println("scheduled");
      } else {
        Serial.println("error");
      }

      http.end();
    }
    else {
      Serial.println("disconnected");
    }
  }

  delay(1000);
}
