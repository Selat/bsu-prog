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
	mov al, byte [spc]

	mov rsi, rdi
	inc rsi
	jrcxz end
	repne scasb					; Search for the first space
	jrcxz end2					; If ecx = 0, than we finished scaning the string
	cmp rsi, rdi
	jne no_spaces
	dec rsi
	jmp loop
no_spaces:
	mov rsi, rdi
loop:
	jrcxz end					; If ecx = 0, than we finished scaning the string

	repe scasb					; Search for the beginning of the word after some spaces
	jz end
	dec rdi						; After execution of repe function rdi points to the second symbol of the word
	inc rcx

	;; Here we need to find out the length of the current word
	mov rbx, rdi
	mov r8, rdi
	repne scasb
	push rcx
	mov rcx, rdi
	sub rcx, rbx
	mov rdi, r8

	xchg rsi, rdi
	rep movsb
	xchg rsi, rdi
	mov byte [rsi], 0

	pop rcx

	jmp loop
end2:
	mov rsi, rdi
end:
	cmp byte [rsi], ' '
	jne skip1
	dec rsi
skip1:	mov byte [rsi], 0
	mov rax, rcx
	ret
