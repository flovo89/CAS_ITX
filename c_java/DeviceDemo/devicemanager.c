/* general control */

/*****************************************************************************/
/*  Module     : Devicemanager                                  Version 1.0  */
/*****************************************************************************/
/*                                                                           */
/*  Function   : This module manages the different devices in our system.    */
/*               Currently it just manages two hardcoded devices, to be      */
/*               more realistic, devices should be added and removed         */
/*               dynamically                                                 */
/*                                                                           */
/*  Procedures : ReadDevice()                                                */
/*               OpenDevice()                                                */
/*               WriteDevice()                                               */
/*               ReadDevice()                                                */
/*                                                                           */
/*  Author     : I. Oesch                                                    */
/*                                                                           */
/*  History    : 01.03.2015  IO Created                                      */
/*               16.05.2017  IO Upgraded by comments                         */
/*                                                                           */
/*  File       : devicemanager.c                                             */
/*                                                                           */
/*****************************************************************************/
/* MagicSoft                                                                 */
/*****************************************************************************/

/* imports */
#include "devicemanager.h"
#include "deviceA.h"
#include "deviceB.h"

#include <string.h>

/* module constant declaration */

/* module type declaration */

/* module data declaration */

/* Table of registered devices, should be dynamic to */
/* be more realistic                                 */
static Device *DeviceTable[] =
{
       &DeviceA,
       &DeviceB,
       NULL  // NULL Marks end of Table
};


/* module procedure declaration */

       
/*****************************************************************************/
/*  Procedure   : OpenDevice                                                 */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Opens the requested device by looking up its name in the   */
/*                device table. Returns a pointer to a device descriptor on  */
/*                success, NULL otherwise.                                   */
/*                                                                           */
/*  Type        : Global                                                     */
/*                                                                           */
/*  Input Para  : Device    Name of device                                   */
/*                Name      Name of service / file / channel of device       */
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
Info *OpenDevice(char *Device, char *Name) 
{
   /* procedure data */
   int i;

   /* procedure code */

   /* Look for the Device in the table */
   for (i = 0; DeviceTable[i] != NULL; i++) {
      if (strcmp(Device, DeviceTable[i]->Name) == 0) {

         /* Open the device an return its descriptor if found */
         return DeviceTable[i]->Open(Name);
      } 
   } 
   /* Unknown device, return faillure */
   return NULL;
}
/*****************************************************************************/
/*  End         : OpenDevice                                                 */
/*****************************************************************************/

/*****************************************************************************/
/*  Procedure   : CloseDevice                                                */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Just closes the given device.                              */
/*                                                                           */
/*  Type        : Global                                                     */
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
void CloseDevice(Info *Device) 
{
   /* procedure data */

   /* procedure code */
   /* just propagate the call on valid device */
   if (Device != NULL) {
      Device->MyDevice->Close(Device);
   }
}
/*****************************************************************************/
/*  End         : CloseDevice                                                */
/*****************************************************************************/

/*****************************************************************************/
/*  Procedure   : WriteDevice                                                */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Just propagates the write command to the given device      */
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
void WriteDevice(Info *Device, char *Data) 
{
   /* procedure data */

   /* procedure code */

   /* just propagate the call on valid device */
   if (Device != NULL) {
      Device->MyDevice->Write(Device, Data);
   }
}
/*****************************************************************************/
/*  End         : WriteDevice                                                */
/*****************************************************************************/

/*****************************************************************************/
/*  Procedure   : ReadDevice                                                 */
/*****************************************************************************/
/*                                                                           */
/*  Function    : Just propagates the write command to the given device      */
/*                                                                           */
/*  Type        : Global                                                     */
/*                                                                           */
/*  Input Para  : Device    Pointer to device descriptor                     */
/*                Buffer    Buffer to write read datas into                  */
/*                Length    Length of Buffer, do not read more Bytes         */
/*                                                                           */
/*  Output Para : Number of Bytes actually read                              */
/*                                                                           */
/*                                                                           */
/*  Author      : I. Oesch                                                   */
/*                                                                           */
/*  History    : 01.03.2015  IO Created                                      */
/*               16.05.2017  IO Upgraded by comments                         */
/*                                                                           */
/*****************************************************************************/
int ReadDevice(Info *Device, char *Buffer, int Length)
{
   /* procedure data */

   /* procedure code */

   /* just propagate the call on valid device */

   if (Device != NULL) {
      return Device->MyDevice->Read(Buffer, Length);
   }

   return 0;
}
/*****************************************************************************/
/*  End         : ReadDevice                                                 */
/*****************************************************************************/

/*****************************************************************************/
/*  End Module  : Devicemanager                                              */
/*****************************************************************************/
