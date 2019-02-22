
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Actualizo PWM;;;;;;;;;;;;;;;
PWM_change_0:
	push 	aux2
	push 	aux
	push 	aux3
	lds		aux,pitch			;ESCALAR PITCH A PWM
	ldi 	aux2,90			
	add 	aux,aux2
	ldi 	aux3,180
	rcall 	MULT		
	ldi		aux2,58
	add 	aux,aux2			;ESCALAR PITCH A PWM
	ldi 	aux2,0
	rcall	SEND_PWM_0
	pop 	aux3
	pop 	aux
	pop 	aux2
	ret

PWM_change_1:
	push 	aux2
	push 	aux
	push 	aux3
	lds		aux,roll			;ESCALAR ROLL A PWM
	ldi 	aux2,90
	add 	aux,aux2
	ldi 	aux3,180
	rcall 	MULT
	ldi		aux2,58
	add 	aux,aux2			;ESCALAR ROLL A PWM
	ldi 	aux2,0
	rcall	SEND_PWM_1
	pop 	aux3
	pop 	aux
	pop 	aux2
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
SEND_PWM_0:					;ENVIO VALOR A PWM E IMPRIMO EN LCD 
	
	sts 	OCR1AH,aux2
	sts		OCR1AL,aux
	rcall	PWM_TO_LCD
	rcall	INT_TO_STR
	ldi		aux,0x88
	rcall	send_LCD_CMND
	rcall	delay_50000
	rcall	LCD_POS
	ret

SEND_PWM_1:

	sts 	OCR1BH,aux2
	sts		OCR1BL,aux
	rcall	PWM_TO_LCD
	rcall	INT_TO_STR
	ldi		aux,0xC8
	rcall	send_LCD_CMND
	rcall	delay_50000
	rcall	LCD_POS
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

configure_PWM:
	push 	aux
	ldi 	aux,1
	sts 	TCNT1H,aux
	sts 	TCNT1L,aux
	ldi 	aux,0xE8
	sts 	ICR1H,aux
	ldi 	aux,0x0B
	sts 	ICR1L,aux
	ldi 	aux,(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11)|(1<<WGM10)
	sts 	TCCR1A,aux

	ldi 	aux,(1<<WGM12)|(1<<CS22)|(0<<CS21)|(0<<CS20)
	;si bien es redundante orear 0's, lo hago para que la funcion este lista
	;para futuras modificaciones
	sts		TCCR1B,aux

	ldi 	aux,0				;valor inicial PWM
	sts 	OCR1AH,aux
	ldi		aux,110
	sts 	OCR1AL,aux
	ldi 	aux,0
	sts 	OCR1BH,aux
	ldi		aux,110
	sts 	OCR1BL,aux
	pop		aux

	ret


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
