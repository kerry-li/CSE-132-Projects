; array.S
;
; arrays and indexing
;
    .extern printRegs
    .extern sum
    .extern val

    .global array
array:
    push r16    ;save registers so C doesn't get confused
    push r17
    push r28
    push r29

    ;insert your assembly language code below
    ;(you can invoke printRegs() with the asm instruction 'call printRegs')
    
	;val is an array of bytes - no need to do 16-bit addition
	
	ldi r30,lo8(val)	;Z now points to val[0]
	ldi r31,hi8(val)
	
	ldi r28,lo8(val)	;Y points to val[0]
	ldi r29,hi8(val)
	ldi r16,8			;using r17:r16 to store the length of val (8)
	ldi r17,0
	add r28,r16			;memory addresses for an array are adjacent to one-another
	adc r29,r17			;r29:r28 now points to val[length = 8] after adding r17:r16 (8)
	
	lds r16,(sum)
loop:
    ld r17, Z+
	add r16,r17
	cp r30,r28			;compares lsb of Z to r29:r28 - if they are equal, compares high byte
	breq lsb
	jmp loop
lsb:
    cp r31, r29			;compares high byte - to get here, low byte must have been equal
	breq escape			;guarantees that Z has reached the end of val
	jmp loop
escape:
	sts (sum),r16


    pop r29     ;restore registers saved earlier
    pop r28
    pop r17
    pop r16
    ret         ;return
