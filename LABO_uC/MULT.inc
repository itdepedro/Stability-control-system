MULT:
	push 	r0	;MULTIPLICA 2 BYTES Y SOLO ME QUEDO CON PARTE ALTA
	push 	r1
loop_mul_45:	
	mul 	aux,aux3
	mov 	aux,r1
	pop		r1
	pop		r0
	ret
