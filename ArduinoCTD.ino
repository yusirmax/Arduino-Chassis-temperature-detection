/*
 * GITHUB: yusirmax
 * 链接: https://github.com/yusirmax/Arduino-Chassis-temperature-detection
 * DHT11传感器数据脚D6
 */
#define BLINKER_PRINT Serial
#define BLINKER_WIFI
#define BLINKER_MIOT_OUTLET
#include <SoftwareSerial.h>
#include "DHTesp.h"
#include <U8g2lib.h>
#include <Blinker.h>
DHTesp dht;
float humidity, temperature; //GET DHT11 DATA
char auth[] = "your blinker key";
char ssid[] = "wifi name";
char pswd[] = "wifi passwd";
BlinkerNumber Numtem("num-tem");  //Blinker上自定义显示数据的气温温度模块
BlinkerNumber Numhum("num-hum");  //Blinker上自定义显示数据的气温湿度模块
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);//定义屏幕
#define fu_x 128
#define fu_y 64
static const unsigned char fu[] U8X8_PROGMEM = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x99, 0xF9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x99, 0xF9, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0xE0, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x00, 0xF8, 0xFF, 0xFF, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x00, 0xF8, 0xFF, 0x7F, 0x00, 0xFE, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0xFE, 0xFF, 0x01, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0xFE, 0xFF, 0x01, 0x80, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0xF0, 0xFF, 0x07, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0xF0, 0xFF, 0x07, 0x00, 0xF8, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0xF8, 0x7F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0xFC, 0x7F, 0x00, 0x80, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x80, 0xFF, 0x07, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x80, 0xFF, 0x07, 0x00, 0xF8, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0xE0, 0x7F, 0x00, 0xE0, 0xFF, 0xF1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0xE0, 0x7F, 0x00, 0xE0, 0xFF, 0xE1, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0xFE, 0x1F, 0x00, 0xFE, 0x1F, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x00, 0xFF, 0x1F, 0x00, 0xFE, 0x1F, 0xF8, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x80, 0xFF, 0x01, 0xE0, 0xFF, 0x01, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xC0, 0xFF, 0x01, 0xE0, 0xFF, 0x01, 0xF8, 0xFF, 0xFF,
  0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xF8, 0x7F, 0x00, 0xFE, 0x07, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0x03, 0xFC, 0x7F, 0x00, 0xFF, 0x07, 0x00, 0xFE, 0xFF, 0xFF,
  0xFF, 0xFF, 0xF1, 0x7F, 0xFF, 0xFF, 0x01, 0xFE, 0x07, 0xE0, 0x7F, 0x60, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x3F, 0xFE, 0xFF, 0x00, 0xFE, 0x03, 0xF0, 0x7F, 0x60, 0x00, 0xFE, 0xFF, 0xFF,
  0xFF, 0xFF, 0xC0, 0x3F, 0xF0, 0x7F, 0x80, 0xFF, 0x01, 0xFE, 0xC7, 0x7F, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC1, 0x3F, 0xE0, 0x3F, 0xC0, 0xFF, 0x01, 0xFF, 0x87, 0x7F, 0x80, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0x03, 0xFF, 0x00, 0x1C, 0xE0, 0x1F, 0xE0, 0x7F, 0xFF, 0x1F, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xFE, 0x00, 0x08, 0xF0, 0x1F, 0xF0, 0x7F, 0xFE, 0x1F, 0x80, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0x0F, 0xFC, 0x03, 0x00, 0xFF, 0x07, 0xF8, 0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xFC, 0x03, 0x00, 0xFF, 0x03, 0xFC, 0xFF, 0xFF, 0x1F, 0xE0, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0x3F, 0xF0, 0x03, 0x80, 0x7F, 0x80, 0xFF, 0xFF, 0xFF, 0x07, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xF0, 0x03, 0xC0, 0x3F, 0xC0, 0xFF, 0xFF, 0xFF, 0x03, 0xF8, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xDF, 0x0F, 0xF0, 0x1F, 0xF8, 0xFF, 0xFF, 0xFF, 0x01, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCF, 0x0F, 0xF0, 0x0F, 0xFC, 0xFF, 0xFF, 0xFF, 0x00, 0xF8, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0xFC, 0x01, 0xFE, 0xFF, 0xFF, 0x7F, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0xFC, 0x00, 0xFE, 0xFF, 0xFF, 0x3F, 0x00, 0xFE, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xFC, 0x03, 0xFC, 0xFF, 0xFF, 0x3F, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F, 0xFC, 0x03, 0xFC, 0xFF, 0xFF, 0x3F, 0x80, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x3F, 0x00, 0xFC, 0xFF, 0x07, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x3F, 0x00, 0xFC, 0xFF, 0x03, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCF, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCF, 0x8C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xCF, 0xCD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  /* (128 X 64 )*/
};

void heartbeat() //心跳包回调函数
{
  BlinkerText Tex1("tex-1");
  Tex1.print("WORKING...");
  Numtem.print(temperature);
  Numhum.print(humidity);
}

void dataRead(const String & data)
{
  BLINKER_LOG("Blinker readString: ", data);
  Blinker.vibrate();
  uint32_t BlinkerTime = millis();
  Blinker.print("millis", BlinkerTime);
}

void dataStorage()
{
  Blinker.dataStorage("cha-temp", temperature);
  Blinker.dataStorage("cha-humi", humidity);
}

void oledDisplay()
{
  u8g2.firstPage();
  do
  {
    float h = dht.getHumidity();
    float t = dht.getTemperature();
    humidity = h;
    temperature = t;
    u8g2.setFont(u8g2_font_unifont_t_chinese1);
    u8g2.setCursor(0, 30);
    u8g2.print("空气温度"); //输出空气温度
    u8g2.setCursor(0, 45);
    u8g2.print("空气湿度"); //输出空气湿度
    u8g2.setFont(u8g2_font_helvR10_tf);
    u8g2.setCursor(62, 30);
    u8g2.print(": " + String(t) + "C"); //输出空气温度
    u8g2.setCursor(62, 45);
    u8g2.print(": " + String(h) + "%"); //输出空气湿度
  } while (u8g2.nextPage());
}


void oledKaiji()
{
  u8g2.clearBuffer();//清除屏幕缓冲区
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.drawXBMP(0, 0, fu_x, fu_y, fu);
  u8g2.sendBuffer();//发送到屏幕缓冲区
  delay(2000);
  u8g2.clearBuffer();
}

void u8g2Init()
{
  u8g2.begin();
  u8g2.setFlipMode(0);
  u8g2.clearBuffer();
  u8g2.enableUTF8Print();
}

void setup()
{
  Serial.begin(115200); //初始化串口
  BLINKER_DEBUG.stream(BLINKER_PRINT);
  Blinker.attachData(dataRead);
  Blinker.attachDataStorage(dataStorage);//附加数据存储
  dht.setup(12, DHTesp::DHT11);//DHT11传感器 D6
  Blinker.begin(auth, ssid, pswd); //联网初始化
  Blinker.attachHeartbeat(heartbeat); //心跳包初始化
  u8g2Init(); //init OLED
  oledKaiji();
}

void loop()
{
  Blinker.run();//Blinker运行
  float t = dht.getTemperature();
  float h = dht.getHumidity();
  oledDisplay();//Display
}
