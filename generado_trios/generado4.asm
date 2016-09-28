segment .data
	_b3 dd 0
segment .bss
	_b1 resd 1
	_b2 resd 1
	__esp resd 1
segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float
main:
	mov dword [__esp] , esp
	
	push dword _b1
	call scan_boolean
	add esp, 4

	push dword _b2
	call scan_boolean
	add esp, 4

	push dword [_b2]
	push dword [_b1]

	pop dword eax
	pop dword ebx
	and eax, ebx
	push dword eax
	pop dword eax
	
		
	cmp eax, 0 ; eax == 0?
	jz _poner1_0 
	push dword 0     ; si eax es 1, res = 0
	jmp _poner1_fin_0
_poner1_0:
	push dword 1   ; si eax es 0, res = 1	
_poner1_fin_0:	

	pop dword [_b3]


	push dword [_b3]
	call print_boolean
	add esp, 4
	call print_endofline
	mov dword esp, [__esp]
	ret
