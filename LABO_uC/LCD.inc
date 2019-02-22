;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;BEGIN LCD;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

configure_LCD:
	push 	aux

	rcall 	delay_50000
	rcall 	delay_50000
	rcall	delay_50000

	ldi 	aux,0x30
	rcall 	write_LCD
	rcall	delay_50000
	ldi 	aux,0x30
	rcall 	write_LCD
	rcall	delay_50000
	ldi 	aux,0x30
	rcall 	write_LCD
	rcall	delay_50000

;INICIALIZACION LCD EN MODO 4 BITS

	ldi		aux,0x20	
	rcall	write_LCD
	rcall	delay_50000

	ldi		aux,0x28
	rcall	send_LCD_CMND
	rcall	delay_50000	; 
			
	ldi		aux,0x08
	rcall	send_LCD_CMND
	rcall	delay_50000

	ldi		aux,0x01
	rcall	send_LCD_CMND
	rcall	delay_50000

	ldi		aux,0x0C
	rcall	send_LCD_CMND
	rcall	delay_50000

	ldi		aux,0x06
	rcall	send_LCD_CMND
	rcall	delay_50000

	pop 	aux
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
write_LCD:

	push 	aux2

	in		aux2,PORTD
	andi	aux2,0x0F
	or		aux2,aux
	out		PORTD,aux2
	
	sbi		PORTD,3			;SET E
	cbi		PORTD,3			;CLR E
	
	rcall 	delay_50

	pop		aux2
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

send_LCD_CMND:

	cbi		PORTD,2

	push	aux
	andi	aux,0xF0
	rcall 	write_LCD
	pop		aux

	swap	aux
	andi	aux,0xF0
	rcall	write_LCD

	cbi		PORTD,2
	ret	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
send_LCD_DATA:

	sbi		PORTD,2

	push	aux
	andi	aux,0xF0
	rcall 	write_LCD
	pop		aux

	swap	aux	
	andi	aux,0xF0
	rcall	write_LCD

	cbi		PORTD,2
	ret		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

PRINT_CAL:					;IMPRIMIR MENSAJE CALIBRANDO SENSOR EN LCD
	push   	aux
	ldi		aux,0x83
	rcall	send_LCD_CMND
	rcall	delay_50000

	ldi		zl,LOW(msg_cal_1<<1)  	;EN ROM
	ldi		zh,HIGH(msg_cal_1<<1)	
LOOP_PRINT_MSG_CAL_1:
	lpm		aux,z+
	cpi 	aux,0
	breq	fin_PRINT_MSG_CAL_1
	rcall 	SEND_LCD_DATA
	rcall 	delay_50000
	rjmp 	LOOP_PRINT_MSG_CAL_1

FIN_PRINT_MSG_CAL_1:

	ldi		aux,0xC5
	rcall	send_LCD_CMND
	rcall	delay_50000


	ldi		zl,LOW(msg_cal_2<<1)	;EN ROM 
	ldi		zh,HIGH(msg_cal_2<<1)
LOOP_PRINT_MSG_CAL_2:
	rcall 	delay_50000
	lpm		aux,z+
	cpi 	aux,0
	breq	fin_PRINT_MSG_CAL_2
	rcall 	SEND_LCD_DATA
	rjmp 	LOOP_PRINT_MSG_CAL_2

FIN_PRINT_MSG_CAL_2:

	pop		aux
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

MSG_FUN:
	push	aux
	lds		aux,FUNCTION
	cpi		aux,1
	breq	FUN_1_MSG
	cpi		aux,2
	breq	FUN_2_MSG
END_MSG_FUN:
	pop		aux
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
	
FUN_1_MSG:										;MENSAJE FUNCION
	
	ldi		aux,0x8D
	rcall	send_LCD_CMND
	rcall	delay_50000

	ldi		zl,LOW(msg_fun_1<<1)
	ldi		zh,HIGH(msg_fun_1<<1)
LOOP_FUN_MSG_1:
	rcall 	delay_50000
	lpm		aux,z+
	cpi 	aux,0
	breq	END_MSG_FUN
	rcall 	SEND_LCD_DATA
	rjmp 	LOOP_FUN_MSG_1

FUN_2_MSG:

	ldi		aux,0x8D
	rcall	send_LCD_CMND
	rcall	delay_50000

	ldi		zl,LOW(msg_fun_2<<1)
	ldi		zh,HIGH(msg_fun_2<<1)
LOOP_FUN_MSG_2:
	rcall 	delay_50000
	lpm		aux,z+
	cpi 	aux,0
	breq	END_MSG_FUN
	rcall 	SEND_LCD_DATA
	rjmp 	LOOP_FUN_MSG_1


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

PRINT_MSG:										;MENSAJE SERVO 1: SERVO 2:
	push   	aux

	ldi		aux,0x80
	rcall	send_LCD_CMND
	rcall	delay_50000

	ldi		zl,LOW(msg_1<<1)
	ldi		zh,HIGH(msg_1<<1)
LOOP_PRINT_MSG_1:
	rcall 	delay_50000
	lpm		aux,z+
	cpi 	aux,0
	breq	fin_PRINT_MSG_1
	rcall 	SEND_LCD_DATA
	rjmp 	LOOP_PRINT_MSG_1

FIN_PRINT_MSG_1:

	ldi		aux,0xC0
	rcall	send_LCD_CMND
	rcall	delay_50000

	ldi		zl,LOW(msg_2<<1)
	ldi		zh,HIGH(msg_2<<1)
LOOP_PRINT_MSG_2:
	rcall 	delay_50000
	lpm		aux,z+
	cpi 	aux,0
	breq	fin_PRINT_MSG_2
	rcall 	SEND_LCD_DATA
	rjmp 	LOOP_PRINT_MSG_2

FIN_PRINT_MSG_2:

	pop		aux
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


CLEAR_LCD:
	push	aux
	ldi		aux,0x01
	rcall	send_LCD_CMND
	rcall	delay_50000
	pop 	aux
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LCD_POS:										;IMPRIME POSICION ANGULAR
	
	push   	aux
	ldi		xl,low(GRAD_SGN)
	ldi		xh,high(GRAD_SGN)
	ld		aux,x
	rcall	SEND_LCD_DATA
	rcall 	delay_50000

	ldi		xl,low(GRAD_STR)
	ldi		xh,high(GRAD_STR)
	ld		aux,x+
	rcall	SEND_LCD_DATA
	rcall 	delay_50000
	ld		aux,x+
	rcall	SEND_LCD_DATA
	rcall 	delay_50000
	ld		aux,x
	rcall	SEND_LCD_DATA
	rcall 	delay_50000
	

	pop 	aux
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

msg_1: 	.db "SERVO 1:",0
msg_2:	.db "SERVO 2:",0
msg_cal_1: 	.db "CALIBRANDO",0
msg_cal_2:	.db "SENSOR",0
msg_fun_1:	.db "MPU",0
msg_fun_2:	.db "ADC",0
