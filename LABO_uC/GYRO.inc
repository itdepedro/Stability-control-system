
;;;;;;;;;;;;;;;;;;;;;AJUSTE OFFSET ACCEL/GYRO;;;;;;;;;;;;;;;;;;;
calibrar_mpu:
	push	aux
	push	aux2
	push	aux3
	push	aux4
	push	aux5

	clr		aux
	clr		aux2
	clr		aux4
	clr		aux5
	ldi		aux3,16	;Contador de muestras
sum_xacc:
	ldi com_reg,xacch
	rcall read_reg
	subi	com_reg,128
	add		aux,com_reg	
	clr		com_reg		
	adc		aux2,com_reg
	ldi com_reg,xaccl
	rcall read_reg
	add		aux4,com_reg
	clr		com_reg		
	adc		aux5,com_reg
	rcall delay_10ms
	dec		aux3
	brne	sum_xacc
	ldi		aux3,4
div_xacc:	
	lsr		aux2
	ror		aux
	lsr 	aux5
	ror		aux4
	dec		aux3	
	brne	div_xacc
	subi aux,128
	sts off_acc_xh, aux
	sts off_acc_xl, aux4
	clr		aux
   	clr		aux2
	clr		aux4
	clr		aux5
	ldi		aux3,16	;Contador de muestras
sum_yacc:
	ldi com_reg,yacch
	rcall read_reg
	subi	com_reg,128
	add		aux,com_reg	
	clr		com_reg		
	adc		aux2,com_reg
	ldi com_reg,yaccl
	rcall read_reg
	add		aux4,com_reg
	clr		com_reg		
	adc		aux5,com_reg
	rcall delay_10ms
	dec		aux3
	brne	sum_yacc
	ldi		aux3,4
div_yacc:	
	lsr		aux2
	ror		aux
	lsr 	aux5
	ror		aux4
	dec		aux3	
	brne	div_yacc
	subi aux,128
	sts off_acc_yh, aux
	sts off_acc_yl, aux4

	clr		aux
    clr		aux2
	clr		aux4
	clr		aux5
	ldi		aux3,16	;Contador de muestras
sum_zacc:
	ldi com_reg,zacch
	rcall read_reg
	subi	com_reg,128
	add		aux,com_reg	
	clr		com_reg		
	adc		aux2,com_reg
	ldi com_reg,zaccl
	rcall read_reg
	add		aux4,com_reg
	clr		com_reg		
	adc		aux5,com_reg
	rcall delay_10ms
	dec		aux3
	brne	sum_zacc
	ldi		aux3,4
div_zacc:	
	lsr		aux2
	ror		aux
	lsr 	aux5
	ror		aux4
	dec		aux3	
	brne	div_zacc
	subi aux,192 ;128(para expresar como signed)+64 porque el eje z lee 1G en pos. neutral
	sts off_acc_zh, aux
	sts off_acc_zl, aux4

	clr		aux
    clr		aux2
	clr		aux4
	clr		aux5
	ldi		aux3,16	;Contador de muestras
sum_xgyro:
	ldi com_reg,xgyroh
	rcall read_reg
	subi	com_reg,128
	add		aux,com_reg	
	clr		com_reg		
	adc		aux2,com_reg
	ldi com_reg,xgyrol
	rcall read_reg
	add		aux4,com_reg
	clr		com_reg		
	adc		aux5,com_reg
	rcall delay_10ms
	dec		aux3
	brne	sum_xgyro
	ldi		aux3,4
div_xgyro:	
	lsr		aux2
	ror		aux
	lsr 	aux5
	ror		aux4
	dec		aux3	
	brne	div_xgyro
	subi aux,128
	sts off_gyro_xh, aux
	sts off_gyro_xl, aux4
	clr		aux
    clr		aux2
	clr		aux4
	clr		aux5
	ldi		aux3,16	;Contador de muestras
sum_ygyro:
	ldi com_reg,ygyroh
	rcall read_reg
	subi	com_reg,128
	add		aux,com_reg	
	clr		com_reg		
	adc		aux2,com_reg
	ldi com_reg,ygyrol
	rcall read_reg
	add		aux4,com_reg
	clr		com_reg		
	adc		aux5,com_reg
	rcall delay_10ms
	dec		aux3
	brne	sum_ygyro
	ldi		aux3,4
div_ygyro:	
	lsr		aux2
	ror		aux
	lsr 	aux5
	ror		aux4
	dec		aux3	
	brne	div_ygyro
	subi aux,128
	sts off_gyro_yh, aux
	sts off_gyro_yl, aux4
	clr		aux
    clr		aux2
	clr		aux4
	clr		aux5
	ldi		aux3,16	;Contador de muestras
sum_zgyro:
	ldi com_reg,zgyroh
	rcall read_reg
	subi	com_reg,128
	add		aux,com_reg	
	clr		com_reg		
	adc		aux2,com_reg
	ldi com_reg,zgyrol
	rcall read_reg
	add		aux4,com_reg
	clr		com_reg		
	adc		aux5,com_reg
	rcall delay_10ms
	dec		aux3
	brne	sum_zgyro
	ldi		aux3,4
