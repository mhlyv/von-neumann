section .text
	move r2, 0xFF
loop:
	sub r2, 1
	jmpnz r2, loop
	exit
