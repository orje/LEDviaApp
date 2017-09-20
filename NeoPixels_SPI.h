#include <SPI.h>
void sendByte (byte b);
void ledsetup();
void sendPixel (const byte r, const byte g, const byte b);
void show();
void showColor (const unsigned int count, const byte r , const byte g , const byte b);

// for the rainbow animation
void Wheel (byte WheelPos, byte & r, byte & g, byte & b);

typedef struct colour {
  byte r;
  byte g;
  byte b;
} colour;  // end of struct colour