// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		processor.h
//		Purpose:	Processor Emulation (header)
//		Created:	26th October 2015
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#ifndef _SYS_PROCESSOR_H
#define _SYS_PROCESSOR_H	

typedef unsigned short WORD16;														// 8 and 16 bit types.
typedef unsigned char  BYTE8;
typedef unsigned int   LONG32;


#define DEFAULT_BUS_VALUE (0xFF)													// What's on the bus if it's not memory.

void CPUReset(void);																// CPU methods
BYTE8 CPUExecuteInstruction(void);													// Execute one instruction (multi phases)
void CPUInterruptRequest(void);														// Request Interrupt.

#ifdef INCLUDE_DEBUGGING_SUPPORT													// Only required for debugging

typedef struct _CPUSTATUS {
	int a,e,s,pc,p0,p1,p2,p3;
	int cycles;																		// Elapsed cycles
} CPUSTATUS;

CPUSTATUS *CPUGetStatus(void);														// Access CPU State
void CPULoadBinary(char *fileName);													// Load Binary in.
BYTE8 CPURead(WORD16 address);														// Access RAM
BYTE8 CPUExecute(WORD16 break1,WORD16 break2);										// Run to break point(s)
WORD16 CPUGetStepOverBreakpoint(void);												// Get step over breakpoint

#endif
#endif