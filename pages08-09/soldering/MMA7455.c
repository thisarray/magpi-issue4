// I2C writes =D0=0
// MMA7455 I2C address 1D (3A ,3B) write , read
// AN3745 app note for calibration
// byte read , write 1D , write address, read 1D ,DATA
// Byte write, write 1D , write address, write data.
// addresses,
// 06 XOUT8
// 07 YOUT8
// 08 ZOUT8
// 09 STATUS  D0 1=data ready
// 0A detection source
// 0F who am i
// 16 Mode Control  x1000101 measure 2gmode
// 18 Control1  D7 filter 0=62Hz,1=125Hz other 0
// 19 Control2  default 0
// CODE in C
// MMA7455test
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h> 
#include "/usr/include/linux/i2c-dev.h"
#include <string.h>
#include <dirent.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) 
{
	int fd;
	char filename[20];
	char buf[10];
	int res;
	int range=0;
	int x,y,z;  // 8 bit acl
	int count=1000; // read times
	
	sprintf(filename, "/dev/i2c-0");   //string to buffer ie filename="/dev/I2C-0"
	fd = open(filename, O_RDWR);
	if (fd < 0) {
		printf("Error on open\n");
		exit(1);
	}
 
	if (ioctl(fd, I2C_SLAVE, 0x1D) < 0) {
		printf("Error on slave address\n");
		exit(1);
	}
 
 // data write , reg,data
	buf[0] = 0x16;  // control reg 16
	buf[1] = 0x45;  // set 2g, enable
	if ((write(fd,buf,2))!=2) {
		printf("Error send the read command\n");
		exit(1);
	}


while (count-- >0)
{
usleep(3000);  // 
 //data read , first set address	
//	data write
	 // x accel 8 bit reg 6 	
	buf[0]=6;
	write(fd,buf,1);  // reg 6 x 
	read(fd,buf,1);
	x=buf[0];
	
	buf[0]=7;
	write(fd,buf,1);  // reg 7 y 
	read(fd,buf,1);
	y=buf[0];
	
	buf[0]=8;
	write(fd,buf,1);  // reg 8 z
	read(fd,buf,1);
	z=buf[0];
	
	printf("x=%d y=%d z=%d \n",x,y,z);	

}
	close(fd); 
	return 0;	
}



