# GPIO Speed Test on a Raspberry Pi 2
Using a 3.5" screen using up more than half the I/O I was wondering if it was possible to use bitbanging to send data through one of the GPIO's. Since I haven't used C much on the RPi I found some examples on a wiki that I modified to test the speed using sysfs or direct hw access (mem).

## Setup
* Raspberry Pi 2, using GPIO 21
* A 3.5" Screen.
* Oscilloscope (100MHz)
* No overclocking (all voltages = 1.2000V, arm_freq = 700)
* Using GCC's speed optimization -Ofast (same as -O3 but with a few more quirks)

## Conclusion
Using memmapping direct to the hardware is much, much faster than using sysfs. The direct access method was able to write to the port at over 40MHz, the nearest sysfs came (using C) was 8.6Khz. The shell using sysfs was the slowest at 5.23Khz.

It did not seem to vary much between no speed optimization and -O3 and -Ofast, biggest difference was on direct access method, but it seemed like the sysfs method run more stable (the same KHz) and did not "sway" as much.

## Using sysfs through standard Shell
I wanted a baseline, and was curious how fast the shell was, but even if it was really stable at 5.23KHz it is a little to slow to be used with some GPS and Blutooth modules.

![alt text](rpi2-speed-test-using-shell.png "Using standard Shell")

## Using sysfs through C 
Was very disapointed about the performance using sysfs, although the speed almost doubled from using the shell, I hoped it would be much higher.

![alt text](rpi2-speed-test-using-sys.png "Using sysfs")

## Using the direct access method
At 40+ MHz the RPi was having problem with producing a clean signal, I tried different cables hoping that would solve it (including shorter cables). I did not try to raise the voltage on the Pi, but it could help (more voltage = faster transistor speeds). I don't have anything I have to communicate with at 40MHz :), this will give me huge headroom. Didn't think that it would be this big of a difference!

![alt text](rpi2-speed-test-using-hw.png "Using direct access to hw")
