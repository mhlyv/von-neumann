section .text
	call sub
	print r2
	exit

sub:
	move r2, 0xFF
	ret
