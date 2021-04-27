section .text
	move r1, 30 ; nth fibonacci
	move r2, 0  ; a
	move r3, 1  ; b
loop:
	sub r1, 1
	add r2, r3  ; a = a + b
	swap r2, r3 ; swap values
	print r2
	jmpnz r1, loop
	exit
