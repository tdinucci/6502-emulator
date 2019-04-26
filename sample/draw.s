; simple program that paints cycling colours to the screen using the
; keyboard curor keys
;
; The emulator loads programs at 0x600 so make sure to assemble with text segment at this address.
; Compile with xa using command:
; xa draw.s -v -bt 1536

; draw position
ldx #$00
stx $00             ; draw position low
ldx #$e0
stx $01             ; draw position high

; buffer for last key pressed
key_addr = $f001

; address that holds the current colour to draw with
draw_colour_addr = $10

left_key_code = $50
right_key_code = $4f
up_key_code = $52
down_key_code = $51

; main program loop
loop
    jsr read_key

    ; if we didn't read a key loop back round
    cmp #$0
    beq loop

    cmp #left_key_code
    bne not_left
    jsr move_left
    jmp loop

    not_left
        cmp #right_key_code
        bne not_right
        jsr move_right
        jmp loop

        not_right
            cmp #up_key_code
            bne not_up
            jsr move_up
            jmp loop

            not_up
                cmp #down_key_code
                bne loop
                jsr move_down
                jmp loop

    jmp loop

read_key
    lda key_addr

    ; clear the key press buffer so we don't read same key press twice
    ldx #$0
    stx key_addr

    rts

move_right
    lda $00

    ; if we're at $ff then we need to increment the high byte before rendering
    cmp #$ff
    bne do_right_render

    ; if we're at $efff then we have to stop because we'd start writing outside of video memory
    lda $01
    cmp $ef
    bcs after_right_render

    ; increment high byte and reset the low one
    inc $01
    ldx #$00
    stx $00

    do_right_render
        inc $00
        jsr render_dot

        after_right_render
            rts

; comments for "move_right" also apply here but direction is obviously reversed
move_left
    lda $00

    cmp #$00
    bne do_left_render

    lda $01
    cmp #$e0
    beq after_left_render

    dec $01
    ldx #$00
    stx $00

    do_left_render
        dec $00
        jsr render_dot

        after_left_render
            rts

move_up
    ; don't want to risk moving into non graphics memory so perform boundary checks
    ldx $00

    ; each line contains $40 (64) pixels, if low byte is above this then we're safe to move
    cpx #$40
    bcs after_up_boundary_check

    ; couldn't tell if we're safe by looking at low byte, does the high byte allow move?
    ldx $01
    cpx #$e0
    beq after_up_render

    after_up_boundary_check
        lda $00
        sbc #$40
        sta $00
        ; if carry flag is set then we'll also have to decrement the high byte
        bcs after_up_subtract
        dec $01

        after_up_subtract
            jsr render_dot

            after_up_render
                rts

; comments for "move_up" also apply here but direction is obviously reversed
move_down
    ldx $00
    cpx #$9b
    bcc after_down_boundary_check
    ldx $01
    cpx #$ef
    beq after_down_render

    after_down_boundary_check
        lda $00
        adc #$40
        sta $00
        bcc after_down_add
        inc $01

        after_down_add
            jsr render_dot

            after_down_render
                rts

render_dot
    ; change the drawing colour (256 colours and we'll wrap around when $ff is hit)
    inc draw_colour_addr
    lda draw_colour_addr

    ; write the "draw colour" to address pointed to across ($01 $00) - little endian
    ldx #$00
    sta ($00, x)

    rts
