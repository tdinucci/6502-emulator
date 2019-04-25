draw_addr = $e000
key_addr = $f001
draw_colour_addr = $10

loop
    lda #$0
    jsr read_key
    cmp #$0
    beq loop

    cmp #$50
    bne not_left
    jsr move_left
    clv
    bvc loop

    not_left
        cmp #$4f
        bne not_right
        jsr move_right
        clv
        bvc loop

        not_right
            cmp #$52
            bne not_up
            jsr move_up
            clv
            bvc loop

            not_up
                cmp #$51
                bne loop
                jsr move_down
                clv
                bvc loop

    clv
    bvc loop

read_key
    lda key_addr
    ldx #$0
    stx key_addr
    rts

move_right
    inc $00
    jsr render_dot
    rts

move_left
    dec $00
    jsr render_dot
    rts

move_up
    lda $00
    sbc #$40
    sta $0
    jsr render_dot
    rts

move_down
    lda $00
    adc #$3f
    sta $0
    jsr render_dot
    rts

render_dot
    inc draw_colour_addr
    lda draw_colour_addr
    ldx $00
    sta draw_addr, x
    rts
