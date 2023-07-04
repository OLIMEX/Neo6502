from machine import Pin, Timer

buz = Pin(20, Pin.OUT)

tim = Timer()

def tick(timer):
    global buz
    buz.toggle()

tim.init(freq=500, mode=Timer.PERIODIC, callback=tick)