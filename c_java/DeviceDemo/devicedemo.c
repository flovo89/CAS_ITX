/* general control */

/*****************************************************************************/
/*  Module     : Device Demo                                    Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : This just shows the use of functionspointer and direct      */
/*               initializers, in the form of a simple device demonstration  */
/*                                                                           */
/*  Procedures : main                                                        */
/*                                                                           */
/*  Author     : I. Oesch                                                    */
/*                                                                           */
/*  History    : 01.03.2015  IO Created                                      */
/*               16.05.2017  IO Upgraded by comments                         */
/*                                                                           */
/*  File       : devicedemo.c                                                */
/*                                                                           */
/*****************************************************************************/
/* MagicSoft                                                                 */
/*****************************************************************************/

/* imports */
#include <stdio.h>
#include <stdlib.h>

#include "devicemanager.h"

/* module constant declaration */
#define BUFFER_LENGTH 10

/* module type declaration */

/* module data declaration */

/* module procedure declaration */

/*****************************************************************************/
/*  Procedure   : main                                                       */
/*****************************************************************************/
/*                                                                           */
/*  Function    : This is the main program, it just opens two different      */
/*                'Devices' and uses them, just to test and demonstrate      */
/*               the devices                                                 */
/*                                                                           */
/*  Type        : Global                                                     */
/*                                                                           */
/*  Input Para  : argc   Number of comandline arguments                      */
/*                argv   Vector with commandline arguments                   */
/*                                                                           */
/*  Output Para : Errorcode to operatingsystem                               */
/*                                                                           */
/*                                                                           */
/*  Author      : I. Oesch                                                   */
/*                                                                           */
/*  History    : 01.03.2015  IO Created                                      */
/*               16.05.2017  IO Upgraded by comments                         */
/*                                                                           */
/*****************************************************************************/
int main(int argc, char *argv[])
{
   /* procedure data */
   Info *Device;
   char Buffer[BUFFER_LENGTH];

   /* procedure code */

   /* Just open a device and write something on sucess */
   Device = OpenDevice("DeviceB", "Hans");
   if (Device != NULL) {
     WriteDevice(Device, "Hallo");
     int Length = ReadDevice(Device, Buffer, BUFFER_LENGTH);
     if ((Length < 0) || (Length >= BUFFER_LENGTH)) {
        Length = 0;
     }
     Buffer[Length] = 0;
     printf("<Read [%s]>\n", Buffer);
     CloseDevice(Device);
  }

   /* Just open another device and write something on sucess */
  Device = OpenDevice("DeviceA", "Fritz");
  if (Device != NULL) {
     WriteDevice(Device, "Welt");
     int Length = ReadDevice(Device, Buffer, BUFFER_LENGTH);
     if ((Length < 0) || (Length >= BUFFER_LENGTH)) {
        Length = 0;
     }
     Buffer[Length] = 0;
     printf("<Read [%s]>\n", Buffer);
	 CloseDevice(Device);
  }
  
  //system("PAUSE");	
  return 0;
}
/*****************************************************************************/
/*  End         : main                                                       */
/*****************************************************************************/

/*****************************************************************************/
/*  End Module  : Device Demo                                                */
/*****************************************************************************/


