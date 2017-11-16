; ***********************************************************************************************
;
;
; ***********************************************************************************************

	cpu 	sc/mp

bootloader:
	nop 
	ldi 	0xA5 									; value in P3.H
	xpah 	p3 	
	ldi	 	0x82									; start with $82 (C)
	xae
	ldi 	0x80-9									; loop counter in P3.L
	xpal 	p3

__nextDigit:	
waitD0:
	xae
	sio
	xae
	jp 		waitD0
	dly 	00

	xpal 	p3 										; check if finished *after* reset to D0
	jp 		__doNextDigitOut

	xpal 	p3 										; fix P3 back so we can loop around.
	csa 											; check if it has changed
	ani 	0x30 									; only interested in SA + SB
__lastKey:	
	xri		0x00
	jz 		waitD0  								; check if it's changed.
	xor 	__lastKey+1								; update last key vaue
	st 		__lastKey+1


__doNextDigitOut:
	xpal 	p3

	lde												; $82 = C $81 = 1 $02 = 0
	jp 		__writeSASB
	dly 	8 * 3 									; skip straight to D8.
	lde 											; reload current value
__writeSASB:
	cas 											; output the lower bits to F0/F1 and CY/L ?
	dly 	3 										; wait end of pulse
	ldi 	0 										; clear F0/F1
	cas 

	xpah 	p3 										; get number being displayed, 
	xae 											; shift left into carry.
	lde
	ade
	xpah 	p3 										; save it back, A will be cleared 

	csa 											; get $81 or $02 in AC.
	ani 	0x80
	adi		0x01
	xri 	0x03
	xae 											; put back in E

	ld 		@1(p3) 									; inc loop counter
	jmp 	__nextDigit 							; do the next digit.

__endofrefresh:
	


