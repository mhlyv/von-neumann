## Von-Neumann machine (OOP exercise)

# Example:

```
$ cat examples/fibonacci.s
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
