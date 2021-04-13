#include "mbed.h"
#include "SDFileSystem.h"
 
SDFileSystem sd(p5, p6, p7, p8, "sd"); // the pinout on the mbed Cool Components workshop board
 
int main() {
    printf("Hello World!\n");   
 
    mkdir("/sd/mydir", 0777);
    
    FILE *fp = fopen("/sd/mydir/sdtest.txt", "w");
    if(fp == NULL) {
        error("Could not open file for write\n");
    }
    fprintf(fp, "Hello SD file world");
    fclose(fp); 
    
    
    //char c;
    FILE *fn = fopen("/sd/mydir/sdtest.txt","r");
    if(fn == NULL) {
        error("Could not open file for read\n");
    }
    int ch;
    while ((ch = getc(fn)) != EOF){
        putc(ch, stdout);
    }
    
    
    
    fclose(fn); 
    
    
 
    printf("\nGoodbye World!\n");
}
