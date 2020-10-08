#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define L_GREEN D7
#define L_RED D8

#define BUTTON D0

#define SW_1 D1
#define SW_2 D2
#define SW_3 D5
#define SW_4 D6

#define SSID "A1"
#define PASSWORD "PASS"
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

String current_environment() {
  String env = "";

  env.concat(digitalRead(SW_1));
  env.concat(digitalRead(SW_2));
  env.concat(digitalRead(SW_3));
  env.concat(digitalRead(SW_4));

  return env;
}

String payload() {
  String data = "{\"environment\":\"";
  data.concat(current_environment());
  data.concat("\"}");

  return data;
}

int deploy_request() {
  HTTPClient http;
  http.begin(SERVER);

  http.addHeader("Content-Type", "application/json");
  http.addHeader("API_KEY", API_KEY);
  int res = http.POST(payload());
  http.end();

  return res;
}

void setup() {
  pinMode(L_RED, OUTPUT);
  pinMode(L_GREEN, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(SW_1, INPUT_PULLUP);
  pinMode(SW_2, INPUT_PULLUP);
  pinMode(SW_3, INPUT_PULLUP);
  pinMode(SW_4, INPUT_PULLUP);

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    unconnected_warning();
  }
}

void loop() {
  if (digitalRead(BUTTON) == HIGH) {
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
