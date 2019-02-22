;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;DELAYS;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
delay_1s:
	push aux
    eor     aux, aux   
loop_retardo_1s:
    rcall   delay_100ms   
    inc     aux       
    cpi     aux,10    
    brne    loop_retardo_1s 
	pop aux  
    ret   
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
delay_100ms:
	push aux
    eor     aux, aux    
loop_retardo_100ms:
    rcall   delay_1ms   
    inc     aux        
    cpi     aux,100  
    brne    loop_retardo_100ms  
	pop aux
    ret      
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
delay_10ms:
	push aux
    eor     aux, aux 
loop_retardo_10ms:
    rcall   delay_1ms   
    inc     aux      
    cpi     aux,10     
    brne    loop_retardo_10ms 
	pop aux
    ret   
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
delay_1ms:
	push aux
    eor     aux, aux  
loop_retardo_1ms:
    rcall   delay_10us        
    inc     aux                
    cpi     aux,100           
    brne    loop_retardo_1ms 
	pop aux   
    ret         
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
delay_10us:
	push aux
    eor     aux, aux 
loop_retardo_10us:
    inc     aux    
    cpi     aux,180  
    brne    loop_retardo_10us  
	pop aux
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
delay_50000:
	push 	r18
	push 	r19
	
    ldi  	r18, 65
    ldi  	r19, 239
L1: dec  	r19
    brne 	L1
    dec 	 r18
    brne 	L1

	pop 	r19
	pop		r18
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
delay_50:
	
	push	aux

	ldi  	aux, 50
L2: dec  	aux
    brne 	L2

	pop		aux
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
