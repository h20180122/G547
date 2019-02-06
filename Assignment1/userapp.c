#include <stdio.h> 
#include<stdlib.h>
#include<fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#define adxl_x "/dev/adxl_x"
#define adxl_y "/dev/adxl_y"
#define adxl_z "/dev/adxl_z"

int main()

{ 
  int fd,n;
  uint16_t val;
while(n!=3){

  printf("\nfor adxl_x enter 1\n");
  printf("for adxl_y enter 2\n");
  printf("for adxl_z enter 3\n");
  printf("\nEnter the axis\n");
  scanf("%d",&n);
  
  if(n==1)
  {
  fd=open(adxl_x, O_RDONLY);
  
  if(fd  == -1)
  {
  
    printf("cannot read source file adxl_x\n");
    return 0;
  }
  
  read(fd,&val,2);
  printf("X-axis value: %d\n",val);
  }
  else if(n==2)
  {
  fd=open(adxl_y , O_RDONLY);
  
  if(fd  == -1)
  {
  
    printf("cannot read source file adxl_y\n");
   return 0;
  }
  
  read(fd,&val,2);
  printf("Y-axis value: %d\n",val);
  }
  else if(n==3)
  {
  fd=open(adxl_z, O_RDONLY);
  
  if(fd  == -1)
  {
  
    printf("cannot read source file adxl_z \n");
    return 0;
  }
  
  read(fd,&val,2);
  printf("Z-axis value %d\n",val);
  }
else
printf("Enter valid key\n");
};
  close(fd);
  
  
  return 0;
}
