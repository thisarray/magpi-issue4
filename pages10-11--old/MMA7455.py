# I2C writes =D0=0
# MMA7455 I2C address 1D (3A ,3B) write , read
# AN3745 app note for calibration
# byte read , write 1D , write address, read 1D ,DATA
# Byte write, write 1D , write address, write data.
# addresses,
# 06 XOUT8
# 07 YOUT8
# 08 ZOUT8
# 09 STATUS  D0 1=data ready
# 0A detection source
# 0F who am i
# 16 Mode Control  x1000101 measure 2gmode
# 18 Control1  D7 filter 0=62Hz,1=125Hz other 0
# 19 Control2  default 0


#!/usr/bin/python
import smbus
import time
#import graphics
import pygame

# Define a class called Accel
 
class Accel():

    b = smbus.SMBus(0)
 
	# Read the value
    def getValue(self):
		#address 1D, register 0x16 sets mode
        self.b.write_byte_data(0x1D,0x16,0x45)

		# point at reg 6
        self.b.write_byte_data(0x1D,0x06,00)
 
		# Read the x value
        l = self.b.read_byte_data(0x1D,00)
        return l	
 
screen = pygame.display.set_mode((1000,300))
	# Create an object called MMA7455
MMA7455 = Accel()

# Get the value from it
for a in range(1000):
    Aval= MMA7455.getValue()
    print Aval,a
    Aval=Aval+128
    if (Aval >255):
        Aval=Aval-255
    screen.set_at((a,Aval),(255,255,255))
    pygame.display.flip()