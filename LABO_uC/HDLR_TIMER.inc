;;;;;;;;;;;;;;;;;;Handler interrupcion timer;;;;;;;;;;;;;;;;
timer_interrupt:
	push aux
	push aux2
	push aux3
	push aux4
	push aux5
	push r0
	push r1
	ldi aux,0
	out TCNT0,aux ;reseteo contador timer
	in aux5,sreg

;hallo pitch integrando gyro x
	lds aux,gyro_xh
	lds aux2,pitch_l
	lds aux3,pitch_h
	rcall suma_s16s8


;corrijo deriva con acelerometro
;filtro complementario: promedio ponderado (pgyro*7+pacc)/8
	ldi aux,7	
	rcall mul_signed16	;pgyro*7
	lds aux, pitch_acc
	neg aux	;mismo sentido que gyro
	ldi aux4,64
	muls aux,aux4 ;escalo a "angulo" de gyro
	add aux2,r0	;pgyro*7+pacc(escalado)
	adc aux3,r1
	ldi aux4,3
div_pitch:	;divido por 8
	asr aux3	;asr porque es signed
	ror aux2
	dec aux4
	brne div_pitch	

	sts pitch_h,aux3
	sts pitch_l,aux2

;hallo roll integrando gyro y
	lds aux,gyro_yh
	lds aux2,roll_l
	lds aux3,roll_h
	rcall suma_s16s8

;idem pitch para roll
	ldi aux,7	
	rcall mul_signed16
	lds aux, roll_acc
	neg aux	
	ldi aux4,64
	muls aux,aux4 
	add aux2,r0	
	adc aux3,r1
	ldi aux4,3
div_roll:
	asr aux3
	ror aux2
	dec aux4
	brne div_roll

	sts roll_h,aux3
	sts roll_l,aux2
	
	out sreg,aux5
	set
	pop r1
	pop r0
	pop aux5
	pop aux4
	pop aux3
	pop aux2
	pop aux
	reti
