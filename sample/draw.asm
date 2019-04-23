    lda #$0

    loop
        sta $e000, x
        inx
        adc #$1
        cpx #$ff
        bne loop

