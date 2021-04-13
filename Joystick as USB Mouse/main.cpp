#include "mbed.h"
#include "USBMouse.h"
//USB mouse demo using a 5-way Navigation Switch (Digital Joystick)
//Needs USB connector breakout with D+, D-, and Gnd to mbed LLP1768
/*

Hookup D+, D-, and gnd pins to the mbed LPC1768 pins with the same name.

*/





USBMouse mouse;

class Nav_Switch
{
public:
    Nav_Switch(PinName up,PinName down,PinName left,PinName right,PinName fire);
    int read();
//boolean functions to test each switch
    bool up();
    bool down();
    bool left();
    bool right();
    bool fire();
//automatic read on RHS
    operator int ();
//index to any switch array style
    bool operator[](int index) {
        return _pins[index];
    };
private:
    BusIn _pins;

};
Nav_Switch::Nav_Switch (PinName up,PinName down,PinName left,PinName right,PinName fire):
    _pins(up, down, left, right, fire)
{
    _pins.mode(PullUp); //needed if pullups not on board or a bare nav switch is used - delete otherwise
    wait(0.001); //delays just a bit for pullups to pull inputs high
}
inline bool Nav_Switch::up()
{
    return !(_pins[0]);
}
inline bool Nav_Switch::down()
{
    return !(_pins[1]);
}
inline bool Nav_Switch::left()
{
    return !(_pins[2]);
}
inline bool Nav_Switch::right()
{
    return !(_pins[3]);
}
inline bool Nav_Switch::fire()
{
    return !(_pins[4]);
}
inline int Nav_Switch::read()
{
    return _pins.read();
}
inline Nav_Switch::operator int ()
{
    return _pins.read();
}

Nav_Switch myNav( p9, p6, p7, p5, p8); //pin order on Sparkfun Nav SW breakout

int main()
{
    int16_t x = 0;
    int16_t y = 0;
    uint8_t left_click = 0;
    while (1) {
        //check relative mouse movement
        x=0;
        y=0;
        if (myNav.up()) x=-1;
        if (myNav.down()) x=1;
        if (myNav.left()) y=1;
        if (myNav.right()) y=-1;
        //check mouse left button click
        if (myNav.fire()) left_click = 1;
        if (!myNav.fire())left_click = 0;
        //send a mouse data packet to PC
        mouse.update(x, y, left_click, 0);
        wait(0.001);
    }
}