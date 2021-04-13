#include "mbed.h"
#include "XNucleo53L0A1.h"
#include <stdio.h>
Serial pc(USBTX,USBRX);

DigitalOut shdn(p26);
// This VL53L0X board test application performs a range measurement in polling mode
// Use 3.3(Vout) for Vin, p28 for SDA, p27 for SCL, P26 for shdn on mbed LPC1768

//I2C sensor pins
#define VL53L0_I2C_SDA   p28
#define VL53L0_I2C_SCL   p27

static XNucleo53L0A1 *board=NULL;

int main()
{
    int status;
    uint32_t distance;
    DevI2C *device_i2c = new DevI2C(VL53L0_I2C_SDA, VL53L0_I2C_SCL);
    /* creates the 53L0A1 expansion board singleton obj */
    board = XNucleo53L0A1::instance(device_i2c, A2, D8, D2);
    shdn = 0; //must reset sensor for an mbed reset to work
    wait(0.1);
    shdn = 1;
    wait(0.1);
    /* init the 53L0A1 board with default values */
    status = board->init_board();
    while (status) {
        pc.printf("Failed to init board! \r\n");
        status = board->init_board();
    }
    //loop taking and printing distance
    while (1) {
        status = board->sensor_centre->get_distance(&distance);
        if (status == VL53L0X_ERROR_NONE) {
            pc.printf("D=%ld mm\r\n", distance);
        }
    }
}
