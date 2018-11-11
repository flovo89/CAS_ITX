#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <math.h>

/* MAX44009 Register pointers */
#define MAX44009_LUX_HIGH (0x03)
#define MAX44009_LUX_LOW (0x04)
#define MAX44009_LUX_CONFIG (0x02)

/* i2c Address of MCP9800 device */
#define MAX44009_I2C_ADDR (0x4A)

/* File handle to i2cdev */
int i2c_fd, Exponent, Mantissa;
double Licht;

/* Communication buffer */
char i2cCommBuffer[8];

int main(int argc, char** argv)
{
 /* Open the Linux i2c device */
 i2c_fd = open("/dev/i2c-4", O_RDWR);
 if (i2c_fd < 0)
 {
 	perror("i2cOpen");
 	exit(1);
 }

 /* Set the I2C slave address for all subsequent I2C transfers */
 if (ioctl(i2c_fd, I2C_SLAVE, MAX44009_I2C_ADDR) < 0)
 {
 	perror("i2cSetAddress");
 	exit(1);
 }

 i2cCommBuffer[0] = MAX44009_LUX_LOW;
 if(write(i2c_fd, i2cCommBuffer, 1) != 1) perror("write error");
 if(read(i2c_fd, i2cCommBuffer, 1) != 1) perror("read error");
 Mantissa = (i2cCommBuffer[0] & 0x0F);
 i2cCommBuffer[0] = MAX44009_LUX_HIGH;
 if(write(i2c_fd, i2cCommBuffer, 1) != 1) perror("write error");
 if(read(i2c_fd, i2cCommBuffer, 1) != 1) perror("read error");
 Mantissa |= ((i2cCommBuffer[0] & 0x0F) << 4);
 Exponent = ((i2cCommBuffer[0] & 0xF0) >> 4);
 close(i2c_fd);

 Licht = pow(2,Exponent) * Mantissa * 0.045;

 printf("Umgebungslicht in Lux: %f\n", Licht);

return 0;
}
