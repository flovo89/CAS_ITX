/*
 ***************************************************************************
 * \brief   Embedded Linux Exercise 6.1
 *	    This is a simple kernel module.
 * \file    hello_module.c
 * \version 1.0
 * \date    28.12.2013
 * \author  Martin Aebersold
 *
 *  Load the module with: 
 *  $ sudo modprobe hello_module
 *  
 *  Unload the module with:
 *  $ sudo modprobe -r hello_module
 *
 * \remark  Last Modifications:
 * \remark  V1.0, AOM1, 28.12.2013
 ***************************************************************************
 */

#include <linux/version.h>	/* Distribution and kernel version */
#include <linux/module.h>	/* Kernel module stuff and macros */

#define MOD_LICENSE 		"GPL"
#define MOD_AUTHOR 		"Martin Aebersold  <martin.aebersold@bfh.ch>"
#define MOD_DESCRIPTION 	"Simple hello device driver"
#define MODULE_NAME 		"hello"

/************************************************************************/
/* Module initialization						*/
/************************************************************************/

static int __init hello_init(void)
 {
  printk("Hello: This is my first kernel module\n");
  return 0;
 }

/************************************************************************/
/* Module cleanup							*/
/************************************************************************/

static void __exit hello_exit(void)
 {
   printk("Goodbye, unloading the hello module\n");
 }

/************************************************************************/
/* Driver init and exit entry points					*/
/************************************************************************/

module_init(hello_init);
module_exit(hello_exit);

/************************************************************************/
/* Module info								*/
/************************************************************************/

MODULE_LICENSE(MOD_LICENSE);
MODULE_DESCRIPTION(MOD_DESCRIPTION);
MODULE_AUTHOR(MOD_AUTHOR);

