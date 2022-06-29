#include <linux/module.h>    // all kernel modules
#include <linux/kernel.h>    // KERN_INFO
#include <linux/errno.h>     // EFAULT
#include <linux/device.h>    // device register
#include <linux/fs.h>        // file_operations
#include <linux/types.h>     // size_t
#include <linux/uaccess.h>   // copy_from/to_user

MODULE_LICENSE("GPL");
MODULE_AUTHOR("VQTRONG");
MODULE_DESCRIPTION("Inverse Case");

/* DEVICE NAME */
#define DEVICE_NAME     "invcase"   // The device will appear at /dev/invcase
#define CLASS_NAME      "invcase"
#define DEVICE_DEBUG    "invcase: "

/* Global variable */
static int majorNumber = 0;
static struct class*  invcaseClass  = NULL;
static struct device* invcaseDevice = NULL;

#define MAX_SIZE 1024
static char __buffer[MAX_SIZE] = {0};

/* Function declaration */
static int invcase_init(void);
static void invcase_exit(void);
static ssize_t invcase_receive(
	struct file *filp, char *buf, size_t count, loff_t *f_pos
);
static ssize_t invcase_send(
	struct file *filp, const char *buf, size_t count, loff_t *f_pos
);

/* Device operations */
static struct file_operations __fops = 
{
	.owner	= THIS_MODULE,
	.read	= invcase_receive,
	.write	= invcase_send,
};

static int invcase_init(void){
	// Try to dynamically allocate a major number for the device -- more difficult but worth it
	majorNumber = register_chrdev(0, DEVICE_NAME, &__fops);
	if (majorNumber<0){
		printk(KERN_ERR DEVICE_DEBUG "Failed to register a major number\n");
		return majorNumber;
	}
	printk(KERN_INFO DEVICE_DEBUG "Registered with major number %d\n", majorNumber);

	// Register the device class
	invcaseClass = class_create(THIS_MODULE, CLASS_NAME);
	if (IS_ERR(invcaseClass)) // Check for error and clean up if there is
	{
		unregister_chrdev(majorNumber, DEVICE_NAME);
		printk(KERN_ERR DEVICE_DEBUG "Failed to register device class\n");
		return PTR_ERR(invcaseClass); // Correct way to return an error on a pointer
	}
	printk(KERN_INFO DEVICE_DEBUG "Device class registered correctly\n");

	// Register the device driver
	invcaseDevice = device_create(invcaseClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
	if (IS_ERR(invcaseDevice)) // Clean up if there is an error
	{
		class_destroy(invcaseClass);
		unregister_chrdev(majorNumber, DEVICE_NAME);
		printk(KERN_ERR DEVICE_DEBUG "Failed to create the device\n");
		return PTR_ERR(invcaseDevice);
	}

	// clear buffer
	memset(__buffer, 0, MAX_SIZE);
	printk(KERN_INFO DEVICE_DEBUG "Init!\n");
	return 0; // Zero means OK
}

static void invcase_exit(void){
	device_destroy(invcaseClass, MKDEV(majorNumber, 0)); // remove the device
	class_unregister(invcaseClass); // unregister the device class
	class_destroy(invcaseClass); // remove the device class
	unregister_chrdev(majorNumber, DEVICE_NAME); // unregister the major number
	printk(KERN_INFO DEVICE_DEBUG "Exit\n");
}

static ssize_t invcase_receive(
	struct file *filp, char *buf, size_t count, loff_t *f_pos
) {
	ssize_t remain = MAX_SIZE - *f_pos;
	ssize_t len = count > remain ? remain : count;
	
	printk(KERN_INFO DEVICE_DEBUG "Read from device, remain=%ld, *f_pos= %lld, count= %ld\n", remain, *f_pos, count);
	if(remain <= 0) return 0;

	if (copy_to_user(buf, __buffer+*f_pos, len)) {
		printk(KERN_ERR DEVICE_DEBUG "Can not copy to user\n");
		return -EFAULT;
	}
	printk(KERN_INFO DEVICE_DEBUG "Read from device: %s\n", __buffer);

	*f_pos += len;
	return len;
}

static ssize_t invcase_send(
	struct file *filp, const char *buf, size_t count, loff_t *f_pos
) {
	int i;
	ssize_t remain = MAX_SIZE - *f_pos;
	ssize_t len = count > remain ? remain : count;
	
	printk(KERN_INFO DEVICE_DEBUG "Write to device, remain=%ld, *f_pos= %lld, count= %ld\n", remain, *f_pos, count);
	
	if(*f_pos == 0) memset(__buffer, 0, MAX_SIZE);
	
	if(remain <= 0) return count; // ignore all requested bytes

	if(copy_from_user(__buffer+*f_pos, buf, len)) {
		printk(KERN_ERR DEVICE_DEBUG "Can not copy from user\n");
		return -EFAULT;
	}
	printk(KERN_INFO DEVICE_DEBUG "Write to device: %s\n", __buffer);

	for(i=*f_pos; i<*f_pos+len; i++) {
		if( __buffer[i] >= 'A' && __buffer[i] <= 'Z') {
			__buffer[i] += 32;
		}
		else if( __buffer[i] >= 'a' && __buffer[i] <= 'z') {
		__buffer[i] -= 32;
		}
	}
	printk(KERN_INFO DEVICE_DEBUG "Convert to: %s\n", __buffer);
	
	*f_pos += len;
	return len;
}

module_init(invcase_init);
module_exit(invcase_exit);
