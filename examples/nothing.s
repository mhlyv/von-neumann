section .text
_start:
	move r0, 0xff
loop:
	sub r0, 1
	jmpz r0, loop ; loop from 0xff to 0
	exit
