segment .data
	_x dd 10
segment .bss
	_y resd 1
	__esp resd 1
segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float
; -----------------------
; PROCEDIMIENTO PRINCIPAL
; -----------------------
main:
; GUARDA DE PUNTERO DE PILA
	mov dword [__esp] , esp


	mov dword [_y], 9

	push dword [_x]
	call print_int
	add esp, 4
	call print_endofline


	push dword 100
	call print_int
	add esp, 4
	call print_endofline


	push dword [_y]
	call print_int
	add esp, 4
	call print_endofline


; RESTAURACIÓN DE PUNTERO DE PILA
	mov dword esp, [__esp]
	ret
