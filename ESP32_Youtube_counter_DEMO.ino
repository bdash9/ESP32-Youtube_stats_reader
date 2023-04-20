// Powered By Arduino classroom Youtube Channel
// Found https://github.com/arduinoclassroom/ESP32_Youtube_Subscribe_Counter

//Youtube api calls to check subscriber, view and video count.
/*
How to Get a YouTube API Key:
Log in to Google Developers Console.
Create a new project.
On the new project dashboard, click Explore & Enable APIs.
In the library, navigate to YouTube Data API v3 under YouTube APIs.
Enable the API.
Create a credential.
A screen will appear with the API key.
*/

#include <WiFi.h>

#include <WiFiClientSecure.h>

#include <YoutubeApi.h>

#include <ArduinoJson.h>

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

const char ssid[] = "xxxxxxx";
const char password[] = "xxxxxxxxxxxx";

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

#define API_KEY "xxxxxxxxxxxxxxxxxxxxxxxxxxx"
#define CHANNEL_ID "xxxxxxxxxxxxxxx"

WiFiClientSecure client;
YoutubeApi api(API_KEY, client);

unsigned long timeBetweenRequests = 60 * 1000;  // 60 seconds, in milliseconds

void setup() {
  Serial.begin(115200);
  delay(300);
  pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);
  tft.init(135, 240);
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);

  tft.setTextSize(2);
  tft.setTextColor (ST77XX_RED);
  tft.print ("DASH"); 
  tft.setTextColor (ST77XX_YELLOW);
  tft.print ("9");    
  tft.setTextColor (ST77XX_BLUE);
  tft.print ("COMPUTING");
  tft.setTextColor(ST77XX_WHITE);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.print("\nConnecting to WiFi: ");
  Serial.println(ssid);
  tft.print("\nConnecting to WiFi: ");
  tft.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    tft.print(".");    
    delay(500);
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  tft.println("\nWiFi connected!");
  tft.print("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  tft.println(ip);
  client.setInsecure();
  delay(1500);
  tft.fillScreen(ST77XX_BLACK);
}

void loop() {
  if (api.getChannelStatistics(CHANNEL_ID)) {
    tft.setCursor(0,0);
    tft.print("-D9C ");
    tft.setTextColor (ST77XX_RED);
    tft.print("YouTube ");
    tft.setTextColor(ST77XX_WHITE);
    tft.println("Stats-");
    tft.println("--------------------");
    tft.println();
    tft.print("Sub Count:   ");
    tft.println(api.channelStats.subscriberCount);

    tft.print("View Count:  ");
    tft.println(api.channelStats.viewCount);

    tft.print("Video Count: ");
    tft.println(api.channelStats.videoCount);
    
    Serial.println("\n---------Stats---------");

    Serial.print("Subscriber Count: ");
    Serial.println(api.channelStats.subscriberCount);

    Serial.print("View Count: ");
    Serial.println(api.channelStats.viewCount);

    Serial.print("Video Count: ");
    Serial.println(api.channelStats.videoCount);

    Serial.println("------------------------");
  }
  delay(timeBetweenRequests);
}
