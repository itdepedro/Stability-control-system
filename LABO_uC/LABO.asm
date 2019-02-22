.include "m88pdef.inc"


.def aux = r16
.def aux2= r17
.def aux3= r18
.def aux4= r19
.def aux5= r21
.def com_reg = r20

.equ slv_r = 0b11010001
.equ slv_w = 0b11010000
.equ xacch = 59
.equ xaccl = 60
.equ yacch = 61
.equ yaccl = 62
.equ zacch = 63
.equ zaccl = 64
.equ xgyroh = 67
.equ xgyrol = 68
.equ ygyroh = 69
.equ ygyrol = 70
.equ zgyroh = 71
.equ zgyrol = 72


.dseg
.org	SRAM_START
;variables gyro/acc
gyro_xh:	.byte 1 
gyro_xl:	.byte 1
gyro_yh:	.byte 1
gyro_yl:	.byte 1
gyro_zh:	.byte 1
gyro_zl:	.byte 1
acc_xh:	.byte 1
acc_xl:	.byte 1
acc_yh:	.byte 1
acc_yl:	.byte 1
acc_zh:	.byte 1
acc_zl:	.byte 1
roll_h: .byte 1
roll_l: .byte 1
pitch_l: .byte 1
pitch_h: .byte 1
roll_acc: .byte 1
pitch_acc: .byte 1
roll: .byte 1
pitch: .byte 1
PWM_value: .byte 1

;calibracion del gyro/acc
off_gyro_xh:	.byte 1 
off_gyro_xl:	.byte 1
off_gyro_yh:	.byte 1
off_gyro_yl:	.byte 1
off_gyro_zh:	.byte 1
off_gyro_zl:	.byte 1
off_acc_xh:	.byte 1
off_acc_xl:	.byte 1
off_acc_yh:	.byte 1
off_acc_yl:	.byte 1
off_acc_zh:	.byte 1
off_acc_zl:	.byte 1

FUNCTION:	.byte 1
GRAD_STR:	.byte 3
GRAD_SGN:	.byte 1
ADC_value_0: .byte 1
ADC_value_1: .byte 1



.cseg
.org 0x0000
	rjmp	inicio
.org 0x00E ;timer0 compa interrupt
	rjmp	timer_interrupt

.org INT_VECTORS_SIZE
inicio:

tabla_atan: 
.db 0,1,2,3,4,4,5,6,7,8,9,10,11,11,12,13,14,15,16,17,17,18,19,20,21,21,22,23,24,24,25,26,27,27,28,29,29,30,31,31,32,33,33,34,35,35,36,36,37,37,38,39,39,40,40,41,41,42,42,43,43,44,44,45,45,45
	; Inicializar Stack
	ldi  aux, low(RAMEND)
	out  SPL, aux
	ldi  aux, high(RAMEND)
	out  SPH, aux

	ldi		aux,1
	sts		FUNCTION,aux

	; Inicializar Perisfericos
   	rcall configure_ports
	rcall configure_LCD
	rcall PRINT_CAL
	rcall configure_I2C
	rcall configure_UART
	rcall configure_timer
	rcall configure_PWM
	rcall configure_ADC

	; Inicializar MPU-6050
	rcall init_mpu
	rcall calibrar_mpu
	;limpio LCD
	rcall CLEAR_LCD
	
	; Inicializar variables
	ldi aux,0
	sts roll_h,aux
	sts roll_l,aux
	sts pitch_h,aux
	sts pitch_l,aux
	sts pitch_acc,aux
	sts roll_acc,aux
	sts roll,aux
	sts pitch,aux

	sei ;habilito interrupciones
	
	rcall PRINT_MSG
	rcall MSG_FUN

main_loop:


end:
	rcall 	POL
	lds		aux,FUNCTION
	cpi		aux,1
	breq	FUN_1
	cpi		aux,2
	breq	FUN_2
	rjmp 	end


FUN_1:
	rcall read_gyro
	rcall read_acc
	rcall angulo_acc
	rcall escalo_pr
	rcall PWM_CHANGE_0
	rcall PWM_CHANGE_1
	brtc nomando
	lds com_reg,pitch
	rcall write_uart
	clt
nomando:
	rjmp end
	
FUN_2:
	push aux3
	ldi	aux2,0
	rcall read_ADC
	lds	aux,ADC_value_0
	lsr	aux
	ldi aux3,57
	add aux,aux3
	rcall SEND_PWM_0
	lds	aux,ADC_value_1
	lsr	aux
	ldi aux3,57
	add aux,aux3
	rcall SEND_PWM_1
	pop aux3
	rjmp end



POL:
	push 	aux
	sbis	PINB,0
	rjmp	INC_FUN	
END_POL:
	pop aux
	ret


INC_FUN:
	sbis	PINB,0
	rjmp	INC_FUN
	lds		aux,FUNCTION
	inc		aux
	cpi		aux,3
	breq	RST_FUN
END_INC_FUN:
	sts		FUNCTION,aux
	rcall	MSG_FUN
	rjmp	END_POL



RST_FUN:
	ldi		aux,1
	rjmp	END_INC_FUN


.include "MULT.inc"
.include "DELAYS.inc"
.include "HDLR_TIMER.inc"
.include "PWM.inc"
.include "SUM_S16_S8.inc"
.include "GYRO.inc"
.include "PORTS.inc"
.include "MPU.inc"
.include "I2C.inc"
.include "TIMER0.inc"
.include "UART.inc"
.include "LCD.inc"
.include "PWM_TO_LCD.inc"
.include "INT_TO_STR.inc" 
.include "ADC.inc"
