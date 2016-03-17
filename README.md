# GPIO Speed Test on a Raspberry Pi
Using a 3.5" screen using up more than half the I/O I was wondering if it was possible to use bitbanging to send data through one of the GPIO's. Since I have also a few RPi 3's it was interesting to test these. I use Raspbian on RPi2 but I use Ubuntu Mate on the v.3. It would be interesting to do the same setup on with the same hardware and os version in the future, although I don't expect it to make a big difference.

## Setup
Raspberry Pi 2 | Raspberry Pi 3
-------------- | --------------
Raspian Jessie | Ubuntu Mate (32bit)
A 3.5" Screen. | No Screen
No overclocking (all voltages = 1.2000V, arm_freq = 700) | No overclocking (All voltages 1.2000v, freq=1200)

* Using GPIO 21
* Using GCC's speed optimization -Ofast (same as -O3 but with a few more quirks)
* Oscilloscope (100MHz)

## Conclusion
Using memmapping direct to the hardware is much, much faster than using sysfs. The direct access method was able to write to the port at over 40MHz, the nearest sysfs came (using C) was 8.6Khz. The shell using sysfs was the slowest at 5.23Khz.

It did not seem to vary much between no speed optimization and -O3 and -Ofast, biggest difference was on direct access method, but it seemed like the sysfs method run more stable (the same KHz) and did not "sway" as much.

Tests | RPi 2 | RPi 3
------|------ | -----
Shell | 5.23KHz | 13.7KHz     
sysfs | 8.20KHz | 21KHz 
HW    | 40MHz   | 66.7MHz 

## Raspberry Pi 2 tests
### Using sysfs through standard Shell
I wanted a baseline, and was curious how fast the shell was, but even if it was really stable at 5.23KHz it is a little to slow to be used with some GPS and Blutooth modules.

![alt text](rpi2-speed-test-using-shell.png "Using standard Shell RPi2")

### Using sysfs through C 
Was very disapointed about the performance using sysfs, although the speed almost doubled from using the shell, I hoped it would be much higher.

![alt text](rpi2-speed-test-using-sys.png "Using sysfs RPi2")

### Using the direct access method
At 40+ MHz the RPi was having problem with producing a clean signal, I tried different cables hoping that would solve it (including shorter cables). I did not try to raise the voltage on the Pi, but it could help (more voltage = faster transistor speeds). I don't have anything I have to communicate with at 40MHz :), this will give me huge headroom. Didn't think that it would be this big of a difference!

![alt text](rpi2-speed-test-using-hw.png "Using direct access to hw RPi2")


## Raspberry Pi 3 tests
### Using sysfs through standard Shell
RPi 3 seems to deliver almost three times the performance over RPi 2, around 13.7KHz.

![alt text](rpi3-speed-test-using-shell.png "Using standard Shell")

### Using sysfs through C 
Almost the same result as with the shell, almost three times the performance, clocking out at 21KHz.

![alt text](rpi3-speed-test-using-sys.png "Using sysfs")

### Using the direct access method
66.7 MHz but as you see the trace doesnt look like a square wave anymore due to different factors.

![alt text](rpi3-speed-test-using-hw.png "Using direct access to hw")
