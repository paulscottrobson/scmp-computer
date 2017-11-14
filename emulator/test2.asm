
	cpu 	sc/mp

	nop
waitD0:
	sio
	lde
	jp 		waitD0
	dly 	00
	ldi 	0xF6
scan:
	xae
	csa
	ani 	0x30
	cas
	jz 		nopress
	lde
	xpal 	p2
nopress:
	lde 	
	xor 	echoKey
	jnz		noecho
	ldi 	1
	cas
	st 		echoKey
noecho:
	dly 	03
	lde
	ccl
	adi 	1
	jnz 	scan
halt:
	xpal 	p2	 		; zeroes P2.L
	xae
	lde
	xor 	lastKey
	jz 		waitD0
	lde
	st 		lastKey
	jz 		waitD0

	xri 	0xFF 		; 2 or = pressed
	jz 		Clear
	lde
echo:
	st 		echoKey
	jmp 	waitD0


Clear:
	ldi 	2
	cas
	dly 	03
	jp 		waitD0

lastKey:
	db 		0
echoKey:
	db 		0
