#include <GPNBadge.hpp>
#include <FS.h>
#include <BadgeUI.h>
#include <UIThemes.h>
#include <math.h>

#include "rboot.h"
#include "rboot-api.h"

#include "sensor.h"

Badge badge;

imu::Vector<3> data;

#define COLOR_WHITE 0xFFFF
#define COLOR_BLACK 0x0000

void setup() {
  badge.init();

  SPIFFS.begin();

  badge.setBacklight(true);
  
  // TODO: Is this needed?
  badge.setGPIO(IR_EN, LOW);
  badge.setAnalogMUX(MUX_JOY);

  bno.begin();
  delay(300);
  badge.setGPIO(MQ3_EN,1);

  rboot_config rboot_config = rboot_get_config();
  File f = SPIFFS.open("/rom" + String(rboot_config.current_rom), "w");
  f.println("GyroVis\n");

  tft.fillScreen(COLOR_BLACK);
  tft.writeFramebuffer();
}

void loop() {
  tft.fillScreen(COLOR_BLACK);
  
  data = euler();

  double x = getUsableX(data.x());
  double y = data.y() + 180.0;
  double z = data.z() + 90.0; // holding device in front of you means "centered"

  tft.setCursor(10, 60);
  tft.println(x);
  tft.setCursor(10, 80);
  tft.println(y);
  tft.setCursor(10, 100);
  tft.println(z);

  tft.drawCircle(
    (y / 360.0) * 128.0, // x-coord
    (z / 360.0) * 128.0, // y-coord
    5.0, //(x / 360.0) * 32.0, // scale
    COLOR_WHITE);

  tft.writeFramebuffer();
  
  pixels.show();
}

double getUsableX(double x) {
  if(x >= 180.0) {
    // x geht nach rechts
    // x geht von 360 nach 180 (negativ)
    // 360 = 1, 359 = 2, 358 = 3)
    x = (x - 360) * (-1);
  } else { // x < 180.0)
    // x geht nach links
    // x geht von 0 nach 180 (positiv)
    x = x * (-1);
  }

  x = x + 180.0;

  return x;
}

