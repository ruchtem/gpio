#!/bin/bash

sudo su -
echo "18" > /sys/class/gpio/unexport
echo "23" > /sys/class/gpio/unexport
echo "24" > /sys/class/gpio/unexport
exit
