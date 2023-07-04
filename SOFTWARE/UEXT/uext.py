from machine import Pin, Timer

gp22 = Pin(22, Pin.OUT)
gp23 = Pin(23, Pin.OUT)
gp24 = Pin(24, Pin.OUT)
gp25 = Pin(25, Pin.OUT)
gp26 = Pin(26, Pin.OUT)
gp27 = Pin(27, Pin.OUT)
gp28 = Pin(28, Pin.OUT)
gp29 = Pin(29, Pin.OUT)

tim = Timer()

def tick(timer):
    global gp22,gp23,gp24,gp25,gp26,gp27,gp28,gp29
    gp22.toggle()
    gp23.toggle()
    gp24.toggle()
    gp25.toggle()
    gp26.toggle()
    gp27.toggle()
    gp28.toggle()
    gp29.toggle()

tim.init(freq=1, mode=Timer.PERIODIC, callback=tick)