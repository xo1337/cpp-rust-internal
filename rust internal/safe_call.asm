.code

encrypt_or_decrypt proc

	; rax = return
	; rcx = value 
	; rbx = encrypted

	mov rbx, rcx

	; process encryption
	mov rax, rbx
	add rax, 8000000h
	xor rax, rbx
	add rax, rbx
	xor rax, 1024h
	sub rax, 18h
	cmp rax, 0
	jnz PROCESS_DECRYPTION

	; process decryption
PROCESS_DECRYPTION:
	add rax, 18h
	xor rax, 1024h
	sub rax, rbx
	xor rax, rbx
	sub rax, 8000000h
	cmp rax, rbx
	jmp PROCESS_REAL_ENCRYPTION

PROCESS_REAL_ENCRYPTION:
	xor rax, 2048
	xor rax, 1024
	xor rax, 512
	xor rax, 256
	xor rax, 128
	xor rax, 64
	xor rax, 32
	xor rax, 16
	xor rax, 8
	xor rax, 4
	xor rax, 2
	add rax, 4096

	sub rax, 4096
	xor rax, 2
	xor rax, 4
	xor rax, 8
	xor rax, 16
	xor rax, 32
	xor rax, 64
	xor rax, 128
	xor rax, 256
	xor rax, 512
	xor rax, 1024
	xor rax, 2048

	xor rax, 1024
	xor rax, 80
	xor rax, 48

	ret

encrypt_or_decrypt endp

do_safe_call proc
	
	push rbx

	mov rax, rcx
	sub rsp, 1024h
	add rsp, 1024h
	call encrypt_or_decrypt
	
	mov rbx, XOR1
	cmp rbx, rax
	jnz XOR1

XOR1:
	xor rax, 48
	xor rax, 80
	xor rax, 1024
	pop rbx
	jmp XOR2

XOR2:
	xor rax, 69
	xor rax, 69

	xor rax, 128
	xor rax, 69
	add rax, 12
	sub rax, 5
	shr rax, 2
	ror rax, 2

XOR3:
	rol rax, 2
	shl rax, 2
	add rax, 5
	sub rax, 12
	xor rax, 69
	xor rax, 128
	jmp ENCRYPTION1

ENCRYPTION1:	
	push rbx

	mov rbx, rax
	ror rax, 24
	shr rax, 8
	rol rax, 24
	shl rax, 5
	bswap rax
	shl rax, 5
	xor rax, 4
	shr rax, 12
	ror rax, 5
	shl rax, 22
	rol rax, 13
	shr rax, 12
	bswap rax
	shl rax, 51
	or rax, 2
	xor rax, 7fffh
	or rax, 56h
	shr rax, 75
	mov rax, rbx

	pop rbx

	ret

do_safe_call endp
end