/*
 Name:		Pico_NEO6502
 Author:	Rien Matthijsse

 Inspired by work  http://www.8bitforce.com/blog/2019/03/12/retroshield-6502-operation/
*/

#include "pico/stdio.h"

#include "pico/stdlib.h"
#include "pico/time.h"

#ifdef OVERCLOCK
#include "hardware/clocks.h"
#include "hardware/vreg.h"
#endif

#include "mos65C02.h"
#include "memory.h"
#include "m6821.h"

// Delay startup by so many seconds
#define START_DELAY 0

// 1-bit (black, white) text mode for PicoDVI.
#include <PicoDVI.h>

// Here's how an 80x30 character display is declared.
DVItext1 display(DVI_RES_640x480p60, pico_neo6502_cfg);

//
uint32_t  clockCount = 0UL;
unsigned long  lastClockTS;
boolean  statusCursor = true;

/// <summary>
/// performa a action on the display
/// </summary>
/// <param name="vCmd"></param>
void setCommand(uint8_t vCmd) {
  switch (vCmd) {
  case 0x01: // clearscreen
//    Serial.println("CLS");
    display.fillScreen(0);
    display.setCursor(0, 0);
    break;
  }
}

/// <summary>
/// 
/// </summary>
/// <param name="vSet"></param>
void showCursor(boolean vSet) {
  statusCursor = vSet;
}

/// <summary>
/// get current x-pos of cursor
/// </summary>
/// <returns></returns>
uint8_t getCursorX() {
  return display.getCursorX();
}

/// <summary>
/// get current y-pos of cursor
/// </summary>
/// <returns></returns>
uint8_t getCursorY() {
  return display.getCursorY();
}

/// <summary>
/// set x-pos of cursor
/// </summary>
/// <param name="vX"></param>
void setCursorX(uint8_t vX) {
  display.setCursor(vX % 80, display.getCursorY());
}

/// <summary>
/// set y-pos of cursor
/// </summary>
/// <param name="vY"></param>
void setCursorY(uint8_t vY) {
  display.setCursor(display.getCursorX(), vY % 60);
}

/// <summary>
/// 
/// </summary>
inline __attribute__((always_inline))
void writeBS() {
  display.setCursor(display.getCursorX() - 1, display.getCursorY());
}

/// <summary>
///  write a char to output DVI output
/// </summary>
/// <param name="vChar"></param>
void writeChar(uint8_t vChar) {
  switch (vChar) {
  case 0x8D: // CR
  case 0x0D: // CR
    if (statusCursor)
      display.println(" ");
    else
      display.println("");
    break;
  case 0x88: // BS
  case 0x08: // BS
    display.write(' ');
    writeBS();
    if (statusCursor) {
      display.write('_');
      writeBS();
    }
    break;
  default:
    display.write(vChar);
    if (statusCursor) {
      display.write('_');
      writeBS();
    }
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>
/// setup emulator
/// </summary>
void setup() {
  Serial.begin(115200);
  //  while (!Serial);

  sleep_ms(2500);
  Serial.println("NEO6502 memulator v0.01");

  if (!display.begin()) {
    Serial.println("ERROR: not enough RAM available");
    for (;;);
  }

  for (uint8_t i = START_DELAY; i > 0; i--) {
    Serial.printf("Starting in %d \n", i);
    sleep_ms(1000);
  }
  Serial.printf("Starting\n");

  initmemory();

  init6821();

  init6502();
  reset6502();

  // 4 stats
  clockCount = 0UL;
  lastClockTS = millis();

  // and we have lift off
  display.println("NEO6502 memulator v0.01");
}

////////////////////////////////////////////////////////////////////
// Serial Event
////////////////////////////////////////////////////////////////////

/*
  SerialEvent occurs whenever a new data comes in the
  hardware serial RX. Multiple bytes of data may be available.
 */
inline __attribute__((always_inline))
void serialEvent1()
{
  if (Serial.available()) {
    if (Serial.peek() == 0x12) { // ^R
      byte ch = Serial.read();
      Serial.println("RESET");
      showCursor(true);
      reset6502();
    }
    else {
      if ((regKBDCR & 0x80) == 0x00) {    // read serial byte only if we can set 6821 interrupt
        cli();                            // stop interrupts while changing 6821 guts.
        // 6821 portA is available      
        byte ch = toupper(Serial.read()); // apple1 expects upper case
        regKBD = ch | 0x80;               // apple1 expects bit 7 set for incoming characters.
        //     Serial.printf("Pressed %02x\n", regKBD);
        regKBDCR |= 0x80;                 // set 6821 interrupt
        sei();
      }
    }
  }
  return;
}


/// <summary>
/// 
/// </summary>
void loop() {
  static uint16_t i, j = 1;

  tick6502(0UL);
  clockCount++;

  // Flush USB from time to time.
  if (j-- == 0) {
    gpio_put(25, LOW);

    serialEvent1();
    display.flush();

    j = 5000;

    gpio_put(25, HIGH);
  }

  if (i-- == 0) {
    if ((millis() - lastClockTS) >= 5000UL) {
      Serial.printf("kHz = %0.1f\n", clockCount / 5000.0);

      clockCount = 0UL;
      lastClockTS = millis();
    }

    i = 10000;
  }
}
