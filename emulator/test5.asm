; ***********************************************************************************************
;
;					Bootloader 2. Displays AAA.DDD in octal. Writes to page 1xx
;
; ***********************************************************************************************

	cpu 	sc/mp


bootloader:
	nop

echo: 									; wait for D0 to go high.
	sio
	lde 
	jp 		echo
	dly 	00
outDataX1:
	ldi 	0x82 						; $02 := '0' $81 := '1' $82 := 'C'
echoloop:	
	jp 		writeout
	xae 								; save in E
	dly 	03							; go to next pulse
	ccl									; CY/L already cleared.
	ldi 	0x10 						; add $10 and go back if not done x times.
	ade
	jmp 	echoloop

writeout:
	cas 								; set F0, F1 bit.
	dly 	03							; wait for next pulse
	ldi 	0 							; turn bits off and clear carry.
	cas

dataToShow:
	ldi 	0xC7 						; get the value to display.
	ccl
	add 	dataToShow+1 				; shift left into CY/L 
	st 		dataToShow+1 				; and write back.

	csa 								; $80 for '1' $00 for '0' and CY/L set 
	jp 		notset
	ori 	3 							
notset:									; $83 for '1' $00 for '0'
	xri 	2 							; $81 for '1' $02 for '1'
	st 		outDataX1+1 				; write back

	dld 	bootloader 					; do as many times as required.
	jp 		echo 

hlt:
	jmp 	hlt

displayValue:

