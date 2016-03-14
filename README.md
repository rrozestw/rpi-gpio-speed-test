# GPIO Speed Test on a Raspberry Pi 2
Using a 3.5" screen using up more than half the I/O I was wondering if it was possible to use bitbanging to send data through one of the GPIO's. Since I haven't used C much on the RPi I found some examples on a wiki that I modified to test the speed using sysfs or direct hw access (mem).

## Setup
* Raspberry Pi 2, using GPIO 21
* A 3.5" Screen.
* Oscilloscope (100MHz)
* No overclocking
** all voltages = 1.2000V
** arm_freq = 700

## Conclusion
Using memmapping direct to the hardware is much, much faster than using sysfs. The direct access method was able to write to the port at over 40MHz, the nearest sysfs came (using C) was 8.6Khz. The shell using sysfs was the slowest at 5.23Khz.

## Using sysfs through standard Shell
I wanted a baseline, and was curious how fast the shell was, but even if it was really stable at 5.23KHz it is a little to slow to be used with some GPS and Blutooth modules.
![alt text](rpi2-speed-test-using-shell.png "Using standard Shell")

## Using sysfs through C 
![alt text](rpi2-speed-test-using-sysfs.png "Using sysfs")

## Using the direct access method
At 40+ MHz the RPi was having problem with producing a clean signal, I tried different cables hoping that would solve it (including shorter cables). I did not try to overclock the 
![alt text](rpi2-speed-test-using-hw.png "Using direct access to hw")
