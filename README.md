Beomote
=======

Bang &amp; Olufsen Remote Library for Arduino

This library decodes the infrared signal from a Bang &amp; Olufsen remote using a TSOP 7000 or probably a plasma protected Bang &amp; Olufsen infrared eye. The TSOP 7000 is discontinued, but still available from eBay.

Supported devices
=======

The following remotes have been tested and works with the library:

- Bang &amp; Olufsen Beo4
- Bang &amp; Olufsen Beolink 1000
- Bang &amp; Olufsen Beoremote One IR (not bluetooth signals)


Connection
=======

This version of the Library uses an interrupt to detect the signal from the TSOP. The interrupt is registered on the rising edge, which is actually the trailing edge of the pulse from the TSOP as it is active low.

Signal Format
==========

B&amp;O uses a PWM style format for their IR signals. Its a 200ns pulse, delay, then a pulse.

```
__|XXXX|_________________________|XXXX|___________________________________________|XXXX|______ etc
```
Depending on the length of the delay, indicates the start of the message, A 0 bit, a 1 bit, a repeat of the last bit, and the end of the message.

The Beo4 message format is

*	START_MESSSAGE
*	Link : bit
*	Address: Byte - Target device. 0=TV, 1=Audio, 1B = Lights
*	Command: Byte - see Commmands.h
*	STOP_MESSAGE
  
BeoRemote one seems to extend the command with an additional 4 bytes for new functionality. The STOP message is delayed until 21 bytes have been sent. Anecdotally these commands all have an address beginning with a C, eg C0 or C4, but I don't know if that is a definitive signal.
