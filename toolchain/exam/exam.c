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

/* String to access the ADC2 via sysfs */
#define AIN2_DEV "/sys/bus/iio/devices/iio\:device0/in_voltage2_raw"
/* Delay value for one second in us */
#define ONE_SECOND 1000000
/* Define some useful constants */
#define BUFFER_SIZE 16
#define ADC_BIT_RES 10
#define V_REF 1.8
#define N pow(2,10)
/* Vars */
int adc_fd;
int charRead;
char adcBuffer[BUFFER_SIZE];

/* Delay values in micro seconds */
#define ONE_MILLISECOND		1000
#define ONE_SECOND		1000000

/* Delay value for the blink time */
#define BLINK_TIME		50

/* Define some useful constants */
#define SYSFS_PATH		"/sys/class/gpio/"
#define MAX_STR_BUF		512
#define MAX_PATH_STR		(512)
#define LOW			0
#define HIGH			1
#define OUTPUT			0
#define INPUT			1
#define PRESSED			'0'

/* Define the GPIO numbers of the FireFly-BFH-Cape LEDs */
#define LED_1			124
#define LED_2			125
#define LED_3			126
#define LED_4			127
#define MAX_LEDS		(4)

/* Define the assignment button to pin number of the FireFly-BFH-Cape */
#define BUTTON_1		120
#define BUTTON_2		121
#define BUTTON_3		122
#define BUTTON_4		123
#define MAX_BUTTONS		(4)

/* Define the index of the LEDs and Buttons */
#define L1			0
#define L2			1
#define L3			2
#define L4			3

#define T1			0
#define T2			1
#define T3			2
#define T4			3

/* Define sysfs enumeration types */
enum
 {
  GPIO_SYSFS_EXPORT = 0,
  GPIO_SYSFS_UNEXPORT,
  GPIO_SYSFS_GET_DIRECTION,
  GPIO_SYSFS_SET_DIRECTION,
  GPIO_SYSFS_GET_VALUE,
  GPIO_SYSFS_SET_VALUE,
 } GPIO_ACTIONS;

/* Function prototypes */
void sigint_handler(int sig);
int sysfs_gpio_handler(uint8_t function, uint32_t gpio, char *val);

/* Static variables */
static int32_t gpio_button[MAX_BUTTONS] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4};
static int32_t gpio_led[MAX_LEDS]       = {LED_1, LED_2, LED_3, LED_4};

static char ON[]  = "1";
static char OFF[] = "0";
static char OUT[] = "out";
static char IN[]  = "in";

/* Sys-Timer tick variable */
volatile static uint32_t softTimer = 0;

/*
 ***************************************************************************
 * Periodic system timer-tick handler 10 ms
 ***************************************************************************
 */

void signal_timer_handler(int32_t signum)
{
 if (softTimer != 0)
  softTimer--;
}

void signal_callback(int32_t signum)
{
	printf("was here\n");
}

/*
 ***************************************************************************
 * Delay base time is 10 ms (blocking)
 ***************************************************************************
 */

void delay(int32_t value)
 {
  softTimer = value;
  while (softTimer != 0);
 }

/*
 ***************************************************************************
 * Define the function to be called when ctrl-c (SIGINT)
 * signal is sent to process
 ***************************************************************************
 */
void signal_ctrlc_handler(int sig_num)
 {
  /* Inform user exit via Ctrl-C */
  printf("\nExit app by pressing Ctrl-C!\n\n");

  /******** BEGIN INSERT YOUR CODE HERE *******/
  sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L1], OFF);
  sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L2], OFF);
  sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L3], OFF);
  sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L4], OFF);
	
  /* Unexport all selected gpios */
  sysfs_gpio_handler(GPIO_SYSFS_UNEXPORT, gpio_led[L1], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_UNEXPORT, gpio_button[T1], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_UNEXPORT, gpio_led[L2], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_UNEXPORT, gpio_button[T2], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_UNEXPORT, gpio_led[L3], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_UNEXPORT, gpio_button[T3], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_UNEXPORT, gpio_led[L4], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_UNEXPORT, gpio_button[T4], NULL);

  /******** END INSERT YOUR CODE HERE *******/

  /* Terminate program */
  exit(sig_num);
}

/*
 ***************************************************************************
 * sysfs_gpio_handler - handle GPIO operations
 ***************************************************************************
 */
int sysfs_gpio_handler(uint8_t function, uint32_t gpio, char *val)
 {
  char     path_str[MAX_PATH_STR];
  char     strBuf[MAX_STR_BUF];
  uint8_t  oflags = 0;
  int32_t  fd;
  uint32_t len;
  uint8_t  inval;

  /* Determine open flags based on function */
  switch (function)
   {
    case GPIO_SYSFS_EXPORT:
     snprintf(path_str, sizeof(path_str), SYSFS_PATH"export");
     oflags=O_WRONLY;
    break;

    case GPIO_SYSFS_UNEXPORT:
     snprintf(path_str, sizeof(path_str), SYSFS_PATH"unexport");
     oflags=O_WRONLY;
    break;

    case GPIO_SYSFS_SET_DIRECTION:
     snprintf(path_str, sizeof(path_str), SYSFS_PATH"gpio%d/direction", gpio);
     oflags=O_WRONLY;
    break;

    case GPIO_SYSFS_SET_VALUE:
     snprintf(path_str, sizeof(path_str), SYSFS_PATH"gpio%d/value", gpio);
     oflags=O_WRONLY;
    break;

    case GPIO_SYSFS_GET_DIRECTION:
    case GPIO_SYSFS_GET_VALUE:
     snprintf(path_str, sizeof(path_str), SYSFS_PATH"gpio%d/value", gpio);
     oflags=O_RDONLY;
    break;

    default:
     printf("File operation flag not defined\n");
   }

  /* Open the pseudo file given its path and open flags	*/
  #ifdef DEBUG
   printf("open:%s\n", path_str);
  #endif

  fd = open(path_str, oflags);
  if (fd  < 0)
   {
    perror(path_str);
    return fd;
   }

  /* File operations r/w on the opened file */
  switch (function)
   {
    case GPIO_SYSFS_EXPORT:
    case GPIO_SYSFS_UNEXPORT:
     len = snprintf(strBuf, sizeof(strBuf), "%d", gpio);
     #ifdef DEBUG
      printf("exp/unexp:%s\n", strBuf);
     #endif
     write(fd, strBuf, len);
     /* Delay time to setup gpio permission by the udev deamon */
     delay(50);
    break;

    case GPIO_SYSFS_SET_DIRECTION:
     #ifdef DEBUG
       printf("write dir:%s\n", val);
     #endif
     write(fd, val, strlen(val)+1);
    break;

    case GPIO_SYSFS_SET_VALUE:
     #ifdef DEBUG
      printf("write val:%s\n", val);
     #endif
     write(fd, val, strlen(val)+1);
    break;

    case GPIO_SYSFS_GET_DIRECTION:
    break;

    case GPIO_SYSFS_GET_VALUE:
     read(fd, &inval, 1);
     #ifdef DEBUG
      printf("read val:%c\n", inval);
     #endif
     *val = inval;
    break;

    default:
     printf("function not defined\n");
   }
  close(fd);
  return 0;
 }

float readPoti(void)
{
	float ret = 0.0;
	/* Open adc file descriptor and check for any errors */
 	if ((adc_fd = open(AIN2_DEV, O_RDONLY)) == -1)
 		perror("Error: cannot open adc device!\n");
 	/* Get ADC value as string */
 	charRead = read(adc_fd, adcBuffer, sizeof(adcBuffer));
 	if (charRead != -1)
 	{
 		/* Terminate string */
 		adcBuffer[charRead] = '\0';
 		/* Calculate input voltage */
 		ret = (float) atoi(adcBuffer);
 		ret = (V_REF * ret) / N;
 		//sprintf(adcBuffer, "%f", aValue);
 		/* Write input voltage to console */
 		//printf("AIN2: %sV\n", adcBuffer);
 		//lseek(adc_fd, 0, 0);
 	}
 	/* Clean up and exit */
 	close(adc_fd);
	return ret;
}

/*
 ***************************************************************************
 * main
 ***************************************************************************
 */

