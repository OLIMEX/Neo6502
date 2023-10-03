
Apple ][ and Oric Atmos emulators: https://github.com/vsladkov/reload-emulator
==============================================================================

6502 firmware: http://www.robsons.org.uk/neo6502/ https://github.com/paulscottrobson/neo6502
============================================================================================

Arduino project with BBC BASIC: https://github.com/marobi/Pico_6502_v4
======================================================================

Same project ported to PlatformIO: https://github.com/astralaster/Pico_6502_v4_platformio
=========================================================================================

Neo6502 hardware check:

Video uses PicoDVI https://github.com/Wren6991/PicoDVI
======================================================
With these modifications fo match the hardware wiring of the DVI signals:

in common_dvi_pin_configs.h

must be set:

#define DVI_DEFAULT_SERIAL_CONFIG pico_neo6502_cfg

and the hardware definition:

// Pico HDMI for Olimex Neo6502
static const struct dvi_serialiser_cfg pico_neo6502_cfg = {
	.pio = DVI_DEFAULT_PIO_INST,
	.sm_tmds = {0, 1, 2},
	.pins_tmds = {14, 18, 16},
	.pins_clk = 12,
	.invert_diffpairs = true
};

Keyboard and mouse uses usb2serial https://github.com/OLIMEX/usb2serial
=======
usb2serial is based on which is based on https://github.com/No0ne/ps2x2pico
Keyboard or/and mouse can be connected to Neo6502 and if DEBUG is set it will stream on the SERUAL port the received Keyboard and Mouse data

UEXT is tested with python code
===============================

Audio is tested with python code
===============================

