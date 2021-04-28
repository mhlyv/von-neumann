section .text
	move r1, 12
loop:
	sub r1, 1
	jmpnz r1, loop
	exit
