#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define BUTTON D0

#define L_GREEN D7
#define L_RED D8

#define SSID "A1"
#define PASSWORD "SENAH"
#define SERVER "http://192.168.0.17:6666/api/v1/deploy"
#define API_KEY "{~c[3^n3u7R-j/By"

void unconnected_warning() {
  digitalWrite(L_GREEN, HIGH);
  digitalWrite(L_RED, HIGH);
  delay(500);
  digitalWrite(L_GREEN, LOW);
  digitalWrite(L_RED, LOW);
}

void success_warning() {
  digitalWrite(L_GREEN, HIGH);
  delay(5000);
  digitalWrite(L_GREEN, LOW);
}

void error_warning() {
  digitalWrite(L_RED, HIGH);
  delay(5000);
  digitalWrite(L_RED, LOW);
}

int deploy_request() {
  HTTPClient http;
  http.begin(SERVER);

  http.addHeader("Content-Type", "application/json");
  http.addHeader("API_KEY", API_KEY);
  int res = http.POST("{\"environment\":\"0000\"}");
  http.end();

  return res;
}

void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(L_RED, OUTPUT);
  pinMode(L_GREEN, OUTPUT);

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    unconnected_warning();
  }
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    if (WiFi.status() == WL_CONNECTED) {
      if (deploy_request() == 201) {
        success_warning();
      } else {
        error_warning();
      }
    }
    else {
      unconnected_warning();
    }
  }

  delay(1000);
}
