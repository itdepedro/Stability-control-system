;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;BEGIN ADC;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
configure_ADC:
	push 	aux
	ldi 	aux,(1 << REFS0)|(1 << ADLAR)
	sts 	ADMUX, aux
	ldi		aux,(1 << ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);hablita ADC, single convertion, disable autotrigger, disable ADC interrupt
	sts		ADCSRA, aux
	pop 	aux
	ret 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
read_ADC:

	push 	aux

 	lds		aux,ADMUX
	andi	aux,0xF8 ;enable ADC0
	sts		ADMUX,aux

	lds		aux, ADCSRA
	ori		aux, (1 << ADSC) ;enable single convertion
	sts		ADCSRA,aux

loop_read_ADC_0:

	lds 	aux,ADCSRA		
	sbrs	aux,ADIF ;skip si termino la conversion
	rjmp 	loop_read_ADC_0

	lds 	aux,ADCSRA
	ori		aux,(1<<ADIF)|(1<<ADEN) ;limpio ADIF seteandolo 
	sts 	ADCSRA, aux

	lds		aux,ADCL
	lds		aux,ADCH
	sts		ADC_value_0,aux ; guardo el resultado en registro RAM

	lds		aux,ADMUX
	andi	aux,0xF8
	ori		aux,(1<<MUX0);habilito ADC1
	sts		ADMUX,aux

	lds		aux, ADCSRA
	ori		aux, (1 << ADSC) ;habilito single convertion
	sts		ADCSRA,aux

loop_read_ADC_1:

	lds		aux,ADCSRA
	sbrs	aux,ADIF 		;skip si termino la conversion
	rjmp 	loop_read_ADC_1

	lds 	aux,ADCSRA
	ori		aux,(1<<ADIF)|(1<<ADEN);limpio flag 
	sts 	ADCSRA, aux
	
	lds		aux,ADCL
	lds		aux,ADCH
	sts		ADC_value_1,aux ;guardo resultado en registro RAM

	pop 	aux
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
