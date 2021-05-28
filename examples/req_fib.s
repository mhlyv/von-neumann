section .text
	move r2, 20 ; nth fac
	move r3, 1
	call fib
	print r3
	exit

fib:
	jmpz r2, fib_exit
	mult r3, r2
	sub r2, 1
	call fib ; recurse
fib_exit:
	ret
