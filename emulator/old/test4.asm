; ***********************************************************************************************
;
;					Bootloader 2. Displays AAA.DDD in octal. Writes to page 1xx
;
; ***********************************************************************************************

	cpu 	sc/mp

buffer = 0x7A							; positioned here so with 6 digits, it 

bootloader:

		nop
		ldi 	1 						; p3.h points to working page.
		xpah 	p3
;
;		Using the current address (at readit+1) fill the buffer with the numeric data
; 		the lower 3 bits only being relevant.
;
		ldi 	(buffer & 255)+3 		; p1 points to buffer, assumes its zero filled.
		xpal 	p1 						; it won't be first time round :)
		ld 		readit+1
		scl

nextexpand:

expand:	st 		@-1(p1)
		sr
		sr
		sr
		jnz 	expand
		csa 							; if CY/L clear, then done.
		jp 		refresh

		ldi 	(buffer & 255)+6 		; p1 points to tail of buffer.		
		xpal	p1

readit:	ldi 	0xFE
		xpal 	p3
		ld 		0(p3) 					; read the byte, p3 = 0. This constant is the address
		ccl 							; clear the carry/link flag
		jmp 	nextexpand 
;
;		Copy data into the screen. Assumes clear.
;
refresh:
		ldi 	buffer & 255			; point P1 to the buffer.
nextdigit:
		xpal 	p1
		sio 							; wait for D0 to go high and step first bit.
		lde
		jp 		nextdigit
		dly 	00
		ldi 	0xF8					; do 8 digits.
digitloop:
		xae
		ld 		0(p1) 					; get required display value
		xre 							; xor with counter
		ani 	7 						; if the lower 3 bits are the same then echo out.
		jnz 	noecho
		st 		0(p1)					; erase buffer for next time around.
		ldi 	1 						; set F0 to 1 to 'type in' the number
		cas
noecho:	dly 	03 						; clock out get key.
		ldi 	0 						; clear F0 + CY/L
		cas 			  
		lde 							; go to	next digit
		adi 	1
		jnz 	digitloop
		ld 		@1(p1) 					; next in buffer.
		xpal 	p1 						; check if done
		jp 		nextdigit 				; all 6 digits

halt:	jmp 	halt
;
;		get keystroke - modify address / data depending.
;
		org 	0x1FE
		db  	0x7A
