// AA - 170
// AB - 171
// BA - 186
// BB - 187

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

byte currentByte;
byte header [4] = {49, 50, 51, 52}; // 1234
byte command;



void setup()
{

  Serial.begin(115200);
}

void loop()
{
  fillrect(random(280)+20, random(160)+20, random(19), random(19), random(32768));
  dot(160, 100, random(32768));
}


void cls(uint16_t c)
{
  Pack.x1 = 0;
  Pack.y1 = 0;
  Pack.x2 = 0;
  Pack.y2 = 0;
  Pack.color = c;

  packSender (1);
}

void vgashow()
{
  Pack.x1 = 0;
  Pack.y1 = 0;
  Pack.x2 = 0;
  Pack.y2 = 0;
  Pack.color = 0;

  packSender (2);
}

void setcursor(int16_t x1, int16_t y1)
{
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = 0;
  Pack.y2 = 0;
  Pack.color = 0;

  packSender (3);
}


void settextcolor(uint16_t c)
{
  Pack.x1 = 0;
  Pack.y1 = 0;
  Pack.x2 = 0;
  Pack.y2 = 0;
  Pack.color = c;

  packSender (4);
}

void dot(int16_t x1, int16_t y1, uint16_t c)
{
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = 0;
  Pack.y2 = 0;
  Pack.color = c;
  packSender (5);
}

void line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t c)
{
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = x2;
  Pack.y2 = y2;
  Pack.color = c;
  packSender (6);
}



void rect(int16_t x1, int16_t y1, int16_t w, int16_t h, uint16_t c)
{
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = w;
  Pack.y2 = h;
  Pack.color = c;
  packSender (7);
}

void fillrect(int16_t x1, int16_t y1, int16_t w, int16_t h, uint16_t c)
{
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = w;
  Pack.y2 = h;
  Pack.color = c;
  packSender (8);
}

void circle(int16_t x1, int16_t y1, int16_t r, uint16_t c)
{
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = r;
  Pack.y2 = 0;
  Pack.color = c;
  packSender (9);
}



void ellipse (int16_t x1, int16_t y1, int16_t rx, int16_t ry, uint16_t c)
{
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = rx;
  Pack.y2 = ry;
  Pack.color = c;
  packSender (10);
}


void fillellipse (int16_t x1, int16_t y1, int16_t rx, int16_t ry, uint16_t c)
{
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = rx;
  Pack.y2 = ry;
  Pack.color = c;
  packSender (11);
}


void fillcircle(int16_t x1, int16_t y1, int16_t r, uint16_t c)
{
  Pack.x1 = x1;
  Pack.y1 = y1;
  Pack.x2 = r;
  Pack.y2 = 0;
  Pack.color = c;
  packSender (12);
}

void lprint(String text)
{
  Pack.x1 = 1;
  Pack.y1 = 1;
  Pack.x2 = 1;
  Pack.y2 = 1;
  Pack.color = 1;
  packSender (13);
}



void packSender (byte command)
{

  for (byte q = 0; q < 4; q++)
  {
    Serial.write (header[q]);
  }
  Serial.write (command);

  unsigned char * Packet;
  Packet = (unsigned char *) &Pack;

  for (int count = 0; count < PackSize; count++)
  {
    Serial.write(Packet[count]);
  }



}