div_zgyro:	
	lsr		aux2
	ror		aux
	lsr 	aux5
	ror		aux4
	dec		aux3	
	brne	div_zgyro
	subi aux,128
	sts off_gyro_zh, aux
	sts off_gyro_zl, aux4
	pop		aux5
	pop		aux4
	pop		aux3
	pop		aux2
	pop		aux
	ret
;;;;;;;;;;;;;;;;;;;LEER GYRO/ACC;;;;;;;;;;;;;;;;;;;;
read_gyro:
	push com_reg
	push aux
	ldi com_reg,xgyroh
	rcall read_reg
	lds aux,off_gyro_xh
	sub com_reg,aux
	sts gyro_xh,com_reg
	ldi com_reg,ygyroh
	rcall read_reg
	lds aux,off_gyro_yh
	sub com_reg,aux
	sts gyro_yh,com_reg
	pop aux
	pop com_reg
	ret
read_acc:
	push com_reg
	push aux
	ldi com_reg,xacch
	rcall read_reg
	lds aux,off_acc_xh
	sub com_reg,aux
	sts acc_xh,com_reg
	ldi com_reg,yacch
	rcall read_reg
	lds aux,off_acc_yh
	sub com_reg,aux
	sts acc_yh,com_reg
	ldi com_reg,zacch
	rcall read_reg
	lds aux,off_acc_zh
	sub com_reg,aux
	sts acc_zh,com_reg
	pop aux
	pop com_reg
	ret

;;;;;;;;;;;;;;;;;;;;;OBTENCION ANGULO ACC;;;;;;;;;;;;;;;;;;;;;;;
angulo_acc:
	push aux
	push aux2
	push aux3
	lds aux3,acc_zh ;z siempre pos para el rango usado
	lds aux,acc_xh
	rcall calculo_atan
	sts roll_acc,aux
	lds aux3,acc_zh ;z siempre pos para el rango usado
	lds aux,acc_yh
	rcall calculo_atan
	sts pitch_acc,aux
	pop aux3
	pop aux2
	pop aux
	ret

;;;;;;;;;;;;;;Calculo atan por tabla;;;;;;;;;;;;;;;;;
calculo_atan:
	push aux4
	clr aux4
	sbrs aux,7 ;salteo si es negativo
	rjmp incl_pos
	neg aux
	ldi aux4,1 ;seteo flag negativo
incl_pos:
	cp aux,aux3
	breq roll45	;si son iguales el angulo es 45
	brlo xmenorz
	mov aux2,aux	;si angulo>45
	mov aux,aux3	;swapeo reg (ver prop. tan)
	mov aux3,aux2
	ori aux4,2	;seteo flag angulo>45
xmenorz:
	ldi aux2,64
	mul aux,aux2
	mov aux,r0
	mov aux2,r1
	rcall div_unsigned16; res: r1:r0 (solo me importa parte baja)
	ldi zl,low(tabla_atan<<1)
	ldi zh,high(tabla_atan<<1)
	add zl,r0
	clr r0
	adc zh,r0
	lpm aux,z ;extraigo atan de la tabla
	rjmp fin_tan
roll45:
	ldi aux,45
fin_tan:
	sbrs aux4,1
	rjmp no_swap
	ldi aux2,90	;si hubo swap, hago 90-angulo
	sub aux2,aux
	mov aux,aux2
no_swap:
	sbrc aux4,0
	neg aux	;niego aux si el angulo es negativo
	pop aux4
	ret
;;;;;;;;;;;;Escalar angulo en unidades del gyro a grados;;;;;;;;;;;;;;;;;
escalo_pr:
;t_muestreo=8ms
;Escalo pitch(°)=pitch*t_muestreo*(250/128)=pitch*(4/256)
;multiplico por 4 y para dividir por 256, simplemente
;utilizo solo los 8bit mas significativos
;Nota: esto es mas rapido que dividir por 64 desplazando
;Nota2: no hay problema de overflow al multiplicar, ya
;que el rango de valores del gyro es mucho menor que
;2^14
	push aux3
	push aux2
	push aux

	lds aux3,pitch_h
	lds aux2,pitch_l
	ldi aux,4
	rcall mul_signed16
	sts pitch,aux3

;Idem pitch, escalo roll
	lds aux3,roll_h
	lds aux2,roll_l
	ldi aux,4
	rcall mul_signed16
	sts roll,aux3
	pop aux
	pop aux2
	pop aux3
	ret

;;;;;;;;;;;;;;Div unsigned 16 / unsigned 8;;;;;;;;;;;;;;;;;
div_unsigned16:	;[r1,r0]<-[aux2,aux]/aux3
	push aux4
	clr aux4
	clr r1
	clr r0
	inc r0

div8a:
	clc
	rol aux
	rol aux2
	rol aux4
	brcs div8b
	cp aux4,aux3
	brcs div8c
div8b:
	sub aux4,aux3
	sec 
	rjmp div8d
div8c:
	clc
div8d:
	rol r0
	rol r1
	brcc div8a
	pop aux4
	ret
