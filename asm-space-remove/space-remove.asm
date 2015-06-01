	extern strlen

	segment .data
%define spacecode 32
%define semicoloncode 59

	segment .text

	global solve

solve:
	push rdi
	push rdi
	call strlen
	pop rdi
	mov rcx, rax
	inc rcx
	mov al, spacecode
	xor r9, r9					; R9 : bool - found any non-space characters in the string.

	;; Remove all unnecessary spaces
	;; 'loop' cycle invariant:
	;; RSI - current insert position
	;; RDI - first space position

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
	dec rdi						; After execution of repe function rdi points to the second symbol of the word
	inc rcx
	;; Find out the length of the current word
	mov rbx, rdi
	repne scasb
	jnz skip2
	dec rdi
	inc rcx
skip2:
	push rcx
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

	;; Add one space after each semicolon
	pop rdi
	push rdi
	call strlen
	pop rdi
	mov rcx, rax
	push rcx

	;; RBX stores number of spaces to add
	push rdi
	xor rbx, rbx
	mov al, semicoloncode
	inc rcx
lcntsemicolon:
	jrcxz endcntsemicolon
	repne scasb
	jnz lcntsemicolon
	cmp byte [rdi], spacecode
	je lcntsemicolon
	inc rbx
	jmp lcntsemicolon

endcntsemicolon:
	pop rdi
	pop rcx
	mov rsi, rdi
	add rsi, rcx
	dec rsi
	add rdi, rcx
	add rdi, rbx
	dec rdi
	mov byte [rdi + 1], 0
	;; Set direction bit, because we neeed to decrement addresses
	inc rcx
	std
lmovesemicolons:
	cmp rbx, 0
	je end2

	;; Firstly we need to find out the length of the string that we should copy
	push rsi
	push rdi
	xchg rsi, rdi
	mov r9, rdi
	repne scasb
	sub r9, rdi
	xchg rsi, rdi
	dec r9
	jrcxz skip4
	;; dec r9
skip4:
	pop rdi
	pop rsi
	push rcx

	;; Than we just copy an array of bytes of known length
	mov rcx, r9
	rep movsb
	pop rcx
	mov byte [rdi], spacecode
	mov byte [rdi - 1], semicoloncode
	dec rbx
	dec rsi
	sub rdi, 2

	jmp lmovesemicolons
end2:
	cld
	mov rax, rbx
	ret
