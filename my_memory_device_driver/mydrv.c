#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "mydrv"
#define MYDRV_MAX_LENGTH 4096
#define MIN(a,b) (((a)<(b)) ? (a) : (b))

struct class* myclass;
struct cdev* mycdev;
struct device* mydevice;

dev_t mydev;

static char* mydrv_data;
static int mydrv_read_offset, mydrv_write_offset;

static int mydrv_open(struct inode* inode, struct file* file){
		return 0;
}

static int mydrv_release(struct inode* inode, struct file* file){
		return 0;

}

static ssize_t mydrv_read(struct file* file, char* buf, size_t count, loff_t* poss){
	if(copy_to_user(buf, mydrv_data+mydrv_read_offset, count))
		return -1;

	mydrv_read_offset += count;

	return count;
	}
static ssize_t mydrv_write(struct file* file, const char* buf, size_t count, loff_t* ppos){


	int divide_count; 			
	int remnant_count;			/* overwrite */
	int index = 0;
	int i=0;	/* To Upper or Lower Case */
	if(count < 100){
		if(copy_from_user(mydrv_data + mydrv_write_offset,buf,count)){
				return -1;
			}				/* If input buffer strlen < 100 */
	}
	else{					/* If input buffer strlen > 100 */
		divide_count = count/ 100;
		remnant_count = count % 100;

		if(copy_from_user(mydrv_data + mydrv_write_offset, buf, 100)){
			return -1;	
		}
		index+=100;			
		while(divide_count != 1){
		if(copy_from_user(mydrv_data + mydrv_write_offset, buf+index , 100)){
				return -1;							

		}
		index += 100;
		divide_count--;

		}

		if(copy_from_user(mydrv_data + mydrv_write_offset,buf+index, remnant_count)){
			return -1;
			
		}

	}	

	while(i< count){
	if (i> 100){
		break;
	}
	if((*(mydrv_data+i) >= 'A') &&( *(mydrv_data+i) <= 'Z')){
		*(mydrv_data+i) = (*(mydrv_data+i))+32;			/* To Lower Case */
	}
	else if((*(mydrv_data+i) >= 'a') && (*(mydrv_data+i) <= 'z')){
		*(mydrv_data+i) = (*(mydrv_data+i))-32;			/* To Upper Case */
	}
	else{
		*(mydrv_data+i) = ' ';
	}
	
	
	i += 1;
	}
	

	

	mydrv_write_offset += 100;

	return count;
}


struct file_operations mydrv_fops = {
	.owner = THIS_MODULE,
	.read = mydrv_read,
	.write = mydrv_write,
	.open = mydrv_open,
	.release = mydrv_release,
};


int mydrv_init(void){
	if(alloc_chrdev_region(&mydev, 0, 1, DEVICE_NAME) <0)
		return -EBUSY;

	myclass = class_create(THIS_MODULE, "mycharclass");
	if(IS_ERR(myclass)){
		unregister_chrdev_region(mydev,1);
		return PTR_ERR(myclass);
		}

	mydevice = device_create(myclass, NULL, mydev, NULL, "mydevicefile");
	if(IS_ERR(mydevice)){
		class_destroy(myclass);
		unregister_chrdev_region(mydev,1);
		return PTR_ERR(mydevice);
	}

	mycdev = cdev_alloc();
	mycdev->ops = &mydrv_fops;
	mycdev->owner = THIS_MODULE;
	if(cdev_add(mycdev,mydev,1) <0){
		device_destroy(myclass,mydev);
		class_destroy(myclass);
		unregister_chrdev_region(mydev,1);
		return -EBUSY;
	}

	mydrv_data = (char*)kmalloc(MYDRV_MAX_LENGTH* sizeof(char), GFP_KERNEL);

	mydrv_read_offset = mydrv_write_offset = 0;
	return 0;
}

void mydrv_cleanup(void){
	kfree(mydrv_data);
	cdev_del(mycdev);
	device_destroy(myclass, mydev);
	class_destroy(myclass);
	unregister_chrdev_region(mydev,1);

}


module_init(mydrv_init);
module_exit(mydrv_cleanup);


MODULE_LICENSE("GPL");
