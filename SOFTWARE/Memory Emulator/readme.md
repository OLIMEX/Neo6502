# Neo6502 memory emulator no PIO

This is work in progress code, use HDMI to connect to monitor and terminal to connect to COM port which Neo6502 will create. 
In Linux it's usually dev/ttyACM0

##Ewoz commands:

start.end	memory dump i.e. 0.100 will display memory content 0x000-0x100

addressR	run code from address

BASIC entry point is BD1B you can run the BASIC with BD1BR

It will ask for amount of memory: enter 32769
then number of columns: enter 80

If you connect UEXT.10 pin to Neo6502BUS.40 you can use aldo Ctrl-R to reset the 6502.
