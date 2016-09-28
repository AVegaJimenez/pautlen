segment .data
	_y dd 10
segment .bss
	_x resd 1
	__esp resd 1
segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float
main:
	mov dword [__esp] , esp
	
	mov dword [_x], 8
	
	push dword _x
	call scan_int
	add esp, 4

	push dword [_y]
	push dword 2
	push dword [_x]
	pop dword eax
	pop dword ebx
	imul ebx
	push dword eax
	pop dword eax
	pop dword ebx
	sub eax, ebx
	push dword eax
	pop dword [_x]
	

	push dword [_x]
	call print_int
	add esp, 4
	call print_endofline
	mov dword esp, [__esp]
	ret
