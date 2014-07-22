#include <Adafruit_NeoPixel.h>

// Strip left and right are your left and right if you're standing at the foot of the table looking back at the sign

// Strip L (By the y in Anatomy) Pin 6
// Strip R (By the a in Anatomy) Pin 7

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel stripL = Adafruit_NeoPixel(60, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripR = Adafruit_NeoPixel(60, 7, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  stripL.begin();
  stripL.show(); // Initialize all pixels to 'off'

  stripR.begin();
  stripR.show(); // Initialize all pixels to 'off'
}

void loop() {
  rainbow(20);
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<45; i++) {
      stripL.setPixelColor(i, WheelL((i+j) & 255));
      stripR.setPixelColor(i, WheelR((i+j) & 255));
    }
    stripL.show();
    stripR.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t WheelL(byte WheelPos) {
  if(WheelPos < 85) {
   return stripL.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return stripL.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return stripL.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

uint32_t WheelR(byte WheelPos) {
  if(WheelPos < 85) {
   return stripR.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return stripR.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return stripR.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

