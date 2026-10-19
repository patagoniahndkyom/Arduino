// 測定に使用するピン（ADC1に対応するピンを推奨：32〜39など）
const int ADC_PIN = 4; 

void setup() {
  // シリアル通信の開始
  Serial.begin(115200);
  
  // ピンをアナログ入力に設定
  pinMode(ADC_PIN, ANALOG);
}

void loop() {
  // 1. 補正済みのミリボルト（mV）値を取得
  uint32_t volt_mv = analogReadMilliVolts(ADC_PIN);
  
  // 2. ボルト（V）単位に変換
  float volt_v = volt_mv / 1000.0;

  // 3. シリアルモニタに出力
  Serial.print("Voltage: ");
  Serial.print(volt_v, 3); // 小数点以下3桁まで表示
  Serial.println(" V");

  // 1秒待機
  delay(1000);
}