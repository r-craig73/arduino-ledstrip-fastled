#include <noise.h>
#include <bitswap.h>
#include <fastspi_types.h>
#include <pixelset.h>
#include <fastled_progmem.h>
#include <led_sysdefs.h>
#include <hsv2rgb.h>
#include <fastled_delay.h>
#include <colorpalettes.h>
#include <color.h>
#include <fastspi_ref.h>
#include <fastspi_bitbang.h>
#include <controller.h>
#include <fastled_config.h>
#include <colorutils.h>
#include <chipsets.h>
#include <pixeltypes.h>
#include <fastspi_dma.h>
#include <fastpin.h>
#include <fastspi_nop.h>
#include <platforms.h>
#include <lib8tion.h>
#include <cpp_compat.h>
#include <fastspi.h>
#include <FastLED.h>
#include <dmx.h>
#include <power_mgt.h>

#define NUM_STRIPS 2
#define NUM_SECTIONS_PER_STRIP 10
#define TOTAL_SECTIONS NUM_SECTIONS_PER_STRIP * NUM_STRIPS
CRGB leds[NUM_STRIPS * NUM_SECTIONS_PER_STRIP];

void setup() {
  // put your setup code here, to run once:
  // check delay
  delay(2000);
  // fixed RGB order
  FastLED.addLeds<TM1803, 8, GBR>(leds, 0, NUM_SECTIONS_PER_STRIP);
  FastLED.addLeds<TM1803, 13, GBR>(leds, NUM_SECTIONS_PER_STRIP, NUM_SECTIONS_PER_STRIP);
}

void loop() {
  // put your main code here, to run repeatedly:

  // alternate and display red & green for each LED section (3 LEDs for TM1803)
  for(int i = 0; i < TOTAL_SECTIONS; i++) {
    if (i % 2 == 0)
      leds[i] = CRGB(64, 0, 0);
    else
      leds[i] = CRGB(0, 64, 0);
    FastLED.show();
  }
  delay(2000);

  // one track color racing through the strip
  for(int i = 0; i < TOTAL_SECTIONS; i++) {
    leds[i] = CRGB(64, 0, 0); // or CRGB::Red
    FastLED.show();
    leds[i] = CRGB(0, 0, 0); // or CRGB::Black
    delay(200);
  }

  // display red across all strips
  for(int i = 0; i < TOTAL_SECTIONS; i++) {
    if (i < NUM_SECTIONS_PER_STRIP)
      leds[i] = CRGB(64, 0, 0);
    else
      leds[i] = CRGB(0, 64, 0);
    FastLED.show();
   }
  delay(2000);

  // display green across all strips
  for(int i = 0; i < TOTAL_SECTIONS; i++) {
    if (i < NUM_SECTIONS_PER_STRIP)
      leds[i] = CRGB(0, 64, 0);
    else
      leds[i] = CRGB(64, 0, 0);
    FastLED.show();
   }
  delay(2000);
}
