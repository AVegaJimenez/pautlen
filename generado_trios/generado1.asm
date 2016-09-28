segment .data
	_x dd 8
segment .bss
	__esp resd 1
segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float
main:
	mov dword [__esp] , esp
	push dword [_x]
	call print_int
	add esp, 4
	call print_endofline
	mov dword esp, [__esp]
	ret
