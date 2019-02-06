#include<linux/init.h>
#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/device.h>
#include <linux/types.h>
#include <linux/random.h>
#include<linux/errno.h>
#include <linux/uaccess.h>
static struct class *cls;
static dev_t accel;


static struct cdev adxl_x;
static struct cdev adxl_y;
static struct cdev adxl_z;

dev_t x,y,z;
uint16_t val;

static int x_open(struct inode *i,struct file *f)
{
printk(KERN_INFO "x-axis:open()\n");
return 0;
}
static int x_close(struct inode *i,struct file *f)
{
printk(KERN_INFO "x-axis:close()\n");
return 0;
}
static ssize_t x_read(struct file *f,char __user *buf,size_t len,loff_t *off)
{
printk(KERN_INFO "x-axis:read()\n");
get_random_bytes(&val, 2);
val=val%100;
printk(KERN_INFO "%d\n",val);
copy_to_user(buf, &val, 2);
return 0;
}
static int y_open(struct inode *i,struct file *f)
{
printk(KERN_INFO "y-axis:open()\n");
return 0;
}
static int y_close(struct inode *i,struct file *f)
{
printk(KERN_INFO "y-axis:close()\n");
return 0;
}
static ssize_t y_read(struct file *f,char __user *buf,size_t len,loff_t *off)
{
printk(KERN_INFO "y-axis:read()\n");
get_random_bytes(&val, 2);
val=val%100;
printk(KERN_INFO "%d\n",val);
copy_to_user(buf, &val, 2);
return 0;
}
static int z_open(struct inode *i,struct file *f)
{
printk(KERN_INFO "z-axis:open()\n");
return 0;
}
static int z_close(struct inode *i,struct file *f)
{
printk(KERN_INFO "z-axis:close()\n");
return 0;
}
static ssize_t z_read(struct file *f,char __user *buf,size_t len,loff_t *off)
{
printk(KERN_INFO "z-axis:read()\n");
get_random_bytes(&val, 2);
val=val%100;
printk(KERN_INFO "%d\n",val);
copy_to_user(buf, &val, 2);
return 0;
}


static struct file_operations xops =
{
.owner=THIS_MODULE,
.open=x_open,
.release=x_close,
.read=x_read,
};
static struct file_operations yops =
{
.owner=THIS_MODULE,
.open=y_open,
.release=y_close,
.read=y_read,
};
static struct file_operations zops =
{
.owner=THIS_MODULE,
.open=z_open,
.release=z_close,
.read=z_read,
};



static __init int accel_init(void)
{
	printk(KERN_INFO "Accelerometer registered\n");
	if((alloc_chrdev_region(&accel,0,3,"accelerometer"))<0) 
		{
			return -1;
		}
  // step 2 : creation of device file
	x=MKDEV(MAJOR(accel), MINOR(accel)+0);
	y=MKDEV(MAJOR(accel), MINOR(accel)+1);
	z=MKDEV(MAJOR(accel), MINOR(accel)+2);
	if((cls=class_create(THIS_MODULE,"chardrv"))==NULL)
		{
			unregister_chrdev_region(accel,3);
			return -1;
		}

   //step 3: Link fops and cdev to the device node
	cdev_init(&adxl_x,&xops);
	device_create(cls,NULL,x,NULL,"adxl_x");
	if(cdev_add(&adxl_x,x,1)<0)
		{
			device_destroy(cls, x);
			class_destroy(cls);
			unregister_chrdev_region(accel, 3);
			return -1;
		}
	cdev_init(&adxl_y,&yops);
	device_create(cls,NULL,y,NULL,"adxl_y");
	if(cdev_add(&adxl_y,y,1)<0)
		{
			cdev_del(&adxl_x);
			device_destroy(cls, y);
			device_destroy(cls, x);
			class_destroy(cls);
			unregister_chrdev_region(accel, 3);
			return -1;
		}
	cdev_init(&adxl_z,&zops);
	device_create(cls,NULL,z,NULL,"adxl_z");
	if(cdev_add(&adxl_z,z,1)<0)
		{
			cdev_del(&adxl_y);
			cdev_del(&adxl_x);
			device_destroy(cls, z);
			device_destroy(cls, y);
			device_destroy(cls, x);
			class_destroy(cls);
			unregister_chrdev_region(accel, 3);
			return -1;
		}
	return 0;

}
static __exit void accel_exit(void)
{

cdev_del(&adxl_x);
cdev_del(&adxl_y);
cdev_del(&adxl_z);
device_destroy(cls,x);
device_destroy(cls,y);
device_destroy(cls,z);
class_destroy(cls);
unregister_chrdev_region(accel,3);
printk(KERN_INFO "Bye accelerometer unregistered\n\n");
}

module_init(accel_init);
module_exit(accel_exit);

MODULE_DESCRIPTION("Assignment 1");
MODULE_AUTHOR("RENUKA RAMRAKHIANI");
MODULE_LICENSE("GPL");
MODULE_INFO(Accelerometer,"First Char driver for accelerometer");
