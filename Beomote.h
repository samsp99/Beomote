#ifndef _BEOMOTE_H
#define _BEOMOTE_H

#include "Commands.h"
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Common divisors for 3125 = 1, 5, 25, 125, 625, 3125
#define TICK 25

// Defining the Bang & Olufsen commands
#define BEO_ZERO    (3125 / TICK) //125
#define BEO_SAME    (6250 / TICK) //250 
#define BEO_ONE     (9375 / TICK) //375
#define BEO_STOP    (12500 / TICK) //500
#define BEO_START   (15625 / TICK) //625

typedef struct {
    boolean link;
   // beo_address address;
   // beo_command command;
    unsigned char address;
    unsigned int command;
} BeoCommand;

typedef enum IrState
{
    WAITING = 0x00,
    FIRST_PULSE = 0x04,
    IN_PROGRESS = 0x08,
    MSG_COMPLETE = 0x10
} IrState;

class Beomote {
    public:
        void initialize(int pin);
        int receive(BeoCommand &cmd);

        // This method is only to be called by the interrupt service routine
        void timerISR();
        void pulseISR();

    private:
        int irPin;

        int lastState;
        int lastBeoBit;

        IrState state;

        boolean link;
        unsigned char address;
        unsigned int command;

        volatile int timer;
        int index;

        void reset();
        int fuzzyCompare(int value, int target);
        void debugDumpState(int beoCode);
};
extern Beomote Beo;


#endif