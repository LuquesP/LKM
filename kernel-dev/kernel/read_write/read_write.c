#include <linux/module.h> 
#include <linux/init.h> 
#include <linux/fs.h> 
#include <linux/cdev.h> 
#include <linux/uaccess.h> 

/* META Information */ 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("LPI");
MODULE_AUTHOR("REGISTER a device nr. and implement some callback funcitons");

static char buffer[255]; 
static int buffer_pointer; 

// Variables for device and device class 

static dev_t my_device_nr; 
static struct class *my_class;  
static struct cdev my_device; 

#define DRIVER_NAME  "dummydriver"
#define DRIVER_CLASS  "MyModuleClass"

//Read data out of the buffer 
static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) {
    int to_copy, not_copied, delta; 

    // Get amount of data to copy
    to_copy = min(count, buffer_pointer); 

    //Copy data to user 
    not_copied = copy_to_user(user_buffer, buffer, to_copy); 
    
    // Calculate data 
    delta = to_copy - not_copied; 

    return delta; 

}

// write data to buffer 
static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs) {
    int to_copy, not_copied, delta; 

    // Get amount of data to copy
    to_copy = min(count, sizeof(buffer)); 

    //Copy data to user 
    not_copied = copy_from_user(buffer, user_buffer, to_copy); 
    buffer_pointer = to_copy; 
    
    // Calculate data 
    delta = to_copy - not_copied; 

    return delta; 

}

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
    .read = driver_read, 
    .write = driver_write,
}; 

#define MYMAJOR 90

// THIS function is called when the module is loaded into the kenrel

static int  __init ModuleInit(void) {
    int retval; 
    // Allocate a device nr 
    if(alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0){
        printk("Devie NR. could not be allocated"); 
        return - 1;  
    }
    printk("read_write - Device Nr. Major: %d, Minor %d was registerd!\n", my_device_nr >> 20, my_device_nr && 0xfffff);

//    create device class 
    if((my_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
        printk("Device class can not e created! \n"); 
        goto ClassError; 
    }
//    create device fiel 
    if(device_create(my_class, NULL, my_device_nr, NULL, DRIVER_NAME) == NULL){
        printk("Can not create device file\n"); 
        goto FileError; 
    }
    cdev_init(&my_device, &fops); 
    // Registering device to kernel 
    if(cdev_add(&my_device, my_device_nr, 1) == -1) {
        printk("Registration fo device to kernel failed" ); 
        goto AddError; 
    }
    
    return 0; 
    AddError: 
        device_destroy(my_class, my_device_nr); 

    FileError: 
        class_destroy(my_class); 

    ClassError: 
        unregister_chrdev_region(my_device_nr, 1); 
        return -1; 
}



// This funciton is called when the module is removed from the kernel

static void __exit ModuleExit(void) {
    cdev_del(&my_device); 
    device_destroy(my_class, my_device_nr); 
    class_destroy(my_class); 
    unregister_chrdev(MYMAJOR, "my_dev_nr"); 
    printk("Goodby Kernel\n"); 
}

module_init(ModuleInit); 
module_exit(ModuleExit); 
