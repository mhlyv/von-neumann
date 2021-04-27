## Von-Neumann machine (OOP exercise)

# Example:

```
$ cat examples/fibonacci.s
section .text
	move r1, 30 ; nth fibonacci
	move r2, 0  ; a
	move r3, 1  ; b
loop:
	sub r1, 1
	move r4, r2 ; backup
	add r2, r3  ; a = a + b
	swap r2, r3 ; swap values
	print r2
	jmpnz r1, loop
	exit
$ make release
...
$ ./build/release/neumann examples/fibonacci.s
1
1
2
3
5
8
13
21
34
55
89
144
233
377
610
987
1597
2584
4181
6765
10946
17711
28657
46368
75025
121393
196418
317811
514229
832040
```
