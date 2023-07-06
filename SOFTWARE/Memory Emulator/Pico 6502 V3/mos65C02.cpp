// 
// 
// 
#include "mos65C02.h"

#define DELAY_FACTOR_SHORT() asm volatile("nop\nnop\n");
#define DELAY_FACTOR_LONG()  asm volatile("nop\nnop\nnop\nnop\n");

#define RESET_COUNT  4

constexpr uint32_t BUS_MASK = 0xFF;

//
uint8_t   resetCount;
boolean   inReset = false;
uint8_t   dataDir = 2;

/// <summary>
/// 
/// </summary>
/// <param name="enable"></param>
inline __attribute__((always_inline))
void setClock(boolean clock) {
  gpio_put(uP_CLOCK, clock);
}

/// <summary>
/// 
/// </summary>
/// <param name="enable"></param>
inline __attribute__((always_inline))
void setReset(boolean reset) {
  gpio_put(uP_RESET, reset);
}

/// <summary>
/// 
/// </summary>
/// <param name="enable"></param>
inline __attribute__((always_inline))
void setEnable(uint32_t enable) {
  gpio_put_masked(en_MASK, enable);
}

/// <summary>
/// 
/// </summary>
/// <param name="direction"></param>
inline __attribute__((always_inline))
void setDir(uint8_t direction) {
  if (direction != dataDir) {
    switch (direction) {
    case OUTPUT:  gpio_set_dir_masked(BUS_MASK, BUS_MASK);
      break;
    case INPUT:   gpio_set_dir_masked(BUS_MASK, (uint32_t)0UL);
      break;
    }

    dataDir = direction;
  }
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
inline __attribute__((always_inline))
bool getRW() {
  return gpio_get(uP_RW);
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
inline __attribute__((always_inline))
uint16_t getAddress() {
  // we are already in INPUT
  setDir(INPUT);

  // read A0-7
  setEnable(en_A0_7);
  DELAY_FACTOR_LONG();
//  delayMicroseconds(1UL);
  uint16_t addr = gpio_get_all() & BUS_MASK;

  // read A8-15
  setEnable(en_A8_15);
  DELAY_FACTOR_LONG();
  delayMicroseconds(1UL);
  addr |= (gpio_get_all() & BUS_MASK) << 8;

  return addr;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
inline __attribute__((always_inline))
uint8_t getData() {
  // we are already in INPUT
//  setDir(INPUT);

  setEnable(en_D0_7);
  DELAY_FACTOR_LONG();
  delayMicroseconds(2UL);
  uint8_t data = gpio_get_all() & BUS_MASK;

  return data;
}

/// <summary>
/// 
/// </summary>
/// <param name="data"></param>
inline __attribute__((always_inline))
void putData(uint8_t data) {

  setDir(OUTPUT);
  setEnable(en_D0_7);
  gpio_put_masked(BUS_MASK, (uint32_t)data);
}

/// <summary>
/// 
/// </summary>
void init6502() {
  // CLOCK
  pinMode(uP_CLOCK, OUTPUT);
  setClock(CLOCK_HIGH);

  // RESET
  pinMode(uP_RESET, OUTPUT);
  setReset(ENABLE_HIGH);

  // RW
  pinMode(uP_RW, INPUT_PULLUP);

  // BUS ENABLE
  gpio_init_mask(en_MASK); 
  gpio_set_dir_out_masked(en_MASK); // enable as output
  setEnable(en_NONE); // all high

  // ADDRESS
  // DATA
  gpio_init_mask(BUS_MASK);
  setDir(INPUT);
}

/// <summary>
/// 
/// </summary>
void reset6502() {
  setReset(RESET_LOW);

  resetCount = RESET_COUNT;
  inReset = true;
}

/// <summary>
/// clock cycle 6502
/// </summary>
//inline __attribute__((always_inline))
void tick6502(uint32_t delay)
{
  while (true) {
    setEnable(en_NONE); // all high

    //------------------------------------------------------------------------------------
    setClock(CLOCK_LOW);
    // set INPUT
    setDir(INPUT);

    DELAY_FACTOR_LONG();
#if CPU_DEBUG
    delayMicroseconds(delay);
#endif


    //------------------------------------------------------------------------------------
    setClock(CLOCK_HIGH);

    DELAY_FACTOR_LONG();
    DELAY_FACTOR_LONG();

    address = getAddress();

    // do RW action
    switch (getRW()) {
    case RW_READ:
      readmemory(); // data = @address
      putData(data);
//      Serial.printf("R %04X %02X\n", address, data);
      break;

    case RW_WRITE:
      data = getData();
      writememory(); // @address = data
//      Serial.printf("W %04X %02X\n", address, data);
      break;
    }

    // reset mgmt
    if (inReset) {
      if (resetCount-- == 0) {
        // end of reset
        setReset(RESET_HIGH);
        inReset = false;
        Serial.printf("RESET release\n");
      }
    }

#if CPU_DEBUG
    delayMicroseconds(delay);
#endif
  }
}

#ifdef TEST_MODE
/// <summary>
/// 
/// </summary>
void test6502() {
  uint32_t dly = 50;

  Serial.println("begin");

  Serial.println("RESET");
  setReset(RESET_LOW);
  delay(dly);
  setReset(RESET_HIGH);

  Serial.println("ENABLE 1");
  setEnable(en_A0_7);
  delay(dly);
//  setEnable(en_NONE);

  Serial.println("ENABLE 2");
  setEnable(en_A8_15);
  delay(dly);
//  setEnable(en_NONE);

  Serial.println("ENABLE 3");
  setEnable(en_D0_7);
  delay(dly);
//  setEnable(en_NONE);

  Serial.println("CLOCK");
  setClock(CLOCK_LOW);
  delay(dly);
  setClock(CLOCK_HIGH);

  Serial.println("end");
}
#endif
