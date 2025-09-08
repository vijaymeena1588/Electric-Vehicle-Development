#include "U8glib.h"
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// OLED display setup
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE | U8G_I2C_OPT_DEV_0);

// GPS module setup
#define RX_PIN 2
#define TX_PIN 3
SoftwareSerial gpsSerial(RX_PIN, TX_PIN);
TinyGPSPlus gps;

// Timezone configuration (Adjust as per your region)
const int TIMEZONE_HOURS = 5;
const int TIMEZONE_MINUTES = 30;

// Display settings
const int x_max = 128;
const int y_max = 62;
const int x_center = x_max / 2;
const int y_center = y_max / 2 + 10;
const int arc = y_max / 2;

// Satellite logo dimensions
#define SAT_LOGO_WIDTH 20
#define SAT_LOGO_HEIGHT 20

// Satellite logo bitmap
const unsigned char sat_logo[] PROGMEM = {
  0x00, 0x01, 0x00, 0x80, 0x07, 0x00, 0xc0, 0x06, 0x00, 0x60, 0x30, 0x00,
  0x60, 0x78, 0x00, 0xc0, 0xfc, 0x00, 0x00, 0xfe, 0x01, 0x00, 0xff, 0x01,
  0x80, 0xff, 0x00, 0xc0, 0x7f, 0x06, 0xc0, 0x3f, 0x06, 0x80, 0x1f, 0x0c,
  0x80, 0x4f, 0x06, 0x19, 0xc6, 0x03, 0x1b, 0x80, 0x01, 0x73, 0x00, 0x00,
  0x66, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x70, 0x00, 0x00
};

// GPS data variables
double lat = 0.0, lng = 0.0;
String hours, minutes;
int second = 0, num_sat = 0, speed = 0;
String heading = "";
int needle_pos = 0;
u8g_uint_t xx = 0;

// -------------------------
// Gauge and Display Function
// -------------------------
void gauge(uint8_t angle) {
  u8g.setFont(u8g_font_chikita);

  // Draw gauge border
  u8g.drawCircle(x_center, y_center, arc + 6, U8G_DRAW_UPPER_RIGHT);
  u8g.drawCircle(x_center, y_center, arc + 4, U8G_DRAW_UPPER_RIGHT);
  u8g.drawCircle(x_center, y_center, arc + 6, U8G_DRAW_UPPER_LEFT);
  u8g.drawCircle(x_center, y_center, arc + 4, U8G_DRAW_UPPER_LEFT);

  // Speed labels
  u8g.drawStr(20, 42, "0");
  u8g.drawStr(18, 29, "25");
  u8g.drawStr(28, 14, "50");
  u8g.drawStr(60, 14, "100");
  u8g.drawStr(91, 14, "150");
  u8g.drawStr(101, 29, "175");
  u8g.drawStr(105, 42, "200");

  // Speed unit
  u8g.setPrintPos(54, 25);
  u8g.print("km/h");
  u8g.setPrintPos(50, 32);
  u8g.print("SPEED");

  // Draw needle
  float x1 = sin(2 * angle * 3.1416 / 180.0);
  float y1 = cos(2 * angle * 3.1416 / 180.0);
  u8g.drawLine(x_center, y_center, x_center + arc * x1, y_center - arc * y1);
  u8g.drawDisc(x_center, y_center, 5, U8G_DRAW_UPPER_LEFT);
  u8g.drawDisc(x_center, y_center, 5, U8G_DRAW_UPPER_RIGHT);

  // Satellite count
  u8g.drawXBM(0, 0, SAT_LOGO_WIDTH, SAT_LOGO_HEIGHT, sat_logo);
  u8g.setPrintPos(18, 5);
  u8g.print(num_sat);

  // Heading direction
  u8g.setPrintPos(110, 5);
  u8g.print(heading);

  // Latitude and Longitude
  u8g.setPrintPos(0, 55);
  u8g.print(lat, 4);
  u8g.setPrintPos(0, 62);
  u8g.print(lng, 4);

  // Time
  u8g.setFont(u8g_font_freedoomr10r);
  u8g.setPrintPos(90, 65);
  u8g.print(hours);
  u8g.drawStr(104, 65, (second % 2 == 0) ? ":" : " ");
  u8g.setPrintPos(111, 65);
  u8g.print(minutes);

  // Speed Value
  u8g.setFont(u8g_font_profont22);
  u8g.setPrintPos(54, 60);
  if (speed < 10) {
    u8g.print("0");
  }
  if (speed > 99) {
    u8g.setPrintPos(47, 60);
  }
  u8g.print(speed);
}

// -------------------------
// Setup
// -------------------------
void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  u8g.setFont(u8g_font_chikita);
  u8g.setColorIndex(1);
  Serial.println("GPS Speedometer System Ready");
}

// -------------------------
// Main Loop
// -------------------------
void loop() {
  Read_GPS();
  needle_pos = map(speed, 0, 200, 0, 90);
  xx = (needle_pos < 45) ? needle_pos + 135 : needle_pos - 45;

  u8g.firstPage();
  do {
    gauge(xx);
  } while (u8g.nextPage());
}

// -------------------------
// GPS Reading Functions
// -------------------------
void Read_GPS() {
  bool newData = false;
  for (unsigned long start = millis(); millis() - start < 1000;) {
    while (gpsSerial.available()) {
      if (gps.encode(gpsSerial.read())) {
        newData = true;
        break;
      }
    }
  }
  if (newData) {
    Get_GPS();
  }
}

void Get_GPS() {
  num_sat = gps.satellites.value();
  if (gps.location.isValid()) {
    speed = gps.speed.kmph();
    lat = gps.location.lat();
    lng = gps.location.lng();
    heading = gps.cardinal(gps.course.value());
  }
  if (gps.time.isValid()) {
    int hour = gps.time.hour();
    int minute = gps.time.minute();
    second = gps.time.second();
    adjustTime(hour, minute);
    hours = (hour < 10) ? "0" + String(hour) : String(hour);
    minutes = (minute < 10) ? "0" + String(minute) : String(minute);
  }
}

// -------------------------
// Adjust Timezone
// -------------------------
void adjustTime(int &hour, int &minute) {
  minute += TIMEZONE_MINUTES;
  hour += TIMEZONE_HOURS;
  if (minute >= 60) {
    minute -= 60;
    hour++;
  }
  if (hour >= 24) hour -= 24;
  if (hour < 0) hour += 24;
}
