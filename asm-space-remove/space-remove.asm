	extern strlen

	segment .data
%define spacecode 32
%define semicoloncode '\;'

	segment .text

	global solve

solve:
	push rdi
	call strlen
	pop rdi
	mov rcx, rax
	inc rcx
	mov al, spacecode
	xor r9, r9					; (bool)R9 - found any non-space characters in the string.

	mov rsi, rdi
	jrcxz end
	repne scasb					; Search for the first space
	dec rdi
	cmp rsi, rdi
	mov rsi, rdi
	je loop
	inc rsi
loop:
	cmp rcx, 1
	jle end					; If ecx = 0, than we finished scaning the string

	cmp byte [rsi], 0
	je end
	repe scasb					; Search for the beginning of the word after some spaces
	cmp byte [rdi - 1], spacecode
	je end
	cmp byte [rdi - 1], 0
	jne skip3
	cmp byte [rdi - 2], spacecode
	je end
skip3:
	;; We have found a non-space character, therefore we need to store 1 in R9.
	mov r9, 1
	push rcx
	dec rdi						; After execution of repe function rdi points to the second symbol of the word
	inc rcx
	;; Find out the length of the current word
	mov rbx, rdi
	repne scasb
	jnz skip2
	dec rdi
	inc rcx
skip2:
	mov rcx, rdi
	sub rcx, rbx
	mov rdi, rbx

	;; Copy current word to it's new position
	xchg rsi, rdi
	rep movsb
	xchg rsi, rdi
	;; And add one space after it
	mov byte [rsi], ' '
	inc rsi

	pop rcx

	jmp loop
end:
	;; Decrement only if input string contains non-space characters
	test r9, 1
	jz skip1
	dec rsi
skip1:
	mov byte [rsi], 0
	ret
