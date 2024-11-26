#include <Arduino.h>
#include <DHT.h>
#include <WiFi.h>
// Define Blynk credentials
#define BLYNK_TEMPLATE_ID "TMPL2WxEV6fZ6"
#define BLYNK_TEMPLATE_NAME "IoT Home System"
#define BLYNK_AUTH_TOKEN "q_BNFuiAHLMPa1Wrvvgds0vsumBgxcjN"
#include <BlynkSimpleEsp32.h>


// Pins and Sensor Configuration
#define DHTPIN 15
#define DHTTYPE DHT22
#define PIR_PIN 27
#define LDR_PIN 34
#define LED1_PIN 16
#define LED2_PIN 17
#define HEATER_PIN 4
#define BUZZER_PIN 26

DHT dht(DHTPIN, DHTTYPE);

// Blynk Auth Token (Get this from the Blynk app)
char auth[] =BLYNK_AUTH_TOKEN ;

// WiFi credentials
const char* ssid = "Wokwi-GUEST";
const char* password = "";
int desiredTemp = 24; // Default humidity level
bool is_alarm_on = false;


void setup() {
  // Initialize serial communication and sensors
  Serial.begin(115200);
  dht.begin();
  pinMode(PIR_PIN, INPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
pinMode(HEATER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Connect to Wi-Fi and Blynk
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  Blynk.begin(auth, ssid, password);
}
void triggerAlarm() {
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED2_PIN, HIGH);
  Serial.println("Alarm triggered !!!!!");
  is_alarm_on=true;
  // delay(500);
  // digitalWrite(BUZZER_PIN, LOW);
}
void checkBlynkConnection() {
  if (!Blynk.connected()) {
    Serial.println("Blynk disconnected. Reconnecting...");
    Blynk.connect();
  }
}
BLYNK_WRITE(V4) {
  desiredTemp = param.asInt(); // Read the slider value
  Serial.print("Desired desiredTemp Set to: ");
  Serial.println(desiredTemp);
}
BLYNK_WRITE(V3) {
  is_alarm_on = param.asInt(); // Read the switch value
  if (is_alarm_on) {
    Serial.println("Manual Alarm Activated!");
    triggerAlarm();
  } else {
    Serial.println("Manual Alarm Deactivated!");
    digitalWrite(BUZZER_PIN, LOW); // Ensure the buzzer is off
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
  }
}

void loop() {
  // Run Blynk
  if (Blynk.connected()) {
    Blynk.run();
    Serial.println("Blynk Connected ...");
  }
  checkBlynkConnection();


  // Read sensors
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int motionDetected = digitalRead(PIR_PIN);
  int lightLevel = analogRead(LDR_PIN);

  // Check and control based on the slider value
  if (temperature < desiredTemp) {
    Serial.println("temperature too low! Activating humidifier...");
    digitalWrite(HEATER_PIN, HIGH); // Example: turn on LED1
  } else {
    Serial.println("temperature is at desired level.");
    digitalWrite(HEATER_PIN, LOW); // Example: turn off LED1
  }
  if (is_alarm_on) {
    triggerAlarm();
  } 
  // Send data to Blynk virtual pins
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, lightLevel);
  Blynk.virtualWrite(V3, is_alarm_on);

  // Print temperature and humidity
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Light Level: ");
  Serial.println(lightLevel);

  // Motion and light logic
  if (motionDetected && lightLevel < 500) { // Adjust threshold as needed
    Serial.println("Motion detected!");
    triggerAlarm();
  }

  delay(2000); // Adjust delay as needed
}
