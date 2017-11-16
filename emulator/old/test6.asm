; ***********************************************************************************************
;
;					Bootloader 2. Displays AAA.DDD in octal. Writes to page 1xx
;
; ***********************************************************************************************

	cpu 	sc/mp


bootloader:
	nop 								
	ldi 	0xC7 						; display value is i E.
	xae
;
;	Coming here, E should contain the number, CY/L should be clear. Outputs value in binary.
;
	ldi 	0x82						; start by writing out C.
	xpal 	p1 							; save in p1.L as the counter initial value

echo: 									; wait for D0 to go high, preserving 'E'
	xae
	sio
	xae 
	jp 		echo
	dly 	00 							; initial step.

	xpal 	p1 							; here 3 values : $02 := '0' $81 := '1' $82 := 'C'
echoloop:	
	jp 		writeout 					; leave immediately for '0', it's part of D0.
	xpal 	p1 							; save in P1.L
	dly 	03							; go to next pulse
;	ccl									; CY/L already cleared.
	ld 		@0x10(p1) 					; add $10 to P1.L
	xpal 	p1
	jmp 	echoloop

writeout:
	cas 								; set F0, F1 bit.
	dly 	03							; wait for next pulse
	ldi 	0 							; turn bits off and clear carry.
	cas

	lde 								; add E to itself. 
	ade
	xae 								; write back, A now contains old value of E
	ani 	0x80 						; A is $80 (CY/L set) or $00 now.
	adi 	0x01 						; A is $82 or $01 now.
	xri 	0x03 						; A is $81 or $02 now.
	xpal 	p1 							; save in P1.L

	dld 	bootloader
	jp 		echo


hlt:
	jmp 	hlt

displayValue:

