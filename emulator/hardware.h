// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		hardware.h
//		Purpose:	Hardware Interface (header)
//		Date:		1st October 2017
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#ifndef _HARDWARE_H
#define _HARDWARE_H
	
void  HWIReset(void);
BYTE8 HWIWaitNewDisplayScan(void);
void  HWINextDisplayScanPulse(BYTE8 status);
BYTE8 HWIGetDisplayDigit(BYTE8 digit);
void  HWIEndFrame(void);
void  HWIEmulateKeyPress(char c);
BYTE8 HWICheckSenseLine(char sense);

#endif
