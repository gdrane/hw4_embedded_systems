/* pins.c
 * Paul Martin & Gauresh Rane
 * EE202A Homework #3
 */

#include "mbed.h"

// -- Variables --
DigitalOut pin21(p21);
DigitalOut pin22(p22);
DigitalOut pin23(p23);

// -- Function Implementations --
void set(char pin){
    switch(pin){
        case 21:
            pin21 = 1;
            break;
        case 22:
            pin22 = 1;
            break;
        case 23:
            pin23 = 1;
            break;
        default:
            break;
    }
}
void clear(char pin){
    switch(pin){
        case 21:
            pin21 = 0;
            break;
        case 22:
            pin22 = 0;
            break;
        case 23:
            pin23 = 0;
            break;
        default:
            break;
    }
}
