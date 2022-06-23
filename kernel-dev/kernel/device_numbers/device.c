#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/fs.h> 

/* META Information */ 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("LPI");
MODULE_AUTHOR("REGISTER a device nr. and implement some callback funcitons");

// This function is called, when the device file is opened 
static int driver_open(struct inode *device_file, struct file *instance){
    printk("dev-nr open was called \n"); 
    return 0; 
}

static int driver_close(struct inode *device_file, struct file *instance){
    printk("dev-nr close was called \n"); 
    return 0; 
} 

static struct file_operations fops = {
    .owner = THIS_MODULE, 
    .open = driver_open, 
    .release = driver_close,
}; 

#define MYMAJOR 90

// THIS function is called when the module is loaded into the kenrel

static int  __init ModuleInit(void) {
    int retval; 
    printk("Hello, Kernel"); 
    retval = register_chrdev(MYMAJOR, "my_dev_nr", &fops); 
    if(retval == 0) {
        printk("dev_nr - registered Device number Major: %d, Minor %d", MYMAJOR, 0); 
    }
    else if(retval > 0) {
        printk("dev_nr - registered Device number Major: %d, Minor %d", retval>>20, retval&0xfffff); 

    }
    else {
        printk("Could not register device number \n"); 
        return -1; 
    }

    return 0; 
}

// This funciton is called when the module is removed from the kernel

static void __exit ModuleExit(void) {
    unregister_chrdev(MYMAJOR, "my_dev_nr"); 
    printk("Goodby Kernel\n"); 
}

module_init(ModuleInit); 
module_exit(ModuleExit); 
