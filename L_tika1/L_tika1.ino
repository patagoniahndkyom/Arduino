const int LED_PIN = 19; // 多くのESP32ボードでは2番ピンが内蔵LEDです

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH); // LEDを点灯
  delay(500);                 // 1秒待つ
  digitalWrite(LED_PIN, LOW);  // LEDを消灯
  delay(500);                 // 1秒待つ
}