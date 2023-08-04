// 
// Author: Rien Matthijsse
// 

#ifndef _M6821_h
#define _M6821_h

#include "arduino.h"

////////////////////////////////////////////////////////////////////
// 6821 Peripheral
// emulate just enough so keyboard/display works thru serial port.
////////////////////////////////////////////////////////////////////
//

#define KBD   0xd010
#define KBDCR 0xd011
#define DSP   0xd012
#define DSPCR 0xd013

extern byte regKBD;
extern byte regKBDDIR;    // Dir register when KBDCR.bit2 == 0
extern byte regKBDCR;
extern byte regDSP;
extern byte regDSPDIR;    // Dir register when DSPCR.bit2 == 0
extern byte regDSPCR; 

extern void init6821();

#endif

