;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;CONFIG PORTS;;;;;;;;;;;;;;;;;;;;;;;;	
configure_ports:
	push 	aux
	
	ldi 	aux,(1 << DDB1) | (1 << DDB2)
	out 	DDRB,aux
	
	ldi 	aux,(0 << DDC1) | (1 << DDC3)
	out		DDRC,aux
	
	ldi		aux,(1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7) ;LCD data_PIN
	ori		aux,(1 << DDD2)	;RS
	ori		aux,(1 << DDD3)	;E
	out 	DDRD,aux
	
	pop 	aux
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
