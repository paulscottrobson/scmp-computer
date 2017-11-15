; ***********************************************************************************************
;
;		Bootloader 1 - toggled in via toggle switches. Allows entering of code using
;		the keypad in the 9-2 C quasi octal format.
;
;
; ***********************************************************************************************

	cpu 	sc/mp

; xx.xx.xx.xx . xx.xx.xx.xx format

bootloader:


		nop

		ldi 	(buffer & 255)+4
		xpal 	p1
		ld 		address
		xae
		ldi 	$FC
expand:
		xae 							; save counter
		st 		@-1(p1) 				; write to previous address
		rr
		rr
		xae
		ccl
		adi		1
		jnz 	expand
























address:	db 0xF3





buffer: