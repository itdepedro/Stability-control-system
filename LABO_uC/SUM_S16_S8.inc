;;;;;;;;;;;;;;;;;;;;;;Suma signed 16bit + signed8bit;;;;;;;;;;;
suma_s16s8: ; [aux3,aux2]<-[aux3,aux2]+aux
	sbrc aux,7 ;salteo si es positivo
	rjmp negativo
	add aux2,aux
	clr aux
	adc aux3,aux
	rjmp listosum
negativo:
	add aux2,aux
	ldi aux,0xff
	adc aux3,aux
listosum:
	ret

;;;;;;;;;;;;;;;;;;;;;;Mul signed 16bit x unsigned 8bit;;;;;;;;;;;
mul_signed16:
	mulsu aux3,aux
	mov aux3,r0 ;desprecio parte alta ya que nunca llega
	mul aux2,aux
	mov aux2,r0
	add aux3,r1
	ret
