
;;;;;;;;;;;;;;;;;;;;;;;;CONFIG I2C;;;;;;;;;;;;;;;;;;;;;;;;;;
configure_I2C:
	push aux
	ldi aux,0
	sts TWSR, aux
	ldi aux,15 ;bitrate 400KHz
	sts TWBR, aux
	ldi aux, (1<<TWEN)
	sts TWCR, aux
	pop aux
	ret
start_i2c:
	push aux
	ldi aux,(1<<TWINT)|(1<<TWSTA)|(1<<TWEN)
	sts TWCR, aux
	waitstart:
	lds aux,TWCR
	sbrs aux,TWINT
	rjmp waitstart
	pop aux
	ret
stop_i2c:
	push aux
	ldi aux,(1<<TWINT)|(1<<TWEN)|(1<<TWSTO)
	sts TWCR, aux
	pop aux
	ret

;;;;;;;;;;;;;;;;;;;;;;;;R/W I2C;;;;;;;;;;;;;;;;;;;;;;;;;;
write_i2c:
	push aux
	sts  TWDR,com_reg
	ldi aux,(1<<TWINT)|(1<<TWEN)
	sts TWCR,aux
	waitwi2c:
	lds aux,TWCR
	sbrs aux,TWINT
	rjmp waitwi2c
	pop aux
	ret
read_i2c:
	push aux
	ldi aux,(1<<TWINT)|(1<<TWEN)
	sts TWCR,aux
	waitri2c:
	lds aux,TWCR
	sbrs aux,TWINT
	rjmp waitri2c
	lds com_reg,TWDR
	pop aux
	ret

