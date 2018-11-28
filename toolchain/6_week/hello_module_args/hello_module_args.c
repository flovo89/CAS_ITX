/*
 ***************************************************************************
 * \brief   Embedded Linux Exercise 6.2
 *	    This is a simple kernel module for the BBB-BFH-Cape.
 * \file    mod_hello_args.c
 * \version 1.0
 * \date    28.12.2013
 * \author  Martin Aebersold
 *
 *  Load the module with command line arguments: 
 *  $ sudo modprobe hello_module_args howmany=5 whom="Begalebone-Black"
 *  
 *  Unload the module with:
 *  $ sudo modprobe -r hello_module_args 
 *
 * \remark  Last Modifications:
 * \remark  V1.0, AOM1, 28.12.2013
 ***************************************************************************
 *
 * Copyright (C) 2015 Martin Aebersold, Bern University of Applied Scinces
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#include <linux/version.h>	/* Distribution and kernel version */
#include <linux/module.h>	/* Kernel module stuff and macros */
#include <linux/kernel.h>	/* Kernel prog stuff : kprintk, types, ... */
#include <linux/init.h> 	/* Required for module_{init,exit}  */
#include <linux/moduleparam.h>	/* For kernel commandline parameter */

#define MOD_LICENSE 		"GPL"
#define MOD_AUTHOR 		"Florian Vogel  <flovo89@hotmail.com>"
#define MOD_DESCRIPTION 	"Simple hello device driver"
#define MODULE_NAME 		"hello_args"

static int howmany = 1;
static char *whom = "world";

/* Setup for argument passing */
module_param(howmany, int, S_IRUGO);
module_param(whom, charp, S_IRUGO); 

/* Command line arguments */
MODULE_PARM_DESC(howmany, "number of times to greet");   
MODULE_PARM_DESC(whom, "whom to greet"); 

/************************************************************************/
/* Module initialization						*/
/************************************************************************/

static int __init hello_init(void)
 {
  int i;

  for (i=0; i<howmany; i++)
   printk(KERN_ALERT "(%d) Hello, %s\n", i, whom);
  return 0;
 }

/************************************************************************/
/* Module cleanup							*/
/************************************************************************/

static void __exit hello_exit(void)
 {
  printk(KERN_ALERT "Goodbye, %s\n", whom);
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

