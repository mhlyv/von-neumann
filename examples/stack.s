section .text
	move r2, 0x10
write:
	sub r2, 1
	push r2
	jmpnz r2, write

	move r2, 0x10
read:
	pop r3
	print r3
	sub r2, 1
	jmpnz r2, read
	exit
