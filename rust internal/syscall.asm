PUBLIC syscall_stub

.code

syscall_stub proc
	mov r10, rcx
	mov eax, [rsp+28h]
	add rsp, 8h
	syscall
	sub rsp, 8h
	ret
syscall_stub endp

end