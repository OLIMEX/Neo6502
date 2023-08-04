#pragma once
// 
// Author: Rien Matthijsse
// 
#define NEO6502

// 65c02 connections
//
#ifdef NEO6502
// NEO6502 board v1.0
#define uP_RESET  26 // RESB(40) <-- UEXT pin 9
#define uP_CLOCK  21 // PHI2
#define uP_RW     11 // RW#

#define uP_BUZZ   20

/*
BUS:
0 - 7
HDMI: pico_neo6502_cfg
15 - 18  27 - 30
*/
#else
// Rien's BB setup
#define uP_RESET  28 // RESB
#define uP_CLOCK  27 // PHI2
#define uP_RW     26 // RW#

/*
BUS:
0 - 7
HDMI: pico_sock_cfg 
12 - 19
*/
#endif

// mux bus enable pins
//                                2         1         0
//                              21098765432109876543210   
#ifdef NEO6502
// 8 - 10
constexpr uint32_t en_MASK =  0b00000000000011100000000;
constexpr uint32_t en_NONE =  0b00000000000011100000000;
constexpr uint32_t en_A0_7 =  0b00000000000011000000000;
constexpr uint32_t en_A8_15 = 0b00000000000010100000000;
constexpr uint32_t en_D0_7 =  0b00000000000001100000000;
#else
// 20 - 22
constexpr uint32_t en_MASK =  0b11100000000000000000000;
constexpr uint32_t en_NONE =  0b11100000000000000000000;
constexpr uint32_t en_A0_7 =  0b01100000000000000000000;
constexpr uint32_t en_A8_15 = 0b10100000000000000000000;
constexpr uint32_t en_D0_7 =  0b11000000000000000000000;
#endif
