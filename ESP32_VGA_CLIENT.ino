// AA - 170
// AB - 171
// BA - 186
// BB - 187

#include <EasyTransfer.h>
EasyTransfer ETin, ETout;

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
byte Packet[PackSize];


byte header [4] = {49, 50, 51, 52}; // 1234
byte command;


void setup()
{
  Serial.begin(115200);
  ETin.begin(details(Pack), &Serial);
  ETout.begin(details(Pack), &Serial);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{

  unsigned int c = 0;
  //  for (int y = 0; y < 20; y++)
  //  {
  //    for (int x = 0; x < 32; x++)
  //    {
  //      fillrect (x * 10, y * 10, 10, 10, c * 102);
  //      c++;
  //    }
  //  }
  //cls(0);
  lprint ("Hello world!", 65535);
  //lprint ("-=#O.O#=-", 32768);

   delay(3000);
  
}



void cls(uint16_t c)
{
  Pack.command = 1;
  Pack.x1 = 0;
  Pack.y1 = 0;
  Pack.x2 = 0;
  Pack.y2 = 0;
  Pack.color = c;
  ETout.sendData();
}

void vgashow()
{
  Pack.command = 2;
  Pack.x1 = 0;
  Pack.y1 = 0;
  Pack.x2 = 0;
  Pack.y2 = 0;
  Pack.color = 0;
  ETout.sendData();
}

void setcursor(int16_t x1, int16_t y1)
{
  Pack.command = 3;
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = 0;
  Pack.y2 = 0;
  Pack.color = 0;
  ETout.sendData();
}


void settextcolor(uint16_t c)
{
  Pack.command = 4;
  Pack.x1 = 0;
  Pack.y1 = 0;
  Pack.x2 = 0;
  Pack.y2 = 0;
  Pack.color = c;
  ETout.sendData();
}

void dot(int16_t x1, int16_t y1, uint16_t c)
{
  Pack.command = 5;
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = 0;
  Pack.y2 = 0;
  Pack.color = c;
  ETout.sendData();
}

void line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t c)
{
  Pack.command = 6;
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = x2;
  Pack.y2 = y2;
  Pack.color = c;
  ETout.sendData();
}



void rect(int16_t x1, int16_t y1, int16_t w, int16_t h, uint16_t c)
{
  Pack.command = 7;
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = w;
  Pack.y2 = h;
  Pack.color = c;
  ETout.sendData();

}

void fillrect(int16_t x1, int16_t y1, int16_t w, int16_t h, uint16_t c)
{
  Pack.command = 8;
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = w;
  Pack.y2 = h;
  Pack.color = c;
  ETout.sendData();
}

void circle(int16_t x1, int16_t y1, int16_t r, uint16_t c)
{
  Pack.command = 9;
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = r;
  Pack.y2 = 0;
  Pack.color = c;
  ETout.sendData();
}



void ellipse (int16_t x1, int16_t y1, int16_t rx, int16_t ry, uint16_t c)
{
  Pack.command = 10;
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = rx;
  Pack.y2 = ry;
  Pack.color = c;
  ETout.sendData();
}


void fillellipse (int16_t x1, int16_t y1, int16_t rx, int16_t ry, uint16_t c)
{
  Pack.command = 11;
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = rx;
  Pack.y2 = ry;
  Pack.color = c;
  ETout.sendData();
}


void fillcircle(int16_t x1, int16_t y1, int16_t r, uint16_t c)
{
  Pack.command = 12;
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = r;
  Pack.y2 = 0;
  Pack.color = c;
  ETout.sendData();
}

void lprint(String text, int16_t color)
{
  int lng = text.length();
  int ostatok = lng % 4;

  if (ostatok != 0) ostatok =  4 - (lng % 4);

  //  Serial.print("lng = ");
  //  Serial.println(lng);
  //  Serial.print("ostatok = ");
  //  Serial.println(ostatok);

  for (int con  = 0; con < ostatok; con++)
  {
    text = text  + "@";
  }
  lng = text.length() / 4;
  for ( int pages = 0; pages < lng; pages++)
  {
    Pack.command = 13;
    Pack.x1 = text.charAt(pages * 4 + 0);
    Pack.y1 = text.charAt(pages * 4 + 1);
    Pack.x2 = text.charAt(pages * 4 + 2);
    Pack.y2 = text.charAt(pages * 4 + 3);
    Pack.color = color;
    ETout.sendData();

  }

}
