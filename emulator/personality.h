// *********************************************************************************************
// *********************************************************************************************
//
//		Name:		personality.h
//		Purpose:	Define the machine type.
//		Created:	26th October 2015
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *********************************************************************************************
// *********************************************************************************************

// *********************************************************************************************
//		
//	The basic computer design. 1/4k of RAM enabled when A8 = 0, and A11 = 1 is used to enable
//	input from the toggle switches. 
//
//	The connection of A11 via an inverter to the 81LS97 not-EN input when the switch is in 
//	run mode (replacing 4k7 to +5v) is the only schematic change.
//
//	For forward code compatibility read the toggle switches from $0Fxx, ideally $0FFF
//
// *********************************************************************************************

#ifdef BASEMODEL

#define MAPPING_4K								// We don't bother to properly calculate the EAC as A12-15 are ignored
//#define USE_OVERFLOW							// Uncomment this to set OV on CAD/CAI/ADD/ADI

#define RAMSIZE 	(256)						// Memory size. needs to be set
static BYTE8 ramMemory[RAMSIZE];				// RAM memory, needs to be defined

#define READ(x) 	__read(x)					// Read including I/O hardware
#define WRITE(x)	ramMemory[(x) & 0xFF] = AC	// Write AC to memory.
#define FETCH()		READ(++P0)					// Can be optimised so doesn't access hardware.

static BYTE8 inline __read(WORD16 addr) {
	if ((addr & 0x100) == 0) {
		return ramMemory[addr & 0xFF];
	}
	if ((addr & 0x800) != 0) {
		return HWIReadDataToggles();
	}
	return DEFAULT_BUS_VALUE;
}

#endif

#ifdef MAPPING_4K
#define 	EACIX(p)		_eac4kix(&p)
#define 	EACIXNOE(p)		_eac4kixnoe(&p)
#define 	EACAIX(p) 		_eac4kaix(&p)
#endif
