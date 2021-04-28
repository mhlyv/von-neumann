section .text
	move r2, 0x1E ; nth fibonacci
	move r3, 0  ; a
	move r4, 1  ; b
loop:
	sub r2, 1
	add r3, r4  ; a = a + b
	swap r3, r4 ; swap values
	print r3
	jmpnz r2, loop
	exit
