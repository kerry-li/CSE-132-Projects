; dm.S
;
; data manipulation
;
    .extern printRegs
    .extern m
    .extern n
    .extern p

    .global dm
dm:
    push r16    ;save registers so C doesn't get confused
    push r17
    push r28
    push r29

    ;insert your assembly language code below
    ;(you can invoke printRegs() with the asm instruction 'call printRegs')
	;m, n, and p are 16-bit (int)
	;registers are only 1 byte (8-bit)
	
	ldi r16, 100	;loads immediate value 100 into register 16
	ldi r17, 0		;loads leading 0's into 17 -- r17:r16 now stores 100
	sts (m), r16	;stores register 16 in memory location m
	sts (m+1), r17	;stores high byte into memory location m+1
	
	lds r28, (m)
	lds r29, (m+1)	;r29:r28 = m = 100
	add r16, r28	
	adc r17, r29	;r17:r16 + r29:r28 --> r17:r16 = 100
	add r16, r28	
	adc r17, r29
	sts (n), r16
	sts (n+1), r17
	
	lds r16, (m)
	lds r17, (m+1)	;r17:r16 = m = 100
	ldi r28, 50		
	ldi	r29, 0		;r29:r28 = 50
	sub	r16, r28
	sbc r17, r29	;r17:r16 - r29:r28
	sts (p), r16
	sts (p+1), r17	;p = r17:r16

    pop r29     ;restore registers saved earlier
    pop r28
    pop r17
    pop r16
    ret         ;return
