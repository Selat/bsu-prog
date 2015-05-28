	segment .text
	global transpose

	;; rcx - current element id.
	;; rsi - n * m - 1.
	;; rbx - n.
	;; rdi - pointer to the first element of the matrix.

transpose:
	mov r8, rsi
	imul rsi, rdx
	mov rbx, r8

	dec rsi
	mov rcx, 0
loop1:
	inc rcx
	cmp rcx, rsi
	jge end

	;; Check if we've already tranposed this element
	mov r8d, [rdi + 4 * rcx]
	test r8d, 0x80000000
	jnz loop1

	;; r8 - beginning of the cycle
	;; r9 - current element to swap
	mov r8, rcx
	mov r9d, [rdi + 4 * rcx]
	or r9d, 0x80000000
	push rcx
loop2:
	xor rdx, rdx
	mov rax, rcx
	imul rax, rbx
	div rsi
	mov rax, rdx

	mov r10d, [rdi + 4 * rax]
	or r10d, 0x80000000
	xchg r10d, r9d
	mov [rdi + 4 * rax], r10d
	mov rcx, rax

	cmp rcx, r8
	jne loop2

	pop rcx
	jmp loop1

end:
	;; Clear sign bit
	mov rcx, rsi
clloop:
	mov r10d, [rdi + 4 * rcx]
	and r10d, 0x7FFFFFFF
	mov [rdi + 4 * rcx], r10d
	loop clloop
	ret
