//This example shows several 2d drawing features available for VGA
//You need to connect a VGA screen cable and an external DAC (simple R2R does the job) to the pins specified below.
//cc by-sa 4.0 license
//bitluni

#include <ESP32Lib.h>
#include <Ressources/Font6x8.h>



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
unsigned int colord;



struct commandPack
{
  int16_t x1;
  int16_t y1;
  int16_t x2;
  int16_t y2;
  uint16_t color;
};

struct commandPack Pack;

const byte PackSize = sizeof (Pack);
byte Packet[PackSize];

//VGA Device
VGA14Bit vga;

//initial setup
void setup()
{
  Serial.begin(115200);


  //we need double buffering for smooth animations
  vga.setFrameBufferCount(2);
  vga.init(vga.MODE320x200, redPins, greenPins, bluePins, hsyncPin, vsyncPin);
  //setting the font
  vga.setFont(Font6x8);
  Serial.print ("PackSize=");
  Serial.println (PackSize);

  vga.setCursor(10, 30);
  vga.setTextColor(vga.RGB(255, 255, 255));
}

void loop()
{

  byte command = headerdetector();


  //vga.clear(0);
  switch (command)
  {
    case 00:

      //Serial.println("00: No Command");

      break;

    case 1:

      Serial.println("01:vga.clear(color)");
      packDecoder ();
      vga.clear(colord);
      break;

    case 2:

      Serial.println("02:vga.show()");
      vga.show();
      break;

    case 3:

      Serial.println("03:setCursor(x,y)");
      packDecoder ();
      vga.setCursor(x1d, y1d);
      break;

    case 4:

      Serial.println("04:setTextColor(color)");
      packDecoder ();
      vga.setTextColor(colord);
      break;

    case 5:

      //Serial.println("05:dot(x,y,c)");
      packDecoder ();
      vga.dot(x1d, y1d, colord);
      break;

    case 6:

      Serial.println("06:line(x1, y1, x2, y2, color)");
      packDecoder ();
      vga.line(x1d, y1d, x2d, y2d, colord);
      break;

    case 7:

      Serial.println("07:rect(x, y, w, h, c)");
      packDecoder ();
      vga.rect(x1d, y1d, x2d, y2d, colord);
      break;

    case 8:

      Serial.println("08:fillRect(x, y, w, h, c)");
      packDecoder ();
      vga.fillRect(x1d, y1d, x2d, y2d, colord);
      break;

    case 9:

      Serial.println("09:circle(x,y,r,c)");
      packDecoder ();
      vga.circle(x1d, y1d , x2d , colord);
      break;

    case 10:

      Serial.println("10:ellipse(x,y,rx,ry,c)");
      packDecoder ();
      vga.ellipse(x1d, y1d, x2d, y2d, colord);
      break;

    case 11:

      Serial.println("11:fillEllipse(x,y,rx,ry,c)");
      packDecoder ();
      vga.fillEllipse(x1d, y1d, x2d, y2d, colord);
      break;

    case 12:

      Serial.println("12:fillCircle(x, y, r, color)");
      packDecoder ();
      vga.fillCircle(x1d, y1d , x2d , colord);
      break;

    case 13:

      Serial.println("13:print(text)");
      packDecoder ();
      vga.print("placeholder for text");
      break;

    case 49:

      packDecoder ();
      Serial.println("49:");
      vga.ellipse(x1d - 1, y1d - 1, x2d / 10, y2d / 10, 0);
      vga.ellipse(x1d, y1d, x2d / 10, y2d / 10, colord / 3);

      break;
  }

  vga.setCursor(10, 10);
  vga.setTextColor(vga.RGB(255, 255, 255));
  vga.print("free memory: ");
  vga.print((int)heap_caps_get_free_size(MALLOC_CAP_DEFAULT));

  //vga.show();
}


byte headerdetector()
{
  byte command = 0;
  byte flag = 0;
  byte currentByte;



  if (Serial.available())
  {
    while (flag < 4)

    { currentByte = Serial.read();

      if (currentByte == header [flag]) flag++; else flag = 0;
    }
  }

  if (Serial.available()) command = Serial.read();

  if (command > 100)
  {
    Serial.print ("Invalid command: ");
    Serial.println (command);
    command = 255;
  }

  return command;
}


void packDecoder ()
{



  for (int count = 0; count < PackSize; count++)
  {
    if (Serial.available()) Packet[count] = Serial.read();
  }

  memcpy(&Pack, Packet, PackSize);

  x1d = Pack.x1;
  y1d = Pack.y1;
  x2d = Pack.x2;
  y2d = Pack.y2;
  colord = Pack.color;
}
