#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include <limits.h>

#define PIN 13

// This is 0.618033988749895 * (2**16)
#define GOLDEN_RATIO_CONJUGATE 40503

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

uint16_t colorNumber = random(1, USHRT_MAX);

uint16_t getRandomHue()
{

    // https://martin.ankerl.com/2009/12/09/how-to-create-random-colors-programmatically/

    uint32_t tempColor = colorNumber + GOLDEN_RATIO_CONJUGATE;
    colorNumber = tempColor %= USHRT_MAX;
    return colorNumber;
}

void setup()
{

    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop()
{


    

    uint16_t hue = getRandomHue();
    for (int pixel = 0; pixel < 12; pixel++)
    {
        
        for (int i = 0; i <= 50; i++)
        {
            for (int j = 0; j < pixel; j++)
            {
                strip.setPixelColor(j, strip.ColorHSV(hue, 242, 50));
            }

            strip.setPixelColor(pixel, strip.ColorHSV(hue, 242, i));
            strip.show();

            delay(60000 / 12 / 50);
        }

        if (pixel == 11)
        {
            strip.clear();
            hue = getRandomHue();
        }
    }
}