import time
from gpiozero import LED

red = LED(18)
yellow = LED(23)
green = LED(24)

print("LEDs on")
red.on()
yellow.on()
green.on()

print("Wait for one second")
time.sleep(1)

print("LEDs off")
red.off()
yellow.off()
green.off()
