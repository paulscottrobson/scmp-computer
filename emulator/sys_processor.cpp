// *********************************************************************************************
// *********************************************************************************************
//
//		Name:		sys_processor.cpp
//		Purpose:	Processor Emulation.
//		Created:	26th October 2015
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *********************************************************************************************
// *********************************************************************************************

#include <stdio.h>
#include "sys_processor.h"
#include "hardware.h"

#define CYCLES_PER_SECOND 	(2000000)
#define FRAMES_PER_SECOND	(60)
#define CYCLES_PER_FRAME 	(CYCLES_PER_SECOND / FRAMES_PER_SECOND)

// *********************************************************************************************
//												CPU Personality stuff
// *********************************************************************************************

#include "personality.h"

// *********************************************************************************************
//												CPU Registers
// *********************************************************************************************

static BYTE8 AC,E,STATUS,CARRY,OVERFLOW,DELAY4CYCLES,T8;
static WORD16 P0,P1,P2,P3,CYCLES,T16;


// *********************************************************************************************
//													CPU Reset
// *********************************************************************************************

void CPUReset(void) {
	AC = E = P0 = P1 = P2 = P3 = CARRY = STATUS = OVERFLOW = 0;
	CYCLES = 0;DELAY4CYCLES = 0;
	HWIReset();
}

// *********************************************************************************************
//												  CPU Support Functions
// *********************************************************************************************

#define SIN() 		HWIWaitNewDisplayScan()
#define SOUT(bit) 	{}
#define FLAGS(bits)	{}
#define SENSEA() 	HWICheckSenseLine('A')
#define SENSEB()	HWICheckSenseLine('B')

#include "_scmp_support.h"

// *********************************************************************************************
//											Execute a single instruction phase
// *********************************************************************************************

#include <stdlib.h>
#include <stdio.h>

BYTE8 CPUExecuteInstruction(void) {

	if (DELAY4CYCLES == 0) {
		T8 = FETCH();
		if (T8 == 0x8F) {
			BYTE8 p = READ(P0+1);
			if (p % 3 == 0) {
				while (p > 0) {
					p = p - 3;
					HWINextDisplayScanPulse(getStatus());
				}
			}
		}
		switch(T8) {																// Do the selected opcode and phase.
			#include "_scmp_case.h"
		}
	}

	if (DELAY4CYCLES != 0) {														// DLY in progress
		WORD16 remCycles = CYCLES_PER_FRAME - CYCLES;								// CYCLES left this frame
		if (remCycles/4 < DELAY4CYCLES) {											// Not enough cycles
			DELAY4CYCLES = DELAY4CYCLES - remCycles / 4;
			CYCLES = 0;
			return FRAMES_PER_SECOND;
		} else {																	// enough this time.
			CYCLES = CYCLES + DELAY4CYCLES * 4;
			DELAY4CYCLES = 0;
		}
	}


	if (CYCLES < CYCLES_PER_FRAME) return 0;										// Frame in progress, return 0.
	CYCLES -= CYCLES_PER_FRAME;														// Adjust cycle counter
	HWIEndFrame();																	// Hardware stuff.
	return FRAMES_PER_SECOND;														// Return the frame rate for sync speed.
}

#ifdef INCLUDE_DEBUGGING_SUPPORT

// *********************************************************************************************
//										 Get the step over breakpoint value
// *********************************************************************************************

WORD16 CPUGetStepOverBreakpoint(void) {
	BYTE8 opcode = CPURead(P0+1);													// Read opcode.
	if ((opcode & 0xFC) == 0x3C) return ((P0+1) & 0xFFFF);							// XPPC Px
	return 0xFFFF;
}

// *********************************************************************************************
//										Run continuously till breakpoints / Halt.
// *********************************************************************************************

BYTE8 CPUExecute(WORD16 break1,WORD16 break2) {
	BYTE8 rate = 0;
	while(1) {
		rate = CPUExecuteInstruction();												// Execute one instruction phase.
		if (rate != 0) {															// If end of frame, return rate.
			return rate;													
		}
		if (P0+1 == break1 || P0+1 == break2) return 0;
	} 																				// Until hit a breakpoint or HLT.
}

// *********************************************************************************************
//												Load a binary file into RAM
// *********************************************************************************************

void CPULoadBinary(char *fileName) {
	if (fileName != NULL) {
		FILE *f = fopen(fileName,"rb");
		fread(ramMemory,RAMSIZE,1,f);
		fclose(f);
	}
}

// *********************************************************************************************
//												Gets a pointer to RAM memory
// *********************************************************************************************
	
BYTE8 CPURead(WORD16 address) {
	return READ(address);
}

// *********************************************************************************************
//											Retrieve a snapshot of the processor
// *********************************************************************************************

static CPUSTATUS s;																	// Status area

CPUSTATUS *CPUGetStatus(void) {
	s.a = AC;s.e = E;s.s = getStatus();
	s.pc = P0;s.p0 = P0;s.p1 = P1;s.p2 = P2;s.p3 = P3;
	s.cycles = CYCLES;																// Number of cycles.
	return &s;
}
#endif
