
	cpu 	sc/mp

	nop
	ldi 	42
	st 		temp
wait:
	jmp 	wait
temp:
	db 		1
