; ***********************************************************************************************
;
;		Bootloader 1 - toggled in via toggle switches. Allows entering of code using
;		the keypad in the 9-2 C quasi octal format.
;
;
; ***********************************************************************************************

	cpu 	sc/mp

bootloader:

	nop
;
;		Come back here when no key is pressed, we set CY/L so we can echo first key press
;
keynotpressed:
	scl 						; can echo on first press as key not pressed
;
;		Come back here to rescan the keyboard
;
waitD0:
	sio 						; wait for D0 to go to logic '1'
	lde
	jp 		waitD0

	dly 	00 					; step into up pulse.
	ldi 	0xF7 				; D0 = F8, D8 = FF
;
;		Inside scanning loop, at top A = F8-FF
;
scan:
	xae 						; save in P3.L and E	
	lde
	xpal 	p3 					

	csa 						; check keyboard
	ani 	0x30 		
	jz 		nokeypressed 		; no key pressed, skip out.

	lde							; put key in p2.L
	xpal 	p2 					

	csa 				 		; if echoed already (carry is clear) don't re-echo it.		
	jp 		nokeypressed
;
;	Echo the key. The hard bit is we want to echo 'C' if we pressed 1 or C to clear the display.
;
	lde 						; get key D0-D8. We want to set F1 for D8 and F0 for D0-7
	xri 	0xFF				; now 0 if D8, #- for D0-D7
	jz 		notD0to7
	ldi 	3 					; now 0 if D8, 3 if D0-D7
notD0to7:
	xri 	0x82 				; now $82 if D8, $81 if D0-D7
	cas 						; write to flags.
;
;	The delay to shift to the next line.
;
nokeypressed:
	dly 	03 					; output possibly, go to next key,
	csa 						; clear everything except the carry flag.
	ani 	0x80
	cas

	ld 		@1(p3) 				; bump P3.L, the line counter until 1-9 all tested
	xpal 	p3
	jnz 	scan 			

	xpal 	p2 					; if no key had been pressed, P2 will be zero, clears for next time
	jz 		keynotpressed 		; then we can go back, resetting the CY/L bit.

	xri 	0xFF 				; so now C/1 = 0 and 2-9 are 1-8
	xae 						; save in E

	csa 						; if CY/L = 0 already processed this key, so rescan
	jp 		waitD0 				; until it's released, at which point it will set CY/L again.

	lde 						; actually do stuff (code in E)
	st 		count+1
	ild 	count

	ccl 						; now carry clear so cannot be re-echoed until key is released.	
	jmp 	waitD0				; this will keep going until released.

count:db 	0
