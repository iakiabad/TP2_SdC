.global _sumar_uno
.text

_sumar_uno:
		pushq %rbp
		movq %rsp, %rbp

		pushq %rdi
		addq $1, -8(%rbp)
		popq %rax

		# movq %rbp, %rsp , no hace falta porque despues de popq %rax, el tope de la pila ya está apuntado por %rbp
		popq %rbp
		ret
