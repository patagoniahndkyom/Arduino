const int adcPin = 34; // 測定に使用するGPIOピン (例: GPIO34)

void setup() {
  Serial.begin(115200);
}

void loop() {
  // キャリブレーション済みのミリボルト値を取得 (例: 1000 = 1.0V)
  uint32_t voltage_mV = analogReadMilliVolts(adcPin);
  
  float voltage_V = voltage_mV / 1000.0;

  Serial.print("Voltage: ");
  Serial.print(voltage_V);
  Serial.println(" V");

  delay(500);
}