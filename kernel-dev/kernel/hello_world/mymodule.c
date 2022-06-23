#include <linux/module.h> 
#include <linux/init.h> 

/* META Information */ 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("LPI");
MODULE_AUTHOR("a hello world LKM");


// THIS function is called when the module is loaded into the kenrel

static int  __init ModuleInit(void) {
    printk("Hello, Kernel"); 

    return 0; 
}

// This funciton is called when the module is removed from the kernel

static void __exit ModuleExit(void) {
    printk("Goodby Kernel\n"); 
}

module_init(ModuleInit); 
module_exit(ModuleExit); 
