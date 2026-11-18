#include <KiwisIoT.h>

const int phPin = A0;

// Replace these example values after calibration.
const float voltageAtPH7 = 2.50;
const float voltageChangePerPH = 0.18;

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* topicId = "YOUR_TOPIC_ID";

void setup() {
  Serial.begin(115200);

  kiwisiot.begin(ssid, password, topicId);

  Serial.println("IoT Water pH Monitoring Started");
}

void loop() {
  kiwisiot.run();

  int rawValue = analogRead(phPin);
  float voltage = rawValue * (3.3 / 1023.0);

  // Example linear conversion only.
  // Confirm the voltage scaling and calibration for your hardware.
  float pH = 7.0 +
             (voltageAtPH7 - voltage) / voltageChangePerPH;

  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V | Estimated pH: ");
  Serial.println(pH, 2);

  kiwisiot.send("1", pH);

  delay(2000);
}