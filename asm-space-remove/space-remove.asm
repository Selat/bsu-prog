	extern strlen

	segment .data
send:	db '\;'
spc:	db ' '

	segment .text

	global solve

solve:
	push rdi
	call strlen
	pop rdi
	mov rcx, rax
	inc rcx
	mov al, byte [spc]

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

	repe scasb					; Search for the beginning of the word after some spaces
	cmp rcx, 0
	jne skip3
	cmp byte [rdi - 1], 0
	jne skip3
	cmp byte [rdi - 2], 32
	je end
skip3:
	;; jrcxz end
	push rcx
	dec rdi						; After execution of repe function rdi points to the second symbol of the word
	inc rcx
	;; Here we need to find out the length of the current word
	mov rbx, rdi
	repne scasb
	jnz skip2
	dec rdi
	inc rcx
skip2:
	mov rcx, rdi
	sub rcx, rbx
	mov rdi, rbx

	xchg rsi, rdi
	rep movsb
	xchg rsi, rdi
	mov byte [rsi], ' '
	inc rsi

	pop rcx

	jmp loop
end2:
	mov rsi, rdi
end:
	;; cmp byte [rsi], ' '
	;; jne skip1
	dec rsi
skip1:	mov byte [rsi], 0
	mov rax, rcx
	ret
