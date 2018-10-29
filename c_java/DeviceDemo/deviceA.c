/* general control */

/*****************************************************************************/
/*  Module     : Device A                                       Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : This module just implements a dummy device for              */
/*               demonstration purposes.                                     */
/*                                                                           */
/*  Procedures : - (Only local functions)                                    */
/*                                                                           */
/*  Author     : I. Oesch                                                    */
/*                                                                           */
/*  History    : 01.03.2015  IO Created                                      */
/*               16.05.2017  IO Upgraded by comments                         */
/*                                                                           */
/*  File       : devicea.c                                                   */
/*                                                                           */
/*****************************************************************************/
/* MagicSoft                                                                 */
/*****************************************************************************/

/* imports */
#include "devicemanager.h"
#include "deviceA.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* module constant declaration */

/* module type declaration */

/* module procedure declaration */
static Info *OpenDeviceA(char *Name);
static void WriteDeviceA(Info* Device, char *Data);
static void CloseDeviceA(Info* Device);

/* module data declaration */

/* Device descriptor for our device with pointer */
/* to our management functions                   */
Device DeviceA = {
       .Name = "DeviceA",
       .Write = WriteDeviceA,
       .Open  = OpenDeviceA,
       .Close = CloseDeviceA
};

/*****************************************************************************/
/*  Procedure   : OpenDeviceA                                                */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Opens the device by creating and initializing a device     */
/*                descriptor.                                                */
/*                Returns a pointer to the device descriptor on success,     */
/*                NULL otherwise.                                            */
/*                                                                           */
/*  Type        : Local                                                      */
/*                                                                           */
/*  Input Para  : Name      Name of service / file / channel of device       */
/*                                                                           */
/*  Output Para : Pointer to device descriptor or NULL on faillure           */
/*                                                                           */
/*                                                                           */
/*  Author      : I. Oesch                                                   */
/*                                                                           */
/*  History    : 01.03.2015  IO Created                                      */
/*               16.05.2017  IO Upgraded by comments                         */
/*                                                                           */
/*****************************************************************************/
static Info *OpenDeviceA(char *Name) 
{
   /* procedure data */

   /* procedure code */

   /* Create an initialize Device descriptor */
   Info* Device = malloc(sizeof(Info));

   if (Device != NULL) {
      /* use our functions by using our device function table */
      Device->MyDevice = &DeviceA;
      strncpy(Device->Name, Name, 18);
      printf("DeviceA Opening <%s>\n", Device->Name);
   }
   return Device;
}
/*****************************************************************************/
/*  End         : OpenDeviceA                                                */
/*****************************************************************************/

/*****************************************************************************/
/*  Procedure   : CloseDeviceA                                               */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Just closes the device.                                    */
/*                                                                           */
/*  Type        : Local                                                      */
/*                                                                           */
/*  Input Para  : Device    Pointer to device descriptor                     */
/*                                                                           */
/*  Output Para : None                                                       */
/*                                                                           */
/*                                                                           */
/*  Author      : I. Oesch                                                   */
/*                                                                           */
/*  History    : 01.03.2015  IO Created                                      */
/*               16.05.2017  IO Upgraded by comments                         */
/*                                                                           */
/*****************************************************************************/
static void CloseDeviceA(Info* Device)
{
   /* procedure data */

   /* procedure code */

   /* Just release the descriptor... */
   printf("DeviceA Closing <%s>\n", Device->Name);
   free(Device);
}
/*****************************************************************************/
/*  End         : CloseDeviceA                                               */
/*****************************************************************************/

/*****************************************************************************/
/*  Procedure   : WriteDeviceA                                                */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Just writes the text as devices output                     */
/*                                                                           */
/*  Type        : Global                                                     */
/*                                                                           */
/*  Input Para  : Device    Pointer to device descriptor                     */
/*                Data      Pointer to string to be written                  */
/*                                                                           */
/*  Output Para : None                                                       */
/*                                                                           */
/*                                                                           */
/*  Author      : I. Oesch                                                   */
/*                                                                           */
/*  History    : 01.03.2015  IO Created                                      */
/*               16.05.2017  IO Upgraded by comments                         */
/*                                                                           */
/*****************************************************************************/
static void WriteDeviceA(Info* Device, char *Data) 
{
    /* procedure data */

    /* procedure code */

   printf("DeviceA <%s>: %s\n", Device->Name, Data);
}
/*****************************************************************************/
/*  End         : WriteDeviceA                                               */
/*****************************************************************************/

/*****************************************************************************/
/*  End Module  : Device A                                                   */
/*****************************************************************************/


