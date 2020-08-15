#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define BUTTON D0

#define L_RED D1
#define L_YELLOW D2
#define L_GREEN D8

#define SSID "WIFI"
#define PASSWORD "PASS"
#define SERVER "http://192.168.0.17:6666/api/v1/deploy"
#define API_KEY "{~c[3^n3u7R-j/By"

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(L_RED, OUTPUT);
  pinMode(L_YELLOW, OUTPUT);
  pinMode(L_GREEN, OUTPUT);

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(L_YELLOW, HIGH);
    delay(500);
  }

  digitalWrite(L_YELLOW, LOW);
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
        digitalWrite(L_GREEN, HIGH);
        delay(5000);
        digitalWrite(L_GREEN, LOW);
      } else {
        digitalWrite(L_RED, HIGH);
        delay(5000);
        digitalWrite(L_RED, LOW);
      }

      http.end();
    }
    else {
      digitalWrite(L_YELLOW, HIGH);
      delay(2000);
      digitalWrite(L_YELLOW, LOW);
    }
  }

  delay(1000);
}
