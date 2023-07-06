// 
// Author: Rien Matthijsse
// 

#include "m6821.h"

byte regKBD;
byte regKBDDIR;    // Dir register when KBDCR.bit2 == 0
byte regKBDCR;
byte regDSP;
byte regDSPDIR;    // Dir register when DSPCR.bit2 == 0
byte regDSPCR;


/// <summary>
/// 
/// </summary>
void init6821()
{
  regKBD = 0x00;
  regKBDDIR = 0x00;
  regKBDCR = 0x00;
  regDSP = 0x00;
  regDSPDIR = 0x00;
  regDSPCR = 0x00;
}
