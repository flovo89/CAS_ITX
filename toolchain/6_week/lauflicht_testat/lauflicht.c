/*
 ***************************************************************************
 * \brief   Embedded-Linux CAS-ITX HS2018
 *	    Linux Sysfs GPIO Exercise 1.0, Template
 *          Use this template for your apps and adjust it accordingly.
 * \file    appSysfsTemplate.c
 * \version 1.0
 * \date    25.10.2013
 * \author  Martin Aebersold
 *
 * \remark  Last Modifications:
 * \remark  V1.0, AOM1, 25.10.2013   Initial release
 * \remark  V1.1, AOM1, 20.11.2015   Added Timer Handling
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
 */

/* Declare the function prototypes headers */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/time.h>

#include <math.h>

char path0[] = "/dev/led0";
char path1[] = "/dev/led1";
char path2[] = "/dev/led2";
char path3[] = "/dev/led3";

volatile static uint32_t softTimer = 0;

/*
 ***************************************************************************
 * main
 ***************************************************************************
 */
void signal_timer_handler(int32_t signum)
{
 	if (softTimer != 0)
  	softTimer--;
}

void delay(int32_t value)
{
  	softTimer = value;
  	while (softTimer != 0);
}

int writeled(char *path, char *state)
{
	int fd = -1;
	fd = open(path, O_WRONLY);	
	if(fd < 0)
	{
		perror(path);
		return fd;
	}
	write(fd, state, strlen(state)+1);
	close(fd);
	return 0;	
}

int main(int argc, char **argv)
{
	struct itimerval timer = {{0}};

  	/* Configure the timer to expire after 10 msec... */
  	timer.it_value.tv_sec = 0;
  	timer.it_value.tv_usec = 10000;

  	/* ... and every 10 msec after that. */
  	timer.it_interval.tv_sec = 0;
  	timer.it_interval.tv_usec = 10000;

  	/* Register signal handler for periodic timer with Kernel */
  	signal(SIGALRM, &signal_timer_handler);
  	setitimer(ITIMER_REAL, &timer, NULL);

  	while (true)
   	{
		if(writeled(path0, "on") < 0) return -1;
		if(writeled(path3, "off") < 0) return -1;
		delay(100);
		if(writeled(path1, "on") < 0) return -1;
		if(writeled(path0, "off") < 0) return -1;
		delay(100);
		if(writeled(path2, "on") < 0) return -1;
		if(writeled(path1, "off") < 0) return -1;
		delay(100);
		if(writeled(path3, "on") < 0) return -1;
		if(writeled(path2, "off") < 0) return -1;
		delay(100);
   	}

  	return EXIT_SUCCESS;
}


