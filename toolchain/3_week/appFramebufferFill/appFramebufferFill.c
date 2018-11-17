/*
 *****************************************************************************
 * \brief   Embedded Linux Framebuffer Exercise 1.0
 *	    Basic framebuffer application.
 *	    Only a minimal error handling is implemented.
 *
 * \file    appFrameBufferFill.c
 * \version 1.0
 * \date    28.09.2008
 * \author  Martin Aebersold
 *
 * \remark  Last Modifications:
 * \remark  V1.0, AOM1, 28.10.2013
 * \remark  Changed color size from 16BPP to 24BPP, aom1 27. 10. 2018
 *
 *****************************************************************************
 *
 * Copyright (C) 2013 Martin Aebersold, Bern University of Applied Scinces
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 ******************************************************************************
 *
 * Disable blinking console cursor
 * --------------------------------
 * @target sudo su
 * @target echo 0 > /sys/class/graphics/fbcon/cursor_blink
 * @target exit
 *
 ******************************************************************************
 */

/******************************************************************************/
/* Includes								      */
/******************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include <linux/fb.h>

#include <sys/mman.h>
#include <sys/ioctl.h>

/******************************************************************************/
/* Macros								      */
/******************************************************************************/

#define CONVERT_RGB24(red, green, blue) \
	    ((red<<16) | (green<<8) | (blue))

/******************************************************************************/
/* Define some constants						      */
/******************************************************************************/

#define	BPP32	32

/*
 * Color definitions   	        R    G    B
 */

#define BLACK	CONVERT_RGB24(  0,   0,   0)
#define RED	CONVERT_RGB24(255,   0,   0)
#define GREEN	CONVERT_RGB24(  0, 255,   0)
#define YELLOW	CONVERT_RGB24(255, 255,   0)
#define BLUE	CONVERT_RGB24(  0,   0, 255)
#define MAGENTA	CONVERT_RGB24(255,   0, 255)
#define CYAN	CONVERT_RGB24(  0, 255, 255)
#define GREY	CONVERT_RGB24(192, 192, 192)
#define WHITE	CONVERT_RGB24(255, 255, 255)

/******************************************************************************/
/* Define some data types						      */
/******************************************************************************/

struct RGB_COLOR
 {
  uint8_t r;
  uint8_t g;
  uint8_t b;
 };

/******************************************************************************/
/* Static Variables							      */
/******************************************************************************/

/* Screen Info */
static struct fb_var_screeninfo fbVarScreenInfo;

static uint16_t y;
static uint16_t x;

static int32_t  *pfb32;

/******************************************************************************/
/* Global Variables							      */
/******************************************************************************/

uint32_t fbfd;
uint32_t screensize;

/******************************************************************************/
/* main()								      */
/******************************************************************************/
void drawCircle(int posX, int posY, int radius)
{
	int x = 0; 
	int y = 0;

	for (y = 0; y<fbVarScreenInfo.yres; y++) { 
            	for (x = 0; x<fbVarScreenInfo.xres; x++) { 
			int a = abs((posX - x) * (posX - x));
			int b = abs((posY - y) * (posY - y));

			int c = abs(a + b);
			int d = abs(radius * radius);

                	// checking if the formula stands correct at each coordinate scanned
                	if ( c == d) {
                    	pfb32[x + y * fbVarScreenInfo.xres] = BLUE; 
                	} 
            	}  
       	 } 
}

int main(int argc, char *argv[])
 {
  int32_t fbfd = 0;
  int32_t screensize = 0;

  printf("FireFly-BFH-Cape Framebuffer Test\n");

  /*
   * Open device file for reading and writing
   */
  fbfd = open("/dev/fb0", O_RDWR);
  if (fbfd == -1)
   {
    perror("Error: cannot open framebuffer device");
    exit(errno);
   }
  printf("The framebuffer device was opened successfully.\n");

  /*
   * Get variable screen information
   */
  if (ioctl(fbfd, FBIOGET_VSCREENINFO, &fbVarScreenInfo) == -1)
   {
    perror("Error reading variable information");
    close(fbfd);
    exit(errno);
   }

  /* Figure out the size of the screen in bytes */
  screensize = (fbVarScreenInfo.xres * fbVarScreenInfo.yres * fbVarScreenInfo.bits_per_pixel) / 8;

  /*
   * Map the frame buffer device memory to user space.
   * Starting address in user space is pfb32.
   */
   if (fbVarScreenInfo.bits_per_pixel == BPP32)
    {
     pfb32 = (int32_t*) mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
     if (pfb32 == (int32_t*) -1)
      {
       perror("Error: failed to map 32-BPP framebuffer device to memory");
       exit(errno);
      }

     /* Fill the screen with 24 bpp, do it for all [x,y] pixel with the desired color	*/
     for (y=0; y<fbVarScreenInfo.yres; y++)
      {
       for (x=0; x<fbVarScreenInfo.xres; x++)
        {
         pfb32[x + y * fbVarScreenInfo.xres] = RED;
        }
      }
	int posX = fbVarScreenInfo.xres / 2;
	int posY = fbVarScreenInfo.yres / 2;
	int radius = 50;
	drawCircle(posX, posY, radius);

     /* Cleanup */
     munmap(pfb32, screensize);
     close(fbfd);
    }
  return 0;
 }

