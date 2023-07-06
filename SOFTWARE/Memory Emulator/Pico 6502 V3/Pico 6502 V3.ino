/*
 Name:		Pico_6502_V30.ino
 Author:	Rien Matthijsse
*/

#include "pico/stdio.h"

#include "pico/stdlib.h"
#include "pico/time.h"

#include "hardware/clocks.h"
#include "hardware/vreg.h"

#include "mos65C02.h"
#include "memory.h"
#include "m6821.h"


// If this is active, then an overclock will be applied
//#define OVERCLOCK

// Delay startup by so many seconds
#define START_DELAY 0

/// <summary>
/// setup emulator
/// </summary>
void setup() {
  Serial.begin(115200);
  //  while (!Serial);

  sleep_ms(1500);
  Serial.println("PICO/6502 memulator V3.0");

#ifdef OVERCLOCK
  vreg_set_voltage(VREG_VOLTAGE_1_15);
  set_sys_clock_khz(252000UL, true);
#endif

  for (uint8_t i = START_DELAY; i > 0; i--) {
    Serial.printf("Starting in %d \n", i);
    sleep_ms(1000);
  }
  //Serial.printf("Starting\n");

  initmemory();

  init6821();

  init6502();
  reset6502();

  tick6502(10UL);
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
    if (Serial.peek() == 0x12) {
      byte ch = Serial.read();
      Serial.printf("RESET\n");
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
  // should not get here
}

//-------------------------- other cpu -----------------------------
/// <summary>
/// 
/// </summary>
void setup1() {
  pinMode(25, OUTPUT); // LED
}

/// <summary>
/// 
/// </summary>
void loop1() {
  static uint16_t j = 1;

  digitalWrite(25, LOW);
  delay(5);

  serialEvent1();

  // Flush USB from time to time.
  if (j-- == 0) {
    Serial.flush();
    j = 50;
  }

  digitalWrite(25, HIGH);
  delay(1);
}
