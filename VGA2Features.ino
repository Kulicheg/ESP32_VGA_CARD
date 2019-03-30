//This example shows several 2d drawing features available for VGA
//You need to connect a VGA screen cable and an external DAC (simple R2R does the job) to the pins specified below.
//cc by-sa 4.0 license
//bitluni

#include <ESP32Lib.h>
#include <Ressources/Font6x8.h>
#include <EasyTransfer.h>



//pin configuration
const int redPins[] = {2, 4, 12, 13, 14};
const int greenPins[] = {15, 16, 17, 18, 19};
const int bluePins[] = {21, 22, 23, 27};
const int hsyncPin = 32;
const int vsyncPin = 33;

int incomingByte;
byte header [4] = {49, 50, 51, 52}; // 1234

int x1d;
int y1d;
int x2d;
int y2d;
int command;

unsigned int colord;



struct commandPack
{
  int16_t command;
  int16_t x1;
  int16_t y1;
  int16_t x2;
  int16_t y2;
  uint16_t color;
};
struct commandPack Pack;

const byte PackSize = sizeof (Pack);

VGA14Bit vga;
EasyTransfer ETin;




//initial setup
void setup()
{
  Serial.begin(115200);

  ETin.begin(details(Pack), &Serial);


  //we need double buffering for smooth animations
  vga.setFrameBufferCount(2);
  vga.init(vga.MODE320x200, redPins, greenPins, bluePins, hsyncPin, vsyncPin);
  //setting the font
  vga.setFont(Font6x8);

  vga.clear(0);
  vga.setCursor(10, 30);
  vga.setTextColor(vga.RGB(255, 255, 255));

}

void loop()
{
  command = 0;
  long int s, f;

  s = millis();
  if (ETin.receiveData())
  {
    command = Pack.command;
    x1d = Pack.x1;
    y1d = Pack.y1;
    x2d = Pack.x2;
    y2d = Pack.y2;
    colord = Pack.color;
    f = millis ();
  }

  switch (command)
  {
    case 00:

      //Serial.println("00: No Command");

      break;

    case 1:

      //Serial.println("01:vga.clear(color)");
      vga.clear(colord);
      break;

    case 2:

      //Serial.println("02:vga.show()");
      vga.show();
      break;

    case 3:

      //Serial.println("03:setCursor(x,y)");
      vga.setCursor(x1d, y1d);
      break;

    case 4:

      //Serial.println("04:setTextColor(color)");
      vga.setTextColor(colord);
      break;

    case 5:

      //Serial.println("05:dot(x,y,c)");
      vga.dot(x1d, y1d, colord);
      break;

    case 6:

      //Serial.println("06:line(x1, y1, x2, y2, color)");
      vga.line(x1d, y1d, x2d, y2d, colord);
      break;

    case 7:

      //Serial.println("07:rect(x, y, w, h, c)");
      vga.rect(x1d, y1d, x2d, y2d, colord);
      break;

    case 8:

      //Serial.println("08:fillRect(x, y, w, h, c)");
      vga.fillRect(x1d, y1d, x2d, y2d, colord);
      break;

    case 9:

      //Serial.println("09:circle(x,y,r,c)");
      vga.circle(x1d, y1d , x2d , colord);
      break;

    case 10:

      //Serial.println("10:ellipse(x,y,rx,ry,c)");
      vga.ellipse(x1d, y1d, x2d, y2d, colord);
      break;

    case 11:

      //Serial.println("11:fillEllipse(x,y,rx,ry,c)");
      vga.fillEllipse(x1d, y1d, x2d, y2d, colord);
      break;

    case 12:

      //Serial.println("12:fillCircle(x, y, r, color)");
      vga.fillCircle(x1d, y1d , x2d , colord);
      break;

    case 13:

      String text =  "    ";

      for ( int pages = 0; pages < 4; pages++)
      {

        text.setCharAt(0, x1d);
        text.setCharAt(1, y1d);
        text.setCharAt(2, x2d);
        text.setCharAt(3, y2d);

        const char * txt = text.c_str();
        vga.print((const char *)txt);

        break;

      }
      //vga.show();
  }
}
