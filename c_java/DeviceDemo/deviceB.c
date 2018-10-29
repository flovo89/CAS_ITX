/* general control */

/*****************************************************************************/
/*  Module     : Device B                                       Version 1.0  */
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
/*  File       : deviceb.c                                                   */
/*                                                                           */
/*****************************************************************************/
/* MagicSoft                                                                 */
/*****************************************************************************/

/* imports */
#include "devicemanager.h"
#include "deviceB.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* module constant declaration */

/* module type declaration */

/* module procedure declaration */
static Info *OpenDeviceB(char *Name);
static void WriteDeviceB(Info* Device, char *Data);
static void CloseDeviceB(Info* Device);

/* module data declaration */

/* Device descriptor for our device with pointer */
/* to our management functions                   */
Device DeviceB = {
       .Name = "DeviceB",
       .Write = WriteDeviceB,
       .Open  = OpenDeviceB,
       .Close = CloseDeviceB
};

/*****************************************************************************/
/*  Procedure   : OpenDeviceB                                                */
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
static Info *OpenDeviceB(char *Name)
{
   /* procedure data */

   /* procedure code */

   /* Create an initialize Device descriptor */
   Info* Device = malloc(sizeof(Info));

   if (Device != NULL) {
      /* use our functions by using our device function table */
      Device->MyDevice = &DeviceB;
      strncpy(Device->Name, Name, 18);
      printf("DeviceB Opening <%s>\n", Device->Name);
   }
   return Device;
}
/*****************************************************************************/
/*  End         : OpenDeviceB                                                */
/*****************************************************************************/

/*****************************************************************************/
/*  Procedure   : CloseDeviceB                                               */
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
static void CloseDeviceB(Info* Device)
{
   /* procedure data */

   /* procedure code */

   /* Just release the descriptor... */
   printf("DeviceB Closing <%s>\n", Device->Name);
   free(Device);
}
/*****************************************************************************/
/*  End         : CloseDeviceB                                               */
/*****************************************************************************/

/*****************************************************************************/
/*  Procedure   : WriteDeviceB                                                */
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
static void WriteDeviceB(Info* Device, char *Data)
{
    /* procedure data */

    /* procedure code */

   printf("DeviceB <%s>: %s\n", Device->Name, Data);
}
/*****************************************************************************/
/*  End         : WriteDeviceB                                               */
/*****************************************************************************/

/*****************************************************************************/
/*  End Module  : Device B                                                   */
/*****************************************************************************/


