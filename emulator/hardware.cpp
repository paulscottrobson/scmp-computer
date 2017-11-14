// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		hardware.cpp
//		Purpose:	Hardware Interface
//		Date:		1st October 2017
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include "sys_processor.h"
#include "hardware.h"
#include "gfx.h"																

/*
	I/O Hardware. Based around a TMS080x based calculator, with the connections between
	KB, KC and the IC broken.

	Inputs to chip
	==============
	KB (0 + others)										from F1
	KC (1-9)											from F0

	Outputs from Chip
	=================
	D0 goes to logic 1 at start of sequence 			to SIN
	KB (key pressed on 0 + others) 						to SB
	KC (1-9) 											to SA

	Emulation
	=========

	SIO 	resets the sequence, this always puts a '1' on E bit 7 (though it should
			still be tested). currentKeyLine is set to 0.
			At this point, SA + SB represent the state of the current key selected 
			on KC and KB. (Initially 0 (KB) and 9 (KC)). Active high.

	DLY <>	Short delay after the positive edge detection, of about 5-10% of the high
			cycle - this allows the key input to stabilise.

	DLY 3	Delay to same position in next cycle. If either F0 or F1 is set at this point
			behaves as if the corresponding keys are pressed (e.g. update display as if
			the key is pressed - only 0-9 . and C are supported). Advance the current key
			line as far as 9 (when it is reset to $FF) thus allowing for next detection.
			The state of the 'key press' (from F0/F1) is on the high/low transition.

*/

// *******************************************************************************************************************************
//											Hardware Reset
// *******************************************************************************************************************************

void HWIReset(void) {
}

// *******************************************************************************************************************************
//											End of frame code.
// *******************************************************************************************************************************

void HWIEndFrame() {
}

// *******************************************************************************************************************************
//						 Read current digit for a given digit (0 = right most)
// *******************************************************************************************************************************

BYTE8 HWIGetDisplayDigit(BYTE8 digit) {
	return (digit & 1) ? digit : digit+16;
}
