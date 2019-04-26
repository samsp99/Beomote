/*********************************************************************************
B&O uses a PWM system, with 200ms pulses with specific sized gaps between them.
The gap size determines the data payload:
	BEO_ZERO    3125 
	BEO_SAME    6250  - Repeat of the last Bit type
	BEO_ONE     9375 
	BEO_STOP    12500 - Marks the start of a message
	BEO_START   15625 - Marks the end of a message

Beo4 commmands are of the form:
	START_PULSE
	Link : bit
	Address: Byte - Target device. 0=TV, 1=Audio, 1B = Lights
	Command: Byte - see Commmands.h
	STOP_PULSE

BeoRemote One uses an additional 4bits for commmands, sending the STOP mark after
21 bits of data
*********************************************************************************/

#include "Beomote.h"

Beomote Beo;

void Pin_ISR()
{
	Beo.pulseISR();
}

ISR(TIMER1_OVF_vect)
{
	Beo.timerISR();
}

// Pin needs to support interrupts, will depend on specific board being used.
// For example, Uno can use Pin2 or Pin3.
void Beomote::initialize(int pin)
{
	irPin = pin;
	// Setting the pinmode of the IR pin and resetting the listener
	pinMode(irPin, INPUT);
	reset();

	// Clearing Control Register A
	TCCR1A = 0;
	// Setting the phase and frequency correct pwm, and stopping the timer
	TCCR1B = _BV(WGM13);

	long cycles = (F_CPU / 2000000) * TICK;
	ICR1 = cycles;

	TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));

	// Setting the timer overflow interrupt enable bit
	TIMSK1 = _BV(TOIE1);

	// Resetting clock select register, and starts the clock with no prescale
	TCCR1B |= _BV(CS10);

	// Setup interrupt to listen to trailing edge of pulse
	attachInterrupt(digitalPinToInterrupt(pin), Pin_ISR, RISING);
}

void Beomote::reset()
{
	index = -1;
	state = WAITING;
	timer = 0;

	link = 0x00;
	address = 0x00;
	command = 0x00;

	//Reset Timer
	TCCR1B |= _BV(CS10);
}

int Beomote::receive(BeoCommand &cmd)
{

	if (state == MSG_COMPLETE)
	{
		cmd.link = link;
		//cmd.address = (beo_address)address;
		//cmd.command = (beo_command)command;
		cmd.address = address;
		cmd.command = command;

		reset();
		return 1;
	}

	return 0;
}

int Beomote::fuzzyCompare(int value, int target)
{
	int fudge = BEO_ZERO / 10;
	return (value >= target - fudge) && (value <= target + fudge);
}

void Beomote::timerISR()
{
	timer++;
}

void Beomote::pulseISR()
{
	int irData = !digitalRead(irPin);
	//digitalWrite(13, irData);
	int beoCode = 0;
	int beoBit;

	// Don't process new command if the old one hasn't been picked up
	if (state == MSG_COMPLETE)
	{
		return;
	}

	if (state == WAITING)
	{
		timer = 0;
		state = FIRST_PULSE;
	}
	else if (fuzzyCompare(timer, BEO_ZERO))
	{
		beoCode = BEO_ZERO;
		beoBit = lastBeoBit = 0;
	}
	else if (fuzzyCompare(timer, BEO_SAME))
	{
		beoCode = BEO_SAME;
		beoBit = lastBeoBit;
	}
	else if (fuzzyCompare(timer, BEO_ONE))
	{
		beoCode = BEO_ONE;
		beoBit = lastBeoBit = 1;
	}
	else if (fuzzyCompare(timer, BEO_STOP))
	{
		beoCode = BEO_STOP;
	}
	else if (fuzzyCompare(timer, BEO_START))
	{
		beoCode = BEO_START;
	}
	else
	{
		// We haven't found a valid pulse size
		//Serial.println("Invalid pulse");
		//DumpState();
		reset();
	}
	//We got a valid message, reset the timer and process it
	timer = 0;

	if (beoCode == BEO_START)
	{
		state = IN_PROGRESS;
		index = 0;
	}
	else if (index == 0)
	{
		link = beoBit;
		index++;
	}
	else if (index < 9)
	{
		address = address << 1;
		address |= beoBit;

		index++;
	}
	else if (beoCode == BEO_STOP)
	{
		state = MSG_COMPLETE;
	}
	else if (index < 21)
	{
		command = command << 1;
		command |= beoBit;

		index++;
	}
	else
	{
		#ifdef DEBUG
		Serial.println("How did we get here?");
		debugDumpState(beoCode);
		#endif
		
		reset();
	}
}

void Beomote::debugDumpState(int beoCode)
{
	Serial.println("Beomote State:");
	Serial.print("  code:");
	Serial.println(beoCode);
	Serial.print("  state:");
	Serial.println(state);
	Serial.print("  timer:");
	Serial.println(timer);
	Serial.print("  index:");
	Serial.println(index);
	Serial.print("  link:");
	Serial.println(link, HEX);
	Serial.print("  address:");
	Serial.println(address, HEX);
	Serial.print("  command:");
	Serial.println(command, HEX);
}
