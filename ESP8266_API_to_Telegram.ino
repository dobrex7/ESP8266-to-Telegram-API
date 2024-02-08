#include <ESP8266WiFi.h> //knjiznica za povezovanje na wifi esp8266
#include <WiFiClientSecure.h> //knjiznica za povezovanje na wifi esp8266
#include <UniversalTelegramBot.h> //knjiznica za telegram bota

const char* ssid = "ssid";// ssid oz. Ime wifija
const char* password = "password"; // geslo od wifija

#define BOTtoken "token" // Bottoken, ki smo ga dobili od botfather-ja
#define CHAT_ID "ID" // chatID, ki smo ga dobili od chatid bota

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
String dataIn = "Testno sporocilo na telegram"; //niz ki vsebuje besedilo

void setup()
{
  Serial.begin(115200); // inicializiramo serijsko komunikacijo na vrednosti 115200
  configTime(0, 0, "pool.ntp.org");      
  client.setTrustAnchors(&cert);
  // Povezava na wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  // izpis statusa, med povezavo na wifi oz. dokler se ne poveze na wifi
  int a = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    a++;
  }
  // Serijski izpisi v programu, ter izpisi za Bota v telegramu.
  Serial.println("");
  Serial.println("WiFi je povezan");
  Serial.print("IP naslov: ");
  Serial.println(WiFi.localIP()); 
  bot.sendMessage(CHAT_ID, "Wifi je povezan!", ""); // izpis v telegram
  bot.sendMessage(CHAT_ID, "Program je zagnan!", ""); // izpis v telegram
  
}

void loop() {
      Serial.println(dataIn); //serijski izpis
      bot.sendMessage(CHAT_ID, dataIn); //izpis v telegram

  delay(2000);
}

