;;;;;;;;;;;;;;;;;CONFIG UART;;;;;;;;;;;;;;;;;;;;;
configure_UART:
	push aux
	ldi aux,0
	sts UBRR0H, aux
	ldi aux,119
	sts UBRR0L, aux
	ldi aux, (1<<UCSZ00)|(1<<UCSZ01)
	sts UCSR0C,aux
	ldi aux, (1<<TXEN0)|(1<<RXEN0)
	sts UCSR0B,aux
	ldi aux, 0
	sts UCSR0A, aux
	pop aux
	ret
write_uart:
	push aux
	waitwuart:
	lds aux,UCSR0A
	sbrs aux,UDRE0
	rjmp waitwuart
	sts UDR0,com_reg
	pop aux
	ret
read_uart:
	push aux
	lds aux,UCSR0A
	sbrs aux,RXC0
	rjmp no_data
	lds com_reg,UDR0
	no_data:
	pop aux
	ret

