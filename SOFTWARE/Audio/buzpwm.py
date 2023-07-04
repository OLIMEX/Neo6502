from machine import Pin, PWM
import time

buz = PWM(Pin(20))

buz.freq(1000)

buz.duty_u16(32768)

time.sleep_ms(1000)

buz.deinit()

