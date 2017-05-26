#include <GPNBadge.hpp>
#include <FS.h>
#include "colors.h"

#include "rboot.h"
#include "rboot-api.h"

#include <gyrostick.h>

Badge badge;
Gyrostick gyrostick;

void setup() {
  badge.init();
  bno.begin();

  SPIFFS.begin();

  tft.fillScreen(BLACK);
  tft.writeFramebuffer();
  badge.setBacklight(true);

  // TODO: Is this needed?
  badge.setGPIO(IR_EN, LOW);

  delay(300);

  rboot_config rboot_config = rboot_get_config();
  File f = SPIFFS.open("/rom" + String(rboot_config.current_rom), "w");
  f.println("GyroVis\n");
}

void loop() {
  tft.fillScreen(BLACK);

  imu::Vector<2> coords = gyrostick.coords();

  tft.drawCircle(
   coords.x(),
   coords.y(),
   5.0, // scale
   WHITE);

  tft.writeFramebuffer();

  pixels.show();
}
