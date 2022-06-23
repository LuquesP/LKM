#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <fcntl.h> 

int main() {
    int dev  = open("/dev/device", O_RDONLY); 
    if (dev == -1 ){
        printf("Opening was not possible\n"); 
    }
    printf("Opening was successfull!\n"); 
    close(dev); 
    return 0; 
}
