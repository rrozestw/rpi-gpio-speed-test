/*
 * Test the speed of GPIO's on a Raspberry Pi using direct hardware access
 * (mem map).
 *
 * Note that RPi1 and RPi2 has different address and you need to add/remove
 * the correct define.
 *
 * Original code is an example from http://elinux.org/RPi_GPIO_Code_Samples
 * 
 * Uses GPIO 21
 */

// Use this for RPi1
//#define BCM2708_PERI_BASE        0x20000000 
// Use this for RPi2
#define BCM2708_PERI_BASE        0x3F000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

// GPIO setup macros.
#define INP_GPIO(pin) *(gpio+((pin)/10)) &= ~(7<<(((pin)%10)*3))
#define OUT_GPIO(pin) *(gpio+((pin)/10)) |=  (1<<(((pin)%10)*3))
#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

int  mem_fd;
void *gpio_map;

// I/O access
volatile unsigned *gpio;

/*
 * Set up a memory regions to access GPIO
 */
void setup_io()
{
   /* open /dev/mem */
   if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
      printf("can't open /dev/mem \n");
      exit(-1);
   }

   /* mmap GPIO */
   gpio_map = mmap(
      NULL,             //Any adddress in our space will do
      BLOCK_SIZE,       //Map length
      PROT_READ|PROT_WRITE,// Enable reading & writting to mapped memory
      MAP_SHARED,       //Shared with other processes
      mem_fd,           //File to map
      GPIO_BASE         //Offset to GPIO peripheral
   );

   close(mem_fd); //No need to keep mem_fd open after mmap

   if (gpio_map == MAP_FAILED) {
      printf("mmap error %d\n", (int)gpio_map);//errno also set!
      exit(-1);
   }

   // Always use volatile pointer!
   gpio = (volatile unsigned *)gpio_map;
}

int main(int argc, char **argv)
{
  // Set up gpi pointer for direct register access
  setup_io();

  // Switch to output mode, must use INP_GPIO before we can use OUT_GPIO
  INP_GPIO(21); 
  OUT_GPIO(21);

  // Set high, set low, repeat.
  while (1)
  {
       GPIO_SET = 1<<21;
       GPIO_CLR = 1<<21;
  }

  return 0;
}
