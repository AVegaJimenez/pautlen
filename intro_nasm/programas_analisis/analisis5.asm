segment .data
	msg_hola_mundo     db "HOLA MUNDO", 0
	msg_adios_madrid     db "ADIOS MADRID", 0
segment .bss
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
	mov dword [__esp], esp

	push dword msg_hola_mundo
	call print_string
	add esp, 4	
	call print_endofline

	push dword msg_adios_madrid
	call print_string
	add esp, 4	
	call print_endofline


fin: 
	mov dword esp, [__esp]
	ret
