; filter.S
;
; FIR filter
;
#define NUM_TAPS 27
#define NUM_SAMPS 125

    .extern printRegs
    .extern q15mpy
    .extern fir1
    .extern input
    .extern output
    .extern numTimes

    .global filter
filter:
    push r16    ;save registers so C doesn't get confused
    push r17	;use r17:r16 for math
    ;push r18
    ;push r19	;r19:r18 store last memory location of input array
    ;push r20	
    ;push r21	;r21:r20 used to store last memory location of fir1 array
    ;push r22
    ;push r23
    ;push r24
    ;push r25	;r25:r24, r23:r22 used for q15mpy()
    ;push r26
    ;push r27	;r27:r26 = input array counter
    ;push r28
    ;push r29	;Y - used to keep track of fir1 array
    push r30
    push r31

    ;insert your assembly language code below
    ;(you can invoke printRegs() with the asm instruction 'call printRegs')
    
    ;input, output, fir1 are arrays of 16-bit ints
    						
    ;X (r27r26 points to output)
	ldi r26,lo8(output)
	ldi r27,hi8(output)

	;Y (r29r28 points to fir1)
	ldi r28,lo8(fir1)
	ldi r29,hi8(fir1)

	;Z (r31r30 points to input)
	ldi r30,lo8(input)
	ldi r31,hi8(input)
	
	ldi r16,0
	ldi r17,0
	

loop:
	ld 	r22,Y+
	ld 	r23,Y+
	ld 	r24,Z+
	ld 	r25,Z+

	;call printRegs
	
	push r16
	push r17
	;push r18
	;push r19
	;push r20
	;push r21
	push r26
	push r27
	call q15mpy
	pop r27
	pop r26
	;pop r21
	;pop r20
	;pop r19
	;pop r18
	pop r17
	pop r16

	;r17r16 is used to store each output index before storing in memory
	add r16,r24
	adc r17,r25
	
	;setting r21r20 to (last index + 1) of fir1
	ldi r20,lo8(fir1)
	ldi r21,hi8(fir1)
	ldi r18,NUM_TAPS
	lsl r18
	add r20,r18
	adc r21,r1
	
	cp r29,r21
	brsh fir1End
	jmp loop
	
fir1End:
	cp	r28,r20
	brsh store
	jmp loop
	
store:
	st 	X+,r16
	st 	X+,r17
	
	;call printRegs
	
	;r19r18 stores memory address of input[last index + 1]
	ldi r18,lo8(input)
	ldi r19,hi8(input)
	ldi r16,NUM_SAMPS
	lsl r16
	add r18,r16
	adc r19,r1
	
	cp r31,r19
	brsh inputEnd

	;input has not reached its end - shift forward 2 memory addresses (1 index) and loop again
	ldi r28,lo8(fir1)
	ldi r29,hi8(fir1)
	ldi r30,lo8(input)
	ldi r31,hi8(input)
	lds r18,(numTimes)
	lds r19,(numTimes + 1)
	ldi r16,2
	add r18,r16
	adc r19,r1
	add r30,r18
	adc r31,r19
	sts (numTimes),r18
	sts (numTimes + 1),r19
	ldi r16,0
	ldi r17,0
	
	;call printRegs
	
	jmp loop
	
inputEnd:
	cp r30,r18
	brsh end
	
	ldi r28,lo8(fir1)
	ldi r29,hi8(fir1)
	ldi r30,lo8(input)
	ldi r31,hi8(input)
	lds r18,(numTimes)
	lds r19,(numTimes + 1)
	ldi r16,2
	add r18,r16
	adc r19,r1
	add r30,r18
	adc r31,r19
	sts (numTimes),r18
	sts (numTimes + 1),r19
	ldi r16,0
	ldi r17,0
	
	;call printRegs
	
	jmp loop
	
end:
	;call printRegs
	
	pop r30
	pop r31
    ;pop r29     			;restore registers saved earlier
    ;pop r28
    ;pop r27
    ;pop r26
    ;pop r25
    ;pop r24
    ;pop r23
    ;pop r22
    ;pop r21
    ;pop r20
    ;pop r19
    ;pop r18
    pop r17
    pop r16
    ret         ;return
