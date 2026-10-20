#include <WiFi.h>
#include <WebServer.h>
#include <time.h>
// Wi-Fiの接続情報を入力
const char* ssid = "aterm-bdbab8-g";
const char* password = "57d744f87f264";
const int ANALOG_PIN32 = 32;
const int ANALOG_PIN33 = 33;
const int ANALOG_PIN34 = 34;
const int ANALOG_PIN35 = 35;
const int ANALOG_PIN36 = 36;
String html = "";

// NTP設定（日本標準時: JST-9）
const char* ntpServer = "ntp.nict.jp";
const long  gmtOffset_sec = 9 * 3600;
const int   daylightOffset_sec = 0;

// ポート80（通常のHTTPポート）でWEBサーバーのインスタンスを作成
WebServer server(80);

// ルートパス「/」にアクセスされた時に実行される関数
void handleRoot() {

struct tm timeinfo;
if (!getLocalTime(&timeinfo)) {
  server.send(500, "text/plain", "Failed to obtain time");
  return;
}
  char timeStringBuff[50];
  strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%d %H:%M:%S", &timeinfo);


  String html = "<!DOCTYPE html><html>";
  html += "<head><meta charset=\"UTF-8\"><title>ESP32 Web Server</title></head>";
  html += "<body>";
  html += "<h1>ESP32 Web Server</h1>";
  html += "<p>Current Time: " + String(timeStringBuff) + "</p>";
  html += "<h1>Hello from ESP32</h1>";
//  html += "</body></html>";
  
  // HTTPステータス200（成功）、コンテンツタイプ「text/html」でHTMLを送信

  int rawValue32 = analogRead(ANALOG_PIN32);
  int rawValue33 = analogRead(ANALOG_PIN33);
  int rawValue34 = analogRead(ANALOG_PIN34);
  int rawValue35 = analogRead(ANALOG_PIN35);
  int rawValue36 = analogRead(ANALOG_PIN36);

  // 2. ミリボルト単位の電圧を直接取得（校正値が適用されます）
  uint32_t volt_mV32 = analogReadMilliVolts(ANALOG_PIN32);
  uint32_t volt_mV33 = analogReadMilliVolts(ANALOG_PIN33);
  uint32_t volt_mV34 = analogReadMilliVolts(ANALOG_PIN34);
  uint32_t volt_mV35 = analogReadMilliVolts(ANALOG_PIN35);
  uint32_t volt_mV36 = analogReadMilliVolts(ANALOG_PIN36);
  
  // 3. ミリボルト（mV）をボルト（V）に変換
  float volt_V32 = volt_mV32 / 1000.0;
  float volt_V33 = volt_mV33 / 1000.0;
  float volt_V34 = volt_mV34 / 1000.0;
  float volt_V35 = volt_mV35 / 1000.0;
  float volt_V36 = volt_mV36 / 1000.0;

  html += "Voltage32:";  
  html += volt_mV32;  
  html += "mV<br>";
  html += "Voltage33:";  
  html += volt_mV33;  
  html += "mV<br>";
  html += "Voltage34:";  
  html += volt_mV34;  
  html += "mV<br>";
  html += "Voltage35:";  
  html += volt_mV35;  
  html += "mV<br>";
  html += "Voltage36:";  
  html += volt_mV36;  
  html += "mV<br>";

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

 // NTP時刻同期の初期化
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  
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
  int rawValue33 = analogRead(ANALOG_PIN33);
  int rawValue34 = analogRead(ANALOG_PIN34);
  int rawValue35 = analogRead(ANALOG_PIN35);
  int rawValue36 = analogRead(ANALOG_PIN36);  
  // 2. ミリボルト単位の電圧を直接取得（校正値が適用されます）
  uint32_t volt_mV32 = analogReadMilliVolts(ANALOG_PIN32);
  uint32_t volt_mV33 = analogReadMilliVolts(ANALOG_PIN33);
  uint32_t volt_mV34 = analogReadMilliVolts(ANALOG_PIN34);
  uint32_t volt_mV35 = analogReadMilliVolts(ANALOG_PIN35);
  uint32_t volt_mV36 = analogReadMilliVolts(ANALOG_PIN36);  
  // 3. ミリボルト（mV）をボルト（V）に変換
  float volt_V32 = volt_mV32 / 1000.0;
  float volt_V33 = volt_mV33 / 1000.0;
  float volt_V34 = volt_mV34 / 1000.0;
  float volt_V35 = volt_mV35 / 1000.0;
  float volt_V36 = volt_mV36 / 1000.0;
  // シリアルモニタへの出力
  Serial.print("Raw ADC32: ");
  Serial.print(rawValue32);
  Serial.print(" | Voltage32: ");
  Serial.print(volt_mV32);
  Serial.println(" mV ");
  Serial.print("Raw ADC33: ");
  Serial.print(rawValue33);
  Serial.print(" | Voltage33: ");
  Serial.print(volt_mV33);
  Serial.println(" mV ");
  Serial.print("Raw ADC34: ");
  Serial.print(rawValue34);
  Serial.print(" | Voltage34: ");
  Serial.print(volt_mV34);
  Serial.println(" mV ");
  Serial.print("Raw ADC35: ");
  Serial.print(rawValue35);
  Serial.print(" | Voltage35: ");
  Serial.print(volt_mV35);
  Serial.println(" mV ");
  Serial.print("Raw ADC36: ");
  Serial.print(rawValue36);
  Serial.print(" | Voltage36: ");
  Serial.print(volt_mV36);
  Serial.println(" mV ");
  delay(500); // 0.5秒ごとに測定

  delay(2); // ウォッチドッグタイマー(WDT)リセット対策用の短いディレイ


}
