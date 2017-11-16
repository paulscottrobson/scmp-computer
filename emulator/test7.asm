; ***********************************************************************************************
;
;					Bootloader 2. Displays AAA.DDD in octal. Writes to page 1xx
;
; ***********************************************************************************************

	cpu 	sc/mp


bootloader:
	nop 								

RepaintBuffer:
	ldi 	0xF2 								; put C in start of buffer
	st 		buffer
	ldi 	buffer 								; buffer
__RPEntry:	
	xpal 	p1
RepaintBufferChar:
	sio 										; wait for code.
	lde
	jp 		RepaintBuffer
	dly 	00
	ldi 	0x70 								; counter
__RPLoop:
	xae
	csa 										; check for key press
	ani 	0x30
	jz 		__RPNoKey
	lde											; key pressed, put in P2.L
	xpal 	p2
__RPNoKey:
	ld 		(p1) 								; is it the current character ?
	xre
	ani 	0xF0
	jnz 	__RPNoSet
	ld 		(p1) 								; re-read it
	ani 	0x03 	 							; isolate the flag bits
	cas 										; copy to Status register
__RPNoSet:
	dly 	03 									; next Data line
	ldi 	0x10 								; A = $10, also used to Clear F0,F1 and CY/L
	cas											
	ade											; add current position to it.
	jnz 	__RPLoop
	ldi 	0x72 								; overwrite character with zero
	st 		@1(p1) 								; and point to next character
	ld 		(p1)								; read the next character
	jnz 	RepaintBufferChar
	st 		emptybuffer 						; make sure emptybuffer is empty

	xpal 	p2 									; if non-zero key pressed, also clears P2.L
	jnz 	__KeyPressed

__KeepScanning:
	st 		lastkey 							; save as last key pressed.
__KeepScanningNoLK:
	ldi 	emptybuffer 						; redo with an empty buffer, just scan keyboard	
	jmp 	__RPEntry

__KeyPressed:
	xor 	lastkey 					
	jz 		__KeepScanningNoLK

w1:	jmp 	w1

lastkey:
	db 		0

buffer:
	db 		0x72 								; 'C'											
	db 		0x72,0x72,0x72,0x72,0x72,0x72		; 0 0 0 0 0 0
emptybuffer:
	db 		0,0 								; a buffer with nothing in it.


	db 		0xFF	