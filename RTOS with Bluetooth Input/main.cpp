#include "mbed.h"
#include "rtos.h"
#include "uLCD_4DGL.h"
#include "wave_player.h"
#include "SDFileSystem.h"
//#include "SongPlayer.h"
 
//BusOut myled(LED1,LED2,LED3,LED4);
PwmOut led1(LED1);
PwmOut led2(LED2);
PwmOut led3(LED3);
RawSerial bluemod(p28,p27);
PwmOut red(p23);
PwmOut green(p22);
PwmOut blue(p21);
// add
AnalogOut DACout(p18);
PwmOut PWMout(p26);
uLCD_4DGL uLCD(p9, p10, p11);
SDFileSystem sd(p5, p6, p7, p8, "sd");
wave_player waver(&DACout,&PWMout);

Mutex lcd_mutex;
Mutex poplock;

bool popped = false;

float note[18]= {1568.0,1396.9,1244.5,1244.5,1396.9,1568.0,1568.0,1568.0,1396.9,
                 1244.5,1396.9,1568.0,1396.9,1244.5,1174.7,1244.5,1244.5, 0.0
                };
float duration[18]= {0.48,0.24,0.72,0.48,0.24,0.48,0.24,0.24,0.24,
                     0.24,0.24,0.24,0.24,0.48,0.24,0.48,0.48, 0.0
                    };

void screeneffect(void const *args){
    while(1) {
        /*
        lcd_mutex.lock();
        uLCD.filled_circle(64,64,20,BLACK);
        lcd_mutex.unlock();
        
        Thread::wait(500);
        */
        lcd_mutex.lock();
        uLCD.filled_circle(64,64,20,BLUE);
        lcd_mutex.unlock();
        poplock.lock();
        bool local_pop = popped;
        poplock.unlock();
        if ( local_pop == true) {
            lcd_mutex.lock();
            uLCD.filled_circle(64,64,20,BLACK);
            uLCD.circle(64,64,20,BLUE);
            lcd_mutex.unlock();
            Thread::wait(2000);
            local_pop = false;
        }
        
        /*
        led1 = 0;
        Thread::wait(1000);
        led1 = 1;
        Thread::wait(1000);
        */
    }
}

void soundeffect(void const *args){
    while(1) {
        led2 = 1;
        Thread::wait(100);
        led2 = 0;
        Thread::wait(100);
        poplock.lock();
        bool soundlock = popped;
        poplock.unlock();
        if(soundlock == true){
            
            FILE *wave_file;
            wave_file = fopen("/sd/mydir/Pop.wav","r");;
            waver.play(wave_file);
            fclose(wave_file);
            led2 = 1; 
            Thread::wait(2000);
            /*
            soundlock = false;
            
            SongPlayer mySpeaker(p26);
            mySpeaker.PlaySong(note,duration);
            */
            Thread::wait(2000);
            
        }
        
        
        
    }
}

void bluetooth(void const *args){
    
    //lcd_mutex.lock();
    char bred=0;
    char bgreen=0;
    char bblue=0;
    red = green = blue = 0;    
    
    //lcd_mutex.lock();
    while(1){
        if (bluemod.getc()=='!') {
            //lcd_mutex.lock();
            if (bluemod.getc()=='C') { //color data packet
                bred = bluemod.getc(); // RGB color values
                bgreen = bluemod.getc();
                bblue = bluemod.getc();
                if (bluemod.getc()==char(~('!' + 'C' + bred + bgreen + bblue))) { //checksum OK?
                    red = bred/255.0; //send new color to RGB LED PWM outputs
                    green = bgreen/255.0;
                    blue = bblue/255.0;
                    poplock.lock();
                    popped = true;
                    poplock.unlock();
                    led1 =1;
                    Thread::wait(2000);
                    led1 =0;
                    
                    poplock.lock();
                    popped = false;
                    poplock.unlock();
                    
                    red = green = blue = 0;
                    Thread::wait(100);
                }
            }
        }
    }
    
}
 
int main()
{
    
    Thread thread2 (screeneffect);
    Thread thread3 (soundeffect);
    Thread thread4 (bluetooth);
    
    
    
    while(1) {
        /*
        if (bluemod.getc()=='!') {
            if (bluemod.getc()=='C') { //color data packet
                bred = bluemod.getc(); // RGB color values
                bgreen = bluemod.getc();
                bblue = bluemod.getc();
                if (bluemod.getc()==char(~('!' + 'C' + bred + bgreen + bblue))) { //checksum OK?
                    red = bred/255.0; //send new color to RGB LED PWM outputs
                    green = bgreen/255.0;
                    blue = bblue/255.0;
                }
            }
        }
        */
    }
    
}