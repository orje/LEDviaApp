/*
 *
 * NeoPixel display library.
 *
 * Author: Nick Gammon
 * Date:   2nd March 2016
 *
 * With ideas from: http://wp.josh.com/2014/05/13/ws2812-neopixels-are-not-so-finicky-once-you-get-to-know-them/
 *
 * Designed for 16 MHz processor.
 *
 * Released for public use under the Creative Commons Attribution 3.0 Australia License
 *      http://creativecommons.org/licenses/by/3.0/au/
 *
 * In other words, if you use this code, please give me the credit for writing the library.
 *
 * Time taken to display: About 63 µs per pixel (21 µs per byte, about 2.6 µs per bit).
 * This is 63 ms to display 1000 pixels, roughly 16 refreshes per second (16 FPS)
 *   Of course, with less pixels the frame rate will go up.
 *
  HOW TO USE
    ledsetup ();         - Get ready to send.
                           Call once at the beginning of the program.
    sendPixel (r, g, b); - Send a single pixel to the string.
                           Call this once for each pixel in a frame.
                           Each colour is in the range 0 to 255.
    show ();             - Latch the recently sent pixels onto the LEDs .
                           Call once per frame.
    showColor (count, r, g, b); - Set the entire string of count Neopixels to this one colour.
                                  This automatically turns interrupts off, so you don't need to do it.
    Note that if you are sending individual pixels (with sendPixel) you should first call
    noInterrupts(), send all the pixels you need, and then call interrupts(). Otherwise a timer or
    other interrupt may pause the sending long enough for the string to reset.
    For example:
    noInterrupts ();          // prevent interrupts while we are sending colours
    for (byte i = 0; i < 10; i++)
      {
      sendPixel (100, 0, 0);    // red
      sendPixel (0, 100, 0);    // green
      sendPixel (0, 0, 100);    // blue
      } // end of for loop
    interrupts ();            // interrupts are OK now
    show ();                  // latch the colours
 */

#include <SPI.h>
#include <NeoPixels_SPI.h>

// Note: Connect NeoPixels to MOSI (pin D11 on a Uno, pin D51 on a Mega)

void sendByte (byte b)
  {
    // send one byte to the Neopixels - note that the "off" gap is partly handled by the loop overhead
    // gaps measured empirically to be 1.7 µs to 2 µs, so we don't need to add any more of our own
    for (byte bit = 0; bit < 8; bit++)
      {
	// byte b mit 0x80 = binär 10000000 ausmaskieren. Ergebnis ist 1, wenn erstes bit von b auch 1 ist.
      if (b & 0x80) // is high-order bit set?
        SPI.transfer (0b11111100);  // 1 bit - 750 ns on + 250 ns off (acceptable "on" range 550 ns to 850 ns)
      else
        SPI.transfer (0b11100000);  // 0 bit - 375 ns on + 625 ns off (acceptable "on" range 200 ns to 500 ns)
	// b = b << 1
      b <<= 1; // shift next bit into high-order position
    } // end of for each bit
} // end of sendByte

void ledsetup()
{
  SPI.begin ();
  SPI.setClockDivider (SPI_CLOCK_DIV2);
  SPI.setBitOrder (MSBFIRST);
  SPI.setDataMode (SPI_MODE1);   // MOSI normally low.
  show ();                       // in case MOSI went high, latch in whatever-we-sent
  sendPixel (0, 0, 0);           // now change back to black
  show ();                       // and latch that
}  // end of ledsetup

void sendPixel (const byte r, const byte g, const byte b)
  {
  sendByte (g);        // NeoPixel wants colors in green-then-red-then-blue order
  sendByte (r);
  sendByte (b);
  } // end of sendPixel

// Just wait long enough without sending any bits to cause the pixels to latch and display the last sent frame
void show()
  {
  delayMicroseconds (9);
  } // end of show

// Display a single color on the whole string
void showColor (const unsigned int count, const byte r , const byte g , const byte b)
  {
  noInterrupts ();
  for (unsigned int pixel = 0; pixel < count; pixel++)
    sendPixel (r, g, b);
  interrupts ();
  show ();  // latch the colours
  } // end of showColor

// for the rainbow animation  
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
void Wheel (byte WheelPos, byte & r, byte & g, byte & b) {
  if (WheelPos < 85) {
    r = WheelPos * 3;
    g = 255 - WheelPos * 3;
    b = 0;
    }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    r = 255 - WheelPos * 3;
    g = 0;
    b = WheelPos * 3;
    }
  else {
    WheelPos -= 170;
    r = 0;
    g = WheelPos * 3;
    b = 255 - WheelPos * 3;
    }
} // end of Wheel