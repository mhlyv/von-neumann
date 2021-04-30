section .text
	move r2, 0xFF 
	relz 0, 2  ; --|
	move r2, 0 ;   |
	print r2   ; <-|

	sub r2, 1    ; <-|
	print r2     ;   |
	relnz r2, -2 ; --|
	exit
