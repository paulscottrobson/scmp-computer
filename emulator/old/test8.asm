; ***********************************************************************************************
;
;
; ***********************************************************************************************

	cpu 	sc/mp

bootloader:
	nop 	
repaint:								
	ldi 	9 							; reset counter to 9
	st 		bootloader
	ldi 	0x82 						; reset first to print
	st 		__Character+1
	dly 	3 							; just in case were on D0 already.
waitD0:									; wait for D0 line
	sio
	lde
	jp 		waitD0
	dly 	0

__Character:
	ldi 	0x82						; $82 is 'C'	$81 is '1' $02 is '0'
	jp 		__NoXDelay
	dly		8*3
__NoXDelay:	
	ld 		__Character+1 				; reget character
	cas
	dly 	3
	ldi 	0							; clear CY/L F0 and F1
	cas
__CurrentValue:
	ldi 	0xC7 						; shift byte left
	add 	__CurrentValue+1
	st 		__CurrentValue+1 			; update it
	csa 								; get carry flag.
	ani 	0x80						; $80 if '1' $00 if '0'
	adi 	0x01 						; $82 if '1' $01 if '0'
	xri 	3 							; $81 if '1' $02 if '0'
	st 		__Character+1 				; overwrite the character

	dld 	bootloader 					; use initial nop as a counter
	jnz		waitD0
	
waitD02:								; wait for D0 line again.
	sio
	lde
	jp 		waitD02
	dly 	0
	csa
	ani 	0x30						; read first keyboard line on D0 (0-9)
__lastkey:
	xri 	00							; has it changed ?
	jz 		waitD02
	st 		__lastKey

hlt:jmp 	hlt




