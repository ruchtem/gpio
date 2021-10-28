import os
import time
from gpiozero import Buzzer

buzzer = Buzzer(22)

def dot():
	buzzer.on()
	time.sleep(0.1)
	buzzer.off()
	time.sleep(0.2)

def dash():
	buzzer.on()
	time.sleep(0.3)
	buzzer.off()
	time.sleep(0.1)

def letterSpace():
	time.sleep(0.2)

def wordSpace():
	time.sleep(0.6)

def morseS():
	dot()
	dot()
	dot()

def morseO():
	dash()
	dash()
	dash()

os.system('clear')

print("Morse code")

loop_count = input("How many times would you like the SOS to loop? ")
loop_count = int(loop_count)

while loop_count > 0:
	morseS()
	letterSpace()
	morseO()
	letterSpace()
	morseS()
	wordSpace()

	loop_count = loop_count - 1
