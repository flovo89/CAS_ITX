#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H
/*****************************************************************************/
/*  Header     : Devicemanager                                  Version 1.0  */
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
/*  File       : devicemanager.h                                             */
/*                                                                           */
/*****************************************************************************/
/* MagicSoft                                                                 */
/*****************************************************************************/

/* imports */

/* module constant declaration  */

/* module type declaration      */
typedef struct DeviceInfo Info;

typedef void    (*WriteHandlerPtr)(Info* Device, char *Data);
typedef Info*   (*OpenHandlerPtr) (char *Name);
typedef void    (*CloseHandlerPtr)(Info* Device);

typedef struct Device {
   char            *Name;
   WriteHandlerPtr  Write;
   OpenHandlerPtr   Open;
   CloseHandlerPtr  Close;
} Device;

struct DeviceInfo {
   Device* MyDevice;
   char Name[20];
   void *MoreInfo;
};

/* module data declaration      */

/* module procedure declaration */
extern Info *OpenDevice(char *Device, char *Name);
extern void CloseDevice(Info *Device);
extern void WriteDevice(Info *Device, char *Data);
extern int ReadDevice(Info *Device, char *Buffer, int Length);

/*****************************************************************************/
/*  End Header  : Devicemanager                                              */
/*****************************************************************************/
#endif
