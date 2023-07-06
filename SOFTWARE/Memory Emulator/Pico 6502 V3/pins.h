#pragma once

// 65c02 connections

#define uP_RESET  28
#define uP_CLOCK  27
#define uP_RW     26

//                                2         1         0
//                              21098765432109876543210                        
constexpr uint32_t en_MASK =  0b11100000000000000000000;
constexpr uint32_t en_NONE =  0b11100000000000000000000;
constexpr uint32_t en_A0_7 =  0b01100000000000000000000;
constexpr uint32_t en_A8_15 = 0b10100000000000000000000;
constexpr uint32_t en_D0_7 =  0b11000000000000000000000;
