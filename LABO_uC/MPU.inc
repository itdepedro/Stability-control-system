;;;;;;;;;;;;INIT MPU;;;;;;;;;;;;;;;;;;;;;;;;
init_mpu:
	rcall start_i2c
	ldi com_reg,slv_w
	rcall write_i2c
	ldi com_reg,0x6b	;power magnament
	rcall write_i2c
	ldi com_reg,0b00000000
	rcall write_i2c
	rcall stop_i2c

	rcall start_i2c
	ldi com_reg,slv_w
	rcall write_i2c
	ldi com_reg,26	;configuro el pasa-bajo
	rcall write_i2c
	ldi com_reg,2
	rcall write_i2c
	rcall stop_i2c

	rcall start_i2c
	ldi com_reg,slv_w
	rcall write_i2c
	ldi com_reg,27	;configuro gyro
	rcall write_i2c
	ldi com_reg,0
	rcall write_i2c
	rcall stop_i2c

	rcall start_i2c
	ldi com_reg,slv_w
	rcall write_i2c
	ldi com_reg,28	;configuro acc
	rcall write_i2c
	ldi com_reg,0
	rcall write_i2c
	rcall stop_i2c
	
	cbi PORTC,3
	ldi com_reg,0x75
	rcall read_reg
	cpi com_reg,0x68
	brne no_com
	sbi PORTC,3	;led testigo comunicacion
	no_com:

	ret



;;;;;;;;;;;;;;;;;;;;READ MPU;;;;;;;;;;;;;;;;;;;;;;;;
read_reg:
	push com_reg
	rcall start_i2c
	ldi com_reg,slv_w
	rcall write_i2c
	pop com_reg
	rcall write_i2c
	rcall start_i2c
	ldi com_reg,slv_r
	rcall write_i2c
	rcall read_i2c
	rcall stop_i2c
	ret

