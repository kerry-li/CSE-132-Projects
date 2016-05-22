; cf.S
;
; control flow
;
    .extern printRegs
    .extern a
    .extern b
    .extern c
    .extern d

    .global cf
cf:
    push r16    ;save registers so C doesn't get confused
    push r17
    push r28
    push r29

    ;insert your assembly language code below
    ;(you can invoke printRegs() with the asm instruction 'call printRegs')
    
    




    pop r29     ;restore registers saved earlier
    pop r28
    pop r17
    pop r16
    ret         ;return
