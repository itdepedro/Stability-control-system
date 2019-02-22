;;;;;;;;;;;;;;;;;;;;;;;CONFIG TIMER 0;;;;;;;;;;;;;;;;;;;;;;;;;;
;calculo output compare: (frec/preescaler)*t_timer=OCR0A
;nota: seteo a 8ms por conveniencia para escalar los valores
;del gyro y acc
configure_timer:
	push aux
	ldi aux,0
	out TCCR0A, aux
	ldi aux, (1<<CS02)|(1<<CS00) ; preescaler 1024
	out TCCR0B,aux
	ldi aux,144; 144 timer a 8ms
	out OCR0A,aux
	ldi aux, (1<<OCIE0A)
	sts TIMSK0,aux
	ldi aux,0
	out TCNT0,aux
	pop aux
	ret

