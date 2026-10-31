section .bss
	VBA resb 64
section .text
global _start
extern print_number
_start:
	MOV qword [VBA + 0], 10 
	MOV qword [VBA + 8], 20 
	MOV RBX, qword [VBA + 0] 
	MOV qword [VBA + 16], RBX 
	MOV qword [VBA + 24], 20 
	MOV qword [VBA + 32], 2 
	MOV RAX, qword[VBA + 24] 
	MUL qword [VBA + 32] 
	MOV qword [VBA + 24], RAX 
	MOV RAX, qword [VBA + 16] 
	ADD RAX, qword [VBA + 24] 
	MOV qword [VBA + 16], RAX 
	MOV qword [VBA + 40], 20 
	MOV RAX, qword [VBA + 16] 
	SUB RAX, qword [VBA + 40] 
	MOV qword [VBA + 16], RAX 
	MOV RAX, qword [VBA + 16] 
	call print_number 
	MOV qword [VBA + 48], 10 
	MOV RAX, qword [VBA + 48] 
	call print_number 
exit_program:
MOV RAX, 60
MOV RDI, 0
syscall
