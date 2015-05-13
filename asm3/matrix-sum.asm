	segment .text

	global test1

test1:
	mov rbx, rdi				; Load into rbx pointer to the first element of the matrix
	xor r9, r9					; Load into r9 number of columns in the matrix
	mov r14, rdx
	xor rax, rax

	mov r11, rcx				; Load into r11 pointer to the array in which we are going
								; to store ids of columns with max sum of elements
	mov DWORD [r11], 8

	mov r13, r8					; Load into r13 address of variable which stores number of
								; columns with maximum sum of elements
	xor r12, r12				; In r12 we are going to store number of columns with
								; maximum sum of elements

	mov r8, rsi					; Calculate in r8 shift to the next row of the matrix
	shl r8, 2

	xor r10, r10	   			; In r10 we store maximum sum of column elements

l_columns:
	cmp r9, r14					; Store temporary value of rcx in r9
	je end

	mov rcx, rsi				; Load into rcx number of rows in the matrix
	xor rax, rax
	mov rbx, rdi

l_sum_column:					; Calculate sum of the elements in the current columnn
	add eax, [rbx]
	add rbx, r8
	loop l_sum_column

	cmp rax, r10				; Update maximum sum of column's elements
	jle less_or_equal
	mov r10, rax
	shl	r12, 2					; Restore pointer to the array of ids to it's initial value
	sub r11, r12
	xor r12, r12
	jmp add_new_column_id

less_or_equal:
	jne less_max

add_new_column_id:
	mov [r11], r9				; Write new column id to the end of the array
	add r11, 4					; Move pointer of the array to the next element
	inc r12						; Increase number of elements in the array

less_max:
	add rdi, 4
	inc r9
	jmp l_columns
end:
	mov DWORD [r13], r12d
	mov rax, r10				; Return maximum sum of column's elements
	ret
