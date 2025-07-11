
// base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
// enable or disable GxEPD2_GFX base class
#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>

GxEPD2_3C<GxEPD2_290_C90c, GxEPD2_290_C90c::HEIGHT> display(GxEPD2_290_C90c(/*CS=5*/ 10, /*DC=*/9, /*RES=*/8, /*BUSY=*/7));  // GDEM029C90 128x296, SSD1680

void setup() {
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);

  display.init(115200, true, 50, false);
  helloWorld();
  // helloFullScreenPartialMode();
  // delay(1000);
  // if (display.epd2.hasFastPartialUpdate)
  // {
  //   showPartialUpdate();
  //   delay(1000);
  // }
  display.hibernate();
}

const char HelloWorld[] = "Hello World!";
const char HelloWeACtStudio[] = "WeAct Studio";
const char Vitosha[] = "Vitosha";


void helloWorld() {
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    display.drawLine(0, 36, display.width(), 36, GxEPD_BLACK);

    display.getTextBounds("2", 0, 0, &tbx, &tby, &tbw, &tbh);
    // x = ((display.width() - tbw) / 2) - tbx;
    x = 11;
    y = 10 + tbh;
    display.setCursor(x, y);
    display.print("2");

    display.drawLine(36, 0, 36, 36, GxEPD_BLACK);

    display.getTextBounds(Vitosha, 0, 0, &tbx, &tby, &tbw, &tbh);
    // x = ((display.width() - tbw) / 2) - tbx;
    x = 50;
    y = 10 + tbh;
    display.setCursor(x, y);
    display.print(Vitosha);

    uint16_t half_w = display.width() / 2;

    display.getTextBounds("2", 0, 0, &tbx, &tby, &tbw, &tbh);
    // x = ((display.width() - tbw) / 2) - tbx;
    x = 15 + half_w;
    y = 10 + tbh;
    display.setCursor(x, y);
    display.print("2");

    display.drawLine(40 + half_w, 0, 40 + half_w, 36, GxEPD_BLACK);

    display.drawLine(0, display.height() - 20, display.width(), display.height() - 20, GxEPD_BLACK);
    display.drawLine(display.width() / 2, 0, display.width() / 2, display.height() - 20, GxEPD_BLACK);

    display.getTextBounds("Obelya", 0, 0, &tbx, &tby, &tbw, &tbh);
    x = 39 + 15 + half_w;
    y = 6 + tbh;
    display.setCursor(x, y);
    display.print("Obelya");
    // display.setCursor(x, y - tbh);
    // display.print(HelloWorld);
    // display.setTextColor(display.epd2.hasColor ? GxEPD_RED : GxEPD_BLACK);
    // display.getTextBounds(HelloWeACtStudio, 0, 0, &tbx, &tby, &tbw, &tbh);
    // x = ((display.width() - tbw) / 2) - tbx;
    // display.setCursor(x, y + tbh);
    // display.print(HelloWeACtStudio);
  } while (display.nextPage());
}

void drawCenteredText(const char* text, int y) {
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.getTextBounds(text, 0, y, &tbx, &tby, &tbw, &tbh);
  int x = (display.width() - tbw) / 2 - tbx;
  display.setCursor(x, y);
  display.print(text);
}

void helloFullScreenPartialMode() {
  //Serial.println("helloFullScreenPartialMode");
  const char fullscreen[] = "full screen update";
  const char fpm[] = "fast partial mode";
  const char spm[] = "slow partial mode";
  const char npm[] = "no partial mode";
  display.setPartialWindow(0, 0, display.width(), display.height());
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  if (display.epd2.WIDTH < 104) display.setFont(0);
  display.setTextColor(GxEPD_BLACK);
  const char* updatemode;
  if (display.epd2.hasFastPartialUpdate) {
    updatemode = fpm;
  } else if (display.epd2.hasPartialUpdate) {
    updatemode = spm;
  } else {
    updatemode = npm;
  }
  // do this outside of the loop
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  // center update text
  display.getTextBounds(fullscreen, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t utx = ((display.width() - tbw) / 2) - tbx;
  uint16_t uty = ((display.height() / 4) - tbh / 2) - tby;
  // center update mode
  display.getTextBounds(updatemode, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t umx = ((display.width() - tbw) / 2) - tbx;
  uint16_t umy = ((display.height() * 3 / 4) - tbh / 2) - tby;
  // center HelloWorld
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t hwx = ((display.width() - tbw) / 2) - tbx;
  uint16_t hwy = ((display.height() - tbh) / 2) - tby;
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(hwx, hwy);
    display.print(HelloWorld);
    display.setCursor(utx, uty);
    display.print(fullscreen);
    display.setCursor(umx, umy);
    display.print(updatemode);
  } while (display.nextPage());
  //Serial.println("helloFullScreenPartialMode done");
}

void showPartialUpdate() {
  // some useful background
  helloWorld();
  // use asymmetric values for test
  uint16_t box_x = 10;
  uint16_t box_y = 15;
  uint16_t box_w = 70;
  uint16_t box_h = 20;
  uint16_t cursor_y = box_y + box_h - 6;
  if (display.epd2.WIDTH < 104) cursor_y = box_y + 6;
  float value = 13.95;
  uint16_t incr = display.epd2.hasFastPartialUpdate ? 1 : 3;
  display.setFont(&FreeMonoBold9pt7b);
  if (display.epd2.WIDTH < 104) display.setFont(0);
  display.setTextColor(GxEPD_BLACK);
  // show where the update box is
  for (uint16_t r = 0; r < 4; r++) {
    display.setRotation(r);
    display.setPartialWindow(box_x, box_y, box_w, box_h);
    display.firstPage();
    do {
      display.fillRect(box_x, box_y, box_w, box_h, GxEPD_BLACK);
      //display.fillScreen(GxEPD_BLACK);
    } while (display.nextPage());
    delay(2000);
    display.firstPage();
    do {
      display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
    } while (display.nextPage());
    delay(1000);
  }
  //return;
  // show updates in the update box
  for (uint16_t r = 0; r < 4; r++) {
    display.setRotation(r);
    display.setPartialWindow(box_x, box_y, box_w, box_h);
    for (uint16_t i = 1; i <= 10; i += incr) {
      display.firstPage();
      do {
        display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
        display.setCursor(box_x, cursor_y);
        display.print(value * i, 2);
      } while (display.nextPage());
      delay(500);
    }
    delay(1000);
    display.firstPage();
    do {
      display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
    } while (display.nextPage());
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(8, HIGH);
  delay(1000);
  digitalWrite(8, LOW);
  delay(1000);
}