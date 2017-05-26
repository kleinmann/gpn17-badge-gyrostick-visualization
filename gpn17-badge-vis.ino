#include <GPNBadge.hpp>
#include <FS.h>
#include <BadgeUI.h>
#include <UIThemes.h>

#include "rboot.h"
#include "rboot-api.h"

#include <gyrostick.h>

Badge badge;
Gyrostick gyrostick;

#define COLOR_WHITE 0xFFFF
#define COLOR_BLACK 0x0000

void setup() {
  badge.init();
  bno.begin();

  SPIFFS.begin();

  tft.fillScreen(COLOR_BLACK);
  tft.writeFramebuffer();
  badge.setBacklight(true);

  // TODO: Is this needed?
  badge.setGPIO(IR_EN, LOW);
  badge.setAnalogMUX(MUX_JOY);

  delay(300);
  badge.setGPIO(MQ3_EN, 1);

  rboot_config rboot_config = rboot_get_config();
  File f = SPIFFS.open("/rom" + String(rboot_config.current_rom), "w");
  f.println("GyroVis\n");
}

void loop() {
  tft.fillScreen(COLOR_BLACK);

  imu::Vector<2> coords = gyrostick.coords();

  tft.setCursor(2, 2);
  tft.println(coords.x());
  tft.setCursor(2, 20);
  tft.println(coords.y());

  tft.drawCircle(
    coords.x(),
    coords.y(),
    5.0, // scale
    COLOR_WHITE);

  tft.writeFramebuffer();

  pixels.show();
}
