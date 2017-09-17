/*

   NeoPixels demo - rainbow colours

*/

#include <SPI.h>
#include <NeoPixels_SPI.h>

const unsigned int PIXELS = 300; // Number of pixels in the string

void setup()
{
  ledsetup();
  showColor (PIXELS, 0, 0, 0);  // all to black
} // end of setup

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
void Wheel (byte WheelPos, byte & r, byte & g, byte & b)
{
  if (WheelPos < 85)
  {
    r = WheelPos * 3;
    g = 255 - WheelPos * 3;
    b = 0;
  }
  else if (WheelPos < 170)
  {
    WheelPos -= 85;
    r = 255 - WheelPos * 3;
    g = 0;
    b = WheelPos * 3;
  }
  else
  {
    WheelPos -= 170;
    r = 0;
    g = WheelPos * 3;
    b = 255 - WheelPos * 3;
  }
} // end of Wheel

typedef struct colour
{
  byte r;
  byte g;
  byte b;
};  // end of struct colour

// store the rainbox in memory
// WARNING! 3 bytes per pixel - take care you don't exceed available RAM
colour pixelArray [PIXELS];

void rainbow (const byte wait)
{
  unsigned int i, j;

  // cycle the starting point
  for (j = 0; j < 256; j++)
  {
    // build into in-memory array, as these calculations take too long to do on the fly
    for (i = 0; i < PIXELS; i++)
    {
      byte r, g, b;
      Wheel ((i + j) & 255, r, g, b);
      pixelArray [i].r = r;
      pixelArray [i].g = g;
      pixelArray [i].b = b;
    }
    // now show results
    noInterrupts ();
    for (i = 0; i < PIXELS; i++)
      sendPixel (pixelArray [i].r, pixelArray [i].g, pixelArray [i].b);
    interrupts ();
    show();
    delay(wait);
  }   // end of for each cycle
} // end of rainbox

void loop()
{
  rainbow(10);
} // end of loop