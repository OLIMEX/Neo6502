// 
// 
// 
#include "memory.h"
#include "m6821.h"

#include "ewoz.h"
#include "mon_ext.h"
#include "msbasic.h"

/// <summary>
/// 64k RAM
/// </summary>
uint8_t mem[MEMORY_SIZE];

// address and data registers
uint16_t address;
uint8_t  data;

/// <summary>
/// initialise memory
/// </summary>
void initmemory() {
  address = 0UL;
  data = 0;

  // lets install some ROMS

  // copy ewoz monitor  ROM into RAM
  for (uint16_t i = 0; i < EWOZ_SIZE; i++) {
    mem[EWOZ_START + i] = ewoz_bin[i];
  }

  // overrule reset vector
  mem[0xFFFC] = 0x20; // ewoz
  mem[0xFFFD] = 0xFC; // ewoz

  // copy monitor ext ROM into RAM
  for (uint16_t i = 0; i < MON_EXT_SIZE; i++) {
    mem[MON_EXT_START + i] = mon_ext_bin[i];
  }

  // copy msbasic ROM into RAM
  for (uint16_t i = 0; i < MSBASIC_SIZE; i++) {
    mem[MSBASIC_START + i] = msbasic_bin[i];
  }
}

/// <summary>
/// read a byte from memory
/// </summary>
/// <param name=address"</param>
/// <param name=data"</param>
/// <returns></returns>
void readmemory() {
  // 6821?
  if (KBD <= address && address <= DSPCR) {
    // KBD?
    if (address == KBD) {
      if (regKBDCR & 0x02) {
        // KBD register  
        data = regKBD;
        regKBDCR &= 0x7F;    // clear IRQA bit upon read
      }
      else
        data = regKBDDIR;
    }
    else
      // KBDCR?
      if (address == KBDCR) {
        // KBDCR register
        data = regKBDCR;
      }
      else
        // DSP?
        if (address == DSP) {
          if (regDSPCR & 0x02) {
            // DSP register  
            data = regDSP;
            regDSPCR &= 0x7F;    // clear IRQA bit upon read
          }
          else
            data = regDSPDIR;
        }
        else
          // DSPCR?
          if (address == DSPCR) {
            // DSPCR register
            data = regDSPCR;
          }
  }
  else
    data = mem[address];
}

/// <summary>
/// store a byte into memory
/// </summary>
/// <param name="address"></param>
/// <param name="data"></param>
void writememory() {
  // 6821?
  if (KBD <= address && address <= DSPCR) {
    // KBD?
    if (address == KBD) {
      if (regKBDCR & 0x02) {
        // KBD register
        regKBD = data;
      }
      else
        regKBDDIR = data;
    }
    else
      // KBDCR?
      if (address == KBDCR) {
        // KBDCR register
        regKBDCR = data & 0X7F;
      }
      else
        // DSP?
        if (address == DSP) {
          if (regDSPCR & 0x02) {
            // DSP register
            if (data == 0x8D)
              Serial.write("\r\n");    // send CR / LF
            else
              Serial.write(regDSP = (data & 0x7F));
          }
          else
            regDSPDIR = data;
        }
        else
          // DSPCR?
          if (address == DSPCR) {
            // DSPCR register
            regDSPCR = data;
          }
  }
  else
    mem[address] = data;
}
