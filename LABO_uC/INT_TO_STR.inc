INT_TO_STR:
	push	aux
	push 	r18 
	push 	r19	
	push 	r20

	clr		r18 ;limpio registros
	clr		r19
	clr		r20

	push 	r21	;auxiliar para el 100 y el 10 para 

	ldi 	r21,100
loop_division_100:

	sub 	aux,r21
	brlo 	fin_100
	inc 	r18				;centena
	rjmp 	loop_division_100

fin_100:
	add 	aux,r21	
	ldi 	r21,10

loop_division_10:
	sub 	aux,r21
	brlo 	fin_10	
	inc 	r19				;decenas
	rjmp 	loop_division_10
	
fin_10:
	add 	aux,r21
	mov 	r20,aux			;unidades 
	ldi		aux,48			;los shifteo ascii
	ldi 	xl,low(GRAD_STR)	;guardo las variables en RAM
	ldi 	xh,high(GRAD_STR)
	add		r18,aux
	st		x+,r18
	add		r19,aux
	st 		x+,r19
	add		r20,aux
	st		x,r20


	pop 	r21
	pop 	r20
	pop 	r19
	pop 	r18
	pop		aux
	ret
