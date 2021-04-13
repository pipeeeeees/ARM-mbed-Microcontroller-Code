/*
https://os.mbed.com/users/4180_1/notebook/ulcd-144-g2-128-by-128-color-lcd/
*/



#include "mbed.h"
#include "LSM9DS1.h"
#include "uLCD_4DGL.h"

#define PI 3.14159

#define DECLINATION -4.94 // Declination (degrees) in Atlanta,GA.

uLCD_4DGL uLCD(p28, p27, p29);  // For the LCD
DigitalOut myled(LED1);
Serial pc(USBTX, USBRX);

float rolll = 64;
float pitchhh = 64;


void printAttitude(float ax, float ay, float az, float mx, float my, float mz) // only needs accel and magnitude
{
    
    float roll = atan2(ay, az);
    float pitch = atan2(-ax, sqrt(ay * ay + az * az));
// touchy trig stuff to use arctan to get compass heading (scale is 0..360)
    mx = -mx;
    float heading;
    if (my == 0.0)
        heading = (mx < 0.0) ? 180.0 : 0.0;
    else
        heading = atan2(mx, my)*360.0/(2.0*PI);
    //pc.printf("heading atan=%f \n\r",heading);
    heading -= DECLINATION; //correct for geo location
    if(heading>180.0) heading = heading - 360.0;
    else if(heading<-180.0) heading = 360.0 + heading;
    else if(heading<0.0) heading = 360.0  + heading;


    // Convert everything from radians to degrees:
    //heading *= 180.0 / PI;
    pitch *= 180.0 / PI;
    roll  *= 180.0 / PI;

    pc.printf("Pitch: %f,    Roll: %f degress\n\r",pitch,roll);
    pc.printf("Magnetic Heading: %f degress\n\r",heading);
    
    // 20 degree limits...
    
    uLCD.filled_circle(pitchhh,rolll, 10, BLACK);
    uLCD.circle(64,64,15,WHITE);   
    rolll = 64 + (roll*3);
    pitchhh = 64 - (pitch*3);
    uLCD.filled_circle(pitchhh,rolll, 10, WHITE);
    
}




int main()
{
    //LSM9DS1 lol(p9, p10, 0x6B, 0x1E);
    LSM9DS1 IMU(p9, p10, 0xD6, 0x3C);
    IMU.begin();
    if (!IMU.begin()) {
        pc.printf("Failed to communicate with LSM9DS1.\n");
        uLCD.printf("Failed to communicate with LSM9DS1.\n");
    }
    IMU.calibrate(1);
    IMU.calibrateMag(0);
    
    
    while(1) {
        while(!IMU.tempAvailable());
        IMU.readTemp();
        while(!IMU.magAvailable(X_AXIS));
        IMU.readMag();
        while(!IMU.accelAvailable());
        IMU.readAccel();
        while(!IMU.gyroAvailable());
        IMU.readGyro();
        
              
        
        /*
        pc.printf("\nIMU Temperature = %f C\n\r",25.0 + IMU.temperature/16.0);
        pc.printf("        X axis    Y axis    Z axis\n\r");
        pc.printf("gyro:  %9f %9f %9f in deg/s\n\r", IMU.calcGyro(IMU.gx), IMU.calcGyro(IMU.gy), IMU.calcGyro(IMU.gz));
        pc.printf("accel: %9f %9f %9f in Gs\n\r", IMU.calcAccel(IMU.ax), IMU.calcAccel(IMU.ay), IMU.calcAccel(IMU.az));
        pc.printf("mag:   %9f %9f %9f in gauss\n\r", IMU.calcMag(IMU.mx), IMU.calcMag(IMU.my), IMU.calcMag(IMU.mz));
        */
        printAttitude(IMU.calcAccel(IMU.ax), IMU.calcAccel(IMU.ay), IMU.calcAccel(IMU.az), IMU.calcMag(IMU.mx),
                      IMU.calcMag(IMU.my), IMU.calcMag(IMU.mz));
        wait(0.1);
    }
}

