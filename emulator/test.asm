; ***********************************************************************************************
;
;
; ***********************************************************************************************

	cpu 	sc/mp

bootloader:
	nop 

__currentAddressX1:	
	xpal 	p1 									; get P1.L
	xae 										; put into E
	lde 										; copy back into P1.L
	xpal 	p1
;
;	Refresh the display with the value in E
;
refreshDisplayWithE:	
	ldi 	0x82 								; put first character to send ($82, 'C') in P3.H
	xpah 	p3
	ldi 	9 									; chars to send in P3.L
refreshDisplayOnceIfACZero:	
	ori 	1
writeKeystroke:									; write the next keystroke
	xpal 	p3 									; put back in P3.L counter.
	xae 										; wait for D0
	sio
	xae
	jp 		writeKeyStroke
	dly 	00									; short delay in.

	csa 										; get status of SA/SB
	ani 	0x30
	xpal 	p2 									; put in P2.L

	xpah 	p3 									; recover character to transmit
	jp 		notD8 								; if +ve, don't skip to D8.
	xpah 	p3 									; save back
	dly 	03*8 								; skip to D8
	xpah 	p3 									; restore.
notD8:
	cas 										; write to F0/F1.

	dly 	03 									; wait till next scan position.
	ldi 	0 									; clear F0, F1 and CY/L.	
	cas 

	lde 										; shift E left into CY/L
	ade
	xae

	csa 										; get SR
	ani 	0x80 								; now $00 (NC) $80 (C)
	adi 	0x01 								; now $01 (NC) $82 (C)
	xri 	0x03 								; now $02 (NC) $81 (C)
	xpah 	p3 									; put in character to write.

	ld 		@-1(p3) 							; decrement counter
	xpal 	p3 									; check it.
	jnz 	writeKeystroke 						; go do the next keystroke.
	xpah 	p3 									; zero 'to write' in P3.H now.

	xpal 	p2 									; get key press value from P2.L
	xae 										; put in E.
__lastKeyStatusX1:
	ldi 	00									; get last key pressed
	xre 										; has it changed ?
	jz  	refreshDisplayOnceIfAcZero			; if not, keep scanning the keyboard.

	lde 										; get the value from the keyboard.
	st 		__lastKeyStatusX1+1 				; update the last key status.
	jz 		__currentAddressX1 					; if released display current address.

	ani 	0x20 								; was SB pressed (e.g. zero)
	jz 		advance 							; if not, it was nine which is advance only

												; pressing 0 copies the toggles in.
	ld 		0xFFF 								; read keyboard toggles
	st 		(p1) 								; and save at current address

advance:
	ld 		@1(p1) 								; read the byte there and bump P1.
	xae 										; into E
	jmp 	refreshDisplayWithE 				; display that





