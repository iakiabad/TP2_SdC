.global _sumar_uno
.text

_sumar_uno:
		addq $1, %rdi
		movq %rdi, %rax
		ret
