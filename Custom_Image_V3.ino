
#include "rm67162.h"
#include <TFT_eSPI.h>   //https://github.com/Bodmer/TFT_eSPI
#include "gImage_true_color_1_16bit.h" // <== my sample png (536 x 240 px), replace with your own 
#include "gImage_true_color_2_16bit.h" // <== my sample png (536 x 240 px), replace with your own 

#if ARDUINO_USB_CDC_ON_BOOT != 1
#warning "If you need to monitor printed data, be sure to set USB CDC On boot to ENABLE, otherwise you will not see any data in the serial monitor"
#endif

#ifndef BOARD_HAS_PSRAM
#error "Detected that PSRAM is not turned on. Please set PSRAM to OPI PSRAM in ArduinoIDE"
#endif

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

#define WIDTH  536
#define HEIGHT 240

const uint16_t* images[] = {gImage_true_color_1, gImage_true_color_2, /* add more images here if memory allows*/};

void displayImage(const uint16_t *image) {
    spr.pushImage(0, 0, WIDTH, HEIGHT, image);
    lcd_PushColors(0, 0, WIDTH, HEIGHT, (uint16_t *)spr.getPointer());
    delay(2000); // 2 seconds before switching
}

void setup()
{
    Serial.begin(9600);
    delay(500);  // Allow time for Serial to initialize

    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, HIGH);

    rm67162_init();
    lcd_setRotation(1);
    spr.createSprite(WIDTH, HEIGHT);
    spr.setSwapBytes(1);
}

void loop() {

  for (int i = 0; i < sizeof(images) / sizeof(images[0]); i++) {
    displayImage(images[i]);
  }

}
