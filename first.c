#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/in.h>  
#include<linux/inet.h>  
#include<linux/socket.h>  
#include<net/sock.h>  

#define DEVICE_NAME "berserker"

static int device_open(struct inode*,struct file*);
static int dev_release(struct inode*,struct file*);
static ssize_t dev_read(struct file*, char*, size_t, loff_t*);
static ssize_t dev_write(struct file*, const char*, size_t, loff_t*);

static struct file_operations fops = {
	.open = device_open,
	.read = dev_read,
	.write = dev_write,
	.release = dev_release,
};

static int major_num;

int init_module()
{
	major_num = register_chrdev(0, DEVICE_NAME, &fops);

	if (major_num<0)
	{
		printk(KERN_ALERT "Berserker armour did not fit you!\n");
		return major_num;
	}

	printk(KERN_INFO "%d Eclipse incoming...\n", major_num);
	return 0;
}

void cleanup_module()
{
	unregister_chrdev(major_num, DEVICE_NAME);
	printk(KERN_INFO "Eclipse ending...\n");
}

static int device_open(struct inode *inodep, struct file *filep)
{
	printk(KERN_INFO "Berserker armour adapted to you!\n");
	return 0;
}
static int dev_release(struct inode *inodep, struct file *filep)
{
	printk(KERN_INFO "Berserker armour removed!\n");
	return 0;
}
static ssize_t dev_write(struct file *filep, const char *buf, size_t len, loff_t *offset)
{
	int err=0;
	char my_buf[100];
	int msg_len = strlen(buf);
	if(len > msg_len-*offset)
	{
		len = msg_len-*offset;
	}
	err = copy_from_user(my_buf+*offset,buf,len);
	printk(KERN_INFO "%s\n",buf);
	*offset += len;
	return err==0?len:-EFAULT;
}
static ssize_t dev_read(struct file *filep, char *buf, size_t len, loff_t *offset)
{
	int err=0;
	char *mssg = "...become the vengeful one, I shall dull your injuries...\n";
	int msg_len = strlen(mssg);
	if(len > msg_len - *offset)
	{
		len=msg_len-*offset;
	}
	err = copy_to_user(buf, mssg+(*offset), len);
	*offset += len;
	return (err==0)?len:-EFAULT;
}
MODULE_LICENSE("GPL");
