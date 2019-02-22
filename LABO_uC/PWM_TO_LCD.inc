PWM_TO_LCD:
				;TRANSFORMA VALOR DE PWM A STRING PARA IMPIRMIR EN LCD
	push aux3
	subi aux,57			;ESCALA PWM A 0 180
	ldi	aux3,181

	push 	r0
	push 	r1		
	mul 	aux,aux3
	rol 	r0
	rol		r1
	mov 	aux,r1
	pop		r1
	pop		r0

	cpi aux,90
	brlo NEG_PWM_TO_LCD			;DETECTO SIGNO 
	ldi	 aux3,0x2B
	sts  GRAD_SGN,aux3
	subi aux,90

END_PWM_TO_LCD:	
	pop aux3
	ret


NEG_PWM_TO_LCD:
	ldi	aux3,0x2D
	sts GRAD_SGN,aux3
	ldi	aux3,90
	sub	aux3,aux
	mov aux,aux3
	rjmp END_PWM_TO_LCD
	
