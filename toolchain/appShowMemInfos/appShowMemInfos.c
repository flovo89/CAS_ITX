/*
 ***************************************************************************
 * \brief   Embedded Linux Course BTE5446
 *	    Simple program to show the amount of system memory in a console
 * \file    appShowMemInfos.c
 * \version 1.0
 * \date    19.10.2014
 * \author  Martin Aebersold
 *
 * \remark  Last Modifications:
 * \remark  V1.0, AOM1,  19.10.2014
 ***************************************************************************
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
 *   Dump Hex: $ cat /proc/cpuinfo | od -t x1
 *
 *   Escape sequences in C
 *   ---------------------
 *   Escape	Sequence	Represents 
 *   \a or 	\A  		A bell 
 *   \b or 	\B  		A backspace 
 *   \f or	\F  		A formfeed 
 *   \n or 	\N  		A new line 
 *   \r or 	\R  		A carriage return 
 *   \t or 	\T  		A horizontal tab 
 *   \v or 	\V  		A vertical tab 
 *   \xhh or 	\Xhh  		A hexadecimal bit pattern 
 *
 *   \ooo  	An octal bit pattern 
 *   \0  	A null character 
 *   \\  	A backslash (\) 
 */

/******************************************************************************/
/* Includes								      */
/******************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h> 

/******************************************************************************/
/* Defines								      */
/******************************************************************************/

#define BUFFER_SIZE	16 * 1024

/******************************************************************************/
/* main()								      */
/******************************************************************************/

int main(int argc, char **argv)
 {
   FILE* fp; 
   char buffer[BUFFER_SIZE]; 
   size_t bytes_read; 
   char* match; 

   /* Read the entire contents of /proc/meminfo into the buffer.  */ 
   fp = fopen("/proc/meminfo", "r"); 
   bytes_read = fread (buffer, 1, sizeof (buffer), fp); 
   fclose(fp); 

   /* Bail if read failed or if buffer isn't big enough.  */ 
   if ((bytes_read == 0) || (bytes_read == sizeof (buffer))) 
    {
     printf("Read failed or buffer overflow!\n");
     return -1; 
    }

   /* Null-terminated string buffer */ 
   buffer[bytes_read] = '\0'; 

   /* Finds the first occurrence of the substring "MemTotal".  */
   match = strstr(buffer, "MemTotal"); 

   /* In case no matched string is found inform user */
   if (match == NULL) 
    {
     printf("String MemTotal not found!\n");
     return -1; 
    }

   /* Parse the line to extract the "MemTotal". Read until '\n' is read --> "%[\^n]"  */
   sscanf(match, "MemTotal	:%[^\n]", (char *) &buffer);

   /* Show the running amount of system memory in a console */	
   printf("\nThe total amount of memory on your system is:%s\n\n" , buffer);

   return 0;
 } 

