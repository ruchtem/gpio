#!/bin/bash

sudo su -
echo "18" > /sys/class/gpio/export
echo "out" > /sys/class/gpio/gpio18/direction

echo "23" > /sys/class/gpio/export
echo "out" > /sys/class/gpio/gpio23/direction

echo "24" > /sys/class/gpio/export
echo "out" > /sys/class/gpio/gpio24/direction
exit
