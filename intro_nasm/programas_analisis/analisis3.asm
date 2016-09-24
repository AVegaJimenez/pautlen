segment .data
segment .bss
	_x resd 1
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
	mov dword [__esp] , esp

; SE DA VALOR A LAS VARIABLES
	mov dword [_x] , 11
	mov dword [_y] , 22

; SE REALIZAR LA OPERACIÓN x+3-y

	push dword [_y]
	push dword 3
	push dword [_x]
	
	pop dword eax
	pop dword ebx
	add eax, ebx
	push dword eax

	pop eax
	pop ebx
	sub eax, ebx
	push dword eax




	call print_int
	add esp, 4
	call print_endofline

	mov dword esp, [__esp]
	ret