int main(int argc, char **argv)
 {
  char    button1;
  char button2;
  char button3;
  char button4;
  struct itimerval timer = {{0}};
  int callbacktime_ms = 1000;
  bool directionUpwards = true;
  int currentled = 0;
  int sleeptime = 100;  

  /* Register signal and signal handler */
  signal(SIGINT, signal_ctrlc_handler);

  /* Configure the timer to expire after 10 msec... */
  timer.it_value.tv_sec = 0;
  timer.it_value.tv_usec = 10000;

  /* ... and every 10 msec after that. */
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = 10000;

  /* Register signal handler for periodic timer with Kernel */
  signal(SIGALRM, &signal_timer_handler);
  setitimer(ITIMER_REAL, &timer, NULL);

struct sigaction sa;
struct itimerval timer2;
/* Install timer_handler as the signal handler for SIGVTALRM. */
memset (&sa, 0, sizeof (sa));
sa.sa_handler = &signal_callback;
sigaction (SIGVTALRM, &sa, NULL);

/* Configure the timer to expire after 250 msec... */
timer2.it_value.tv_sec = 0;
timer2.it_value.tv_usec = 250000;
/* ... and every 250 msec after that. */
timer2.it_interval.tv_sec = 0;
timer2.it_interval.tv_usec = 0;		//For cyclic
/* Start a virtual timer. It counts down whenever this process is
executing. */
setitimer(ITIMER_VIRTUAL, &timer2, NULL);		//Can be set whenever it should be started

  /******** BEGIN INSERT YOUR CODE HERE *******/

  /* Setup gpio sysfs for your app */
  sysfs_gpio_handler(GPIO_SYSFS_EXPORT, gpio_led[L1], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_SET_DIRECTION, gpio_led[L1], OUT);
  sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L1], OFF);
  sysfs_gpio_handler(GPIO_SYSFS_EXPORT, gpio_led[L2], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_SET_DIRECTION, gpio_led[L2], OUT);
  sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L2], OFF);
  sysfs_gpio_handler(GPIO_SYSFS_EXPORT, gpio_led[L3], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_SET_DIRECTION, gpio_led[L3], OUT);
  sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L3], OFF);
  sysfs_gpio_handler(GPIO_SYSFS_EXPORT, gpio_led[L4], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_SET_DIRECTION, gpio_led[L4], OUT);
  sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L4], OFF);

  sysfs_gpio_handler(GPIO_SYSFS_EXPORT, gpio_button[T1], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_SET_DIRECTION, gpio_button[T1], IN);
  sysfs_gpio_handler(GPIO_SYSFS_EXPORT, gpio_button[T2], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_SET_DIRECTION, gpio_button[T2], IN);
  sysfs_gpio_handler(GPIO_SYSFS_EXPORT, gpio_button[T3], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_SET_DIRECTION, gpio_button[T3], IN);
  sysfs_gpio_handler(GPIO_SYSFS_EXPORT, gpio_button[T4], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_SET_DIRECTION, gpio_button[T4], IN);


  /******** END INSERT YOUR CODE HERE *******/

  /* Toggle LED-1 until Button T1 or Ctrl/C is pressed */
  printf("\nTOOLCHAIN EXAM of vogef\n");
  printf("--------------------------------------------------\n\n");
  printf("Terminate program by pressing Ctrl-C\n\n");

  while (true)
   {
     /******** BEGIN INSERT YOUR CODE HERE *******/
     if(directionUpwards)
     {
    	currentled++;
      	currentled%=4;
     }	
     else
     {
	if(currentled == 0)
	{
	     currentled = 4;
	}
	currentled--;

     }
printf("poti: %f\n", readPoti());

     switch(currentled)
     {
 	case L1:
	{
		sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L1], ON);
		sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L2], OFF);
		sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L3], OFF);
		sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L4], OFF);
		break;
	}
	case L2:
	{
		sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L1], OFF);
		sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L2], ON);
		sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L3], OFF);
		sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L4], OFF);
		break;
	}
	case L3:
	{
		sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L1], OFF);
		sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L2], OFF);
		sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L3], ON);
		sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L4], OFF);
		break;
	}
	case L4:
	{
		sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L1], OFF);
		sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L2], OFF);
		sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L3], OFF);
		sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L4], ON);
		break;
	}
	default:
	{
		break;
	}
     }

     delay(sleeptime);

     sysfs_gpio_handler(GPIO_SYSFS_GET_VALUE, gpio_button[T1], &button1);
     if (button1 == PRESSED)
      break;

     sysfs_gpio_handler(GPIO_SYSFS_GET_VALUE, gpio_button[T2], &button2);
     if (button2 == PRESSED)
      if(sleeptime >= 13)
	sleeptime/=2;

     sysfs_gpio_handler(GPIO_SYSFS_GET_VALUE, gpio_button[T3], &button3);
     if (button3 == PRESSED)
      if(sleeptime < 100)
	sleeptime*=2;

     sysfs_gpio_handler(GPIO_SYSFS_GET_VALUE, gpio_button[T4], &button4);
     if (button4 == PRESSED)
      directionUpwards = !directionUpwards;

     /******** END INSERT YOUR CODE HERE *******/
   }
  
  /******** BEGIN INSERT YOUR CODE HERE *******/

  sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L1], OFF);
  sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L2], OFF);
  sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L3], OFF);
  sysfs_gpio_handler(GPIO_SYSFS_SET_VALUE, gpio_led[L4], OFF);
	
  /* Unexport all selected gpios */
  sysfs_gpio_handler(GPIO_SYSFS_UNEXPORT, gpio_led[L1], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_UNEXPORT, gpio_button[T1], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_UNEXPORT, gpio_led[L2], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_UNEXPORT, gpio_button[T2], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_UNEXPORT, gpio_led[L3], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_UNEXPORT, gpio_button[T3], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_UNEXPORT, gpio_led[L4], NULL);
  sysfs_gpio_handler(GPIO_SYSFS_UNEXPORT, gpio_button[T4], NULL);

  /******** END INSERT YOUR CODE HERE *******/

  /* Set default signal handling */
  signal(SIGINT, SIG_DFL);

  return EXIT_SUCCESS;
 }


