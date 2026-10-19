#include <WiFi.h>
#include <WebServer.h>

// Wi-Fiの接続情報を入力
const char* ssid = "aterm-bdbab8-g";
const char* password = "57d744f87f264";
const int ANALOG_PIN32 = 32; // 測定に使用するGPIOピン（例: GPIO1）
String html = "";
// ポート80（通常のHTTPポート）でWEBサーバーのインスタンスを作成
WebServer server(80);

// ルートパス「/」にアクセスされた時に実行される関数
void handleRoot() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta charset=\"UTF-8\"><title>ESP32 Web Server</title></head>";
  html += "<body>";
  html += "<h1>Hello from ESP32</h1>";
//  html += "</body></html>";
  
  // HTTPステータス200（成功）、コンテンツタイプ「text/html」でHTMLを送信

  int rawValue32 = analogRead(ANALOG_PIN32);
  
  // 2. ミリボルト単位の電圧を直接取得（校正値が適用されます）
  uint32_t volt_mV32 = analogReadMilliVolts(ANALOG_PIN32);
  
  // 3. ミリボルト（mV）をボルト（V）に変換
  float volt_V32 = volt_mV32 / 1000.0;


//  html += "<head><meta charset=\"UTF-8\"><title>Web Server</title></head>";
//  html += "<body>";
//  html += "<h1>Hello from ESP32-S3!</h1>";
  html += "Voltage32:";  
  html += volt_mV32;  
  html += "mV";
  //  html += "</body></html>";
  
  delay(500); 


  server.send(200, "text/html", html);
}

// 登録されていないパスにアクセスされた時に実行される関数
void handleNotFound() {
  server.send(404, "text/plain", "404 Not Found");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Wi-Fiに接続
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // 接続完了を待つ
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // 接続されたらIPアドレスをシリアルモニターに表示
  Serial.println("");
  Serial.println("Wi-Fi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // ルーティングの設定（特定のURLパスと処理する関数を紐付け）
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  // サーバーの起動
  server.begin();
  Serial.println("HTTP server started");

  // ESP32-S3のデフォルト解像度は13bit（0?8191）ですが、
  // 明示的に12bit（0?4095）に固定しておくと他機種との互換性が上がります。
  analogReadResolution(12); 
  
  // 3.3Vまでの電圧を測定できるようにアッテネータ（減衰器）を11dB（または12dB）に設定
  analogSetAttenuation(ADC_11db); 








}

void loop() {
  // クライアントからの要求（HTTPリクエスト）を常に監視・処理する
  server.handleClient();
 
  int rawValue32 = analogRead(ANALOG_PIN32);
  
  // 2. ミリボルト単位の電圧を直接取得（校正値が適用されます）
  uint32_t volt_mV32 = analogReadMilliVolts(ANALOG_PIN32);
  
  // 3. ミリボルト（mV）をボルト（V）に変換
  float volt_V32 = volt_mV32 / 1000.0;

  // シリアルモニタへの出力
  Serial.print("Raw ADC32: ");
  Serial.print(rawValue32);
  Serial.print(" | Voltage32: ");
  Serial.print(volt_mV32);
  Serial.print(" mV32 (");
  Serial.print(volt_V32, 3);
  Serial.println(" V)");

  delay(500); // 0.5秒ごとに測定

  delay(2); // ウォッチドッグタイマー(WDT)リセット対策用の短いディレイ


}
