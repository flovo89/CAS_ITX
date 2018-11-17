/*
 ***************************************************************************
 * \brief   Embedded Linux Framebuffer Infos
 *	    Prints the framebuffer information to a console.
 * \file    appFramefufferShapes.c
 * \version 1.0
 * \date    28.10.2013
 * \author  Martin Aebersold
 *
 * \remark  Last Modifications:
 * \remark  V1.0, AOM1, 28.10.2013
 ***************************************************************************
 */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <fcntl.h>

#include <math.h>

#include <linux/fb.h>

#include <sys/mman.h>
#include <sys/ioctl.h>

#include <stdbool.h>
#include <errno.h>

/*
 ***************************************************************************
 * Define some data types
 ***************************************************************************
 */

typedef signed char INT8;
typedef unsigned char UINT8;

typedef signed short INT16;
typedef unsigned short UINT16;

typedef signed int INT32;
typedef unsigned int UINT32;

/************************************************************************/
/* VARS									*/
/************************************************************************/

/* Screen Info */
struct fb_var_screeninfo fbVarScreenInfo;
struct fb_fix_screeninfo fbFixScreenInfo;

static int fb_fd = 0;

/*
 ******************************************************************************
 * main
 ******************************************************************************
 */

int main(int argc, char *argv[])
 {
  printf("\nFramebuffer video parameters\n");
  printf("*****************************\n");

  /* Open the file for reading and writing */
  fb_fd = open("/dev/fb0", O_RDONLY);
  if (fb_fd == -1)
   {
    perror("Error: cannot open framebuffer device");
    exit(1);
   }

  printf("The framebuffer device was opened successfully.\n");

  /* Get fixed and variable screen information */
  if (ioctl(fb_fd, FBIOGET_FSCREENINFO, &fbFixScreenInfo) == -1)
   {
    perror("Error reading fixed information");
    close(fb_fd);
    exit(2);
   }
  printf("\nFixed screen information\n");
  printf("*************************\n");
  printf("Physical fb memory start:         0x%lX\n", fbFixScreenInfo.smem_start);
  printf("Length:                           %u\n", fbFixScreenInfo.smem_len);

  switch (fbFixScreenInfo.type)
   {
    case FB_TYPE_PACKED_PIXELS:
     printf("Type:                             Packed Pixels\n");
    break;

    case FB_TYPE_PLANES:
     printf("Type:                              Non interleaved planes\n");
    break;
	
    case FB_TYPE_INTERLEAVED_PLANES:
     printf("Type:                              Interleaved planes\n");
    break;

    case FB_TYPE_TEXT:
     printf("Type:                              Text/attributes\n");
    break;

    case FB_TYPE_VGA_PLANES:
     printf("Type:                              EGA/VGA planes\n");
    break;

    default: printf("Type:                      illegal\n\n");
   }

  switch (fbFixScreenInfo.type_aux)
   {
     case FB_AUX_TEXT_MDA:
      printf("Type aux:                         Monochrome text\n");
     break;
	
     default: 
      printf("type aux(%d):                     illegal\n", fbFixScreenInfo.type_aux);
    }
   
   switch (fbFixScreenInfo.visual)
    {
     case FB_VISUAL_MONO01:
      printf("Visual:                           Monochr. 1=Black 0=White\n");
     break;

     case FB_VISUAL_MONO10:
      printf("Visual:                           Monochr. 1=White 0=Black\n");
     break;

     case FB_VISUAL_TRUECOLOR:
      printf("Visual:                           True color\n");
     break;

     case FB_VISUAL_PSEUDOCOLOR:
      printf("Visual:                           Pseudo color (like atari)\n");
     break;
 
     case FB_VISUAL_DIRECTCOLOR:
      printf("Visual:                           Direct color\n");
     break;

     case FB_VISUAL_STATIC_PSEUDOCOLOR:
      printf("Visual:                           Pseudo color readonly\n");
     break;

     default:
      printf("Type visual(%d): illegal\n", fbFixScreenInfo.visual);
    }

   printf("Xpanstep:                         %u\n",  fbFixScreenInfo.xpanstep);
   printf("Ypanstep:                         %u\n",  fbFixScreenInfo.ypanstep);
   printf("Ywrapstep:                        %u\n",  fbFixScreenInfo.ywrapstep);
   printf("Line length:                      %u\n",  fbFixScreenInfo.line_length);
   printf("Memory mapped IO memory start:    %lx\n", fbFixScreenInfo.mmio_start);
   printf("Length:                           %u\n",  fbFixScreenInfo.mmio_len);
   printf("Access:                           %u\n",  fbFixScreenInfo.accel);

   if (ioctl(fb_fd, FBIOGET_VSCREENINFO, &fbVarScreenInfo) == -1)
    {
     perror("Error reading variable information");
     close(fb_fd);
     exit(3);
    }

   printf("\nVariable screen information\n");
   printf("****************************\n");
   printf("Visible resolution:               [xres: %u; yres: %u]\n", fbVarScreenInfo.xres, fbVarScreenInfo.yres);
   printf("Virtual resolution:               [xres: %u; yres: %u]\n", fbVarScreenInfo.xres_virtual, fbVarScreenInfo.yres_virtual);
   printf("Offset from virtual to visible:   [xofs: %u; yofs: %u]\n", fbVarScreenInfo.xoffset, fbVarScreenInfo.yoffset);
   printf("Red   bitfield:                   [ofs: %u; len: %u; msgRight: %u]\n", fbVarScreenInfo.red.offset, fbVarScreenInfo.red.length, fbVarScreenInfo.red.msb_right);
   printf("Green bitfield:                   [ofs: %u;  len: %u; msgRight: %u]\n", fbVarScreenInfo.green.offset, fbVarScreenInfo.green.length, fbVarScreenInfo.green.msb_right);
   printf("Blue  bitfield:                   [ofs: %u;  len: %u; msgRight: %u]\n", fbVarScreenInfo.blue.offset, fbVarScreenInfo.blue.length, fbVarScreenInfo.blue.msb_right);
   printf("Greyscale:                        %u\n", fbVarScreenInfo.grayscale);
   printf("Bits per pixel:                   %u\n", fbVarScreenInfo.bits_per_pixel);
   printf("Activate:                         %u\n", fbVarScreenInfo.activate);
   printf("Picture in mm:                    [height: %u; width: %u]\n", fbVarScreenInfo.height, fbVarScreenInfo.width);
   printf("Accel_flags:                      %u\n", fbVarScreenInfo.accel_flags);
   printf("Non standard pixel format:        %u\n\n", fbVarScreenInfo.nonstd);

   printf("Timing information\n");
   printf("******************\n");
   printf("Pixel clock:                      %u\n", fbVarScreenInfo.pixclock);
   printf("Time from sync to picture(left):  %u\n", fbVarScreenInfo.left_margin);
   printf("Time from picture to sync(right): %u\n", fbVarScreenInfo.right_margin);
   printf("Time from sync to picture(upper): %u\n", fbVarScreenInfo.upper_margin);
   printf("Time from picture to sync(lower): %u\n", fbVarScreenInfo.lower_margin);
   printf("Length of horizontal sync:        %u\n", fbVarScreenInfo.hsync_len);
   printf("Length of vertical   sync:        %u\n", fbVarScreenInfo.vsync_len);

   switch (fbVarScreenInfo.sync)
    {
      case FB_SYNC_HOR_HIGH_ACT:
       printf("Sync:                         horizontal sync high active\n");
      break;

      case FB_SYNC_VERT_HIGH_ACT:
       printf("Sync:                         vertical sync high active\n");
      break;

      case FB_SYNC_EXT:
       printf("Sync:                         external sync\n");
      break;

      case FB_SYNC_COMP_HIGH_ACT:
       printf("Sync:                         composite sync high active\n");
      break;

      case FB_SYNC_BROADCAST:
       printf("Sync:                         broadcast video timings\n");
      break;

      case FB_SYNC_ON_GREEN:
       printf("Sync:                         sync on green\n");
      break;
     
      default:
       printf("Sync(%d):                          illegal\n", fbVarScreenInfo.sync);
   }

  printf("\n");
  switch (fbVarScreenInfo.vmode)
   {
    case FB_VMODE_NONINTERLACED:
     printf("Vmode:                            non interlaced\n");
    break;

    case FB_VMODE_INTERLACED:
     printf("Vmode:                            interlaced\n");
    break;

    case FB_VMODE_DOUBLE:
     printf("Vmode:                            double scan\n");
    break;

    default:
     printf("Vmode(%d):                        illegal\n", fbVarScreenInfo.vmode);
   }
  printf("Rotate:                           %u\n\n", fbVarScreenInfo.rotate);
  close(fb_fd);
  return 0;
 }

