; simple program that paints cycling colours to the screen using the keyboard curor keys and will max out your
; CPU in the process!
;
; Esc - ends the process
;
; Del - clears the screen - this is HORRIBLY SLOW!  There is no clock emulation and so it's not possible within
; assembly to slow things down, i.e. to prevent painting to screen at lightning speed, meaning you have no real control.
; In order approximate this a delay of 20ms has been put into the terminal between rendering each pixel change.  Since
; clearing the screen effectively redraws each pixel this means it takes around 64 * 64 * 20ms, so ~82 seconds!!
; While waiting for this process to complete the program won't respond to you pressing the Esc key.
;
; The emulator loads programs at 0x600 so make sure to assemble with text segment at this address.
;
; Compile with xa using command:
; xa draw.s -v -bt 1536

; buffer for last key pressed
key_addr = $f001

video_bottom_lb = $00
video_bottom_hb = $e0

video_top_lb = $00
video_top_hb = $f0

video_memory_ptr_lb = $00
video_memory_ptr_hb = $01

; address that holds the current colour to draw with
draw_colour_addr = $03
is_clearing_addr = $04

rubber_colour = $00

left_key_code = $50
right_key_code = $4f
up_key_code = $52
down_key_code = $51
esc_key_code = $29
del_key_code = $4c

; draw position
ldx #video_bottom_lb
stx video_memory_ptr_lb       ; starting draw position low
ldx #video_bottom_hb
stx video_memory_ptr_hb       ; starting draw position high

; main program loop
loop
    jsr read_key

    ; if we didn't read a key loop back round
    cmp #0
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
                bne not_down
                jsr move_down
                jmp loop

                not_down
                    cmp #del_key_code
                    bne not_del
                    jsr clear_screen
                    jmp loop

                    not_del
                        cmp #esc_key_code
                        bne loop
                        jmp exit

    jmp loop

read_key
    lda key_addr

    ; clear the key press buffer so we don't read same key press twice
    ldx #0
    stx key_addr

    rts

move_right
    lda video_memory_ptr_lb

    ; if we're at $ff then we need to increment the high byte before rendering
    cmp #$ff
    bne do_right_render

    ; if we're at $efff then we have to stop because we'd start writing outside of video memory
    lda video_memory_ptr_hb
    cmp #$ef
    bcs after_right_render

    ; increment high byte and reset the low one
    inc video_memory_ptr_hb
    ldx #0
    stx video_memory_ptr_lb

    do_right_render
        inc video_memory_ptr_lb
        jsr render_dot

        after_right_render
            rts

; comments for "move_right" also apply here but direction is obviously reversed
move_left
    lda video_memory_ptr_lb

    cmp #0
    bne do_left_render

    lda video_memory_ptr_hb
    cmp #video_bottom_hb
    beq after_left_render

    dec video_memory_ptr_hb
    ldx #0
    stx video_memory_ptr_lb

    do_left_render
        dec video_memory_ptr_lb
        jsr render_dot

        after_left_render
            rts

move_up
    ; don't want to risk moving into non graphics memory so perform boundary checks
    ldx video_memory_ptr_lb

    ; each line contains $40 (64) pixels, if low byte is above this then we're safe to move
    cpx #$40
    bcs after_up_boundary_check

    ; couldn't tell if we're safe by looking at low byte, does the high byte allow move?
    ldx video_memory_ptr_hb
    cpx #$e0
    beq after_up_render

    after_up_boundary_check
        lda video_memory_ptr_lb
        sbc #$40
        sta video_memory_ptr_lb
        ; if carry flag is set then we'll also have to decrement the high byte
        bcs after_up_subtract
        dec video_memory_ptr_hb

        after_up_subtract
            jsr render_dot

            after_up_render
                rts

; comments for "move_up" also apply here but direction is obviously reversed
move_down
    ldx video_memory_ptr_lb
    cpx #$9b
    bcc after_down_boundary_check
    ldx video_memory_ptr_hb
    cpx #$ef
    beq after_down_render

    after_down_boundary_check
        lda video_memory_ptr_lb
        adc #$40
        sta video_memory_ptr_lb
        bcc after_down_add
        inc video_memory_ptr_hb

        after_down_add
            jsr render_dot

            after_down_render
                rts

; renders a pixel on the screen
render_dot
    ; if we're clearing the screen then load the rubber colour...
    ldx is_clearing_addr
    cpx #0
    beq set_colour
    lda #rubber_colour
    jmp end_set_colour

    ; ... else cycle the drawing colour
    set_colour
        ; change the drawing colour (256 colours and we'll wrap around when $ff is hit)
        inc draw_colour_addr
        lda draw_colour_addr

    end_set_colour

    ; write the "draw colour" to address pointed to across (video_memory_ptr_hb video_memory_ptr_lb)
    ldx #video_memory_ptr_lb
    sta (video_memory_ptr_lb, x)

    rts

; clears the screen
clear_screen
    ; go into "clear screen" mode
    ldx #1
    stx is_clearing_addr

    ldx #video_bottom_lb
    stx video_memory_ptr_lb

    ldx #video_bottom_hb
    stx video_memory_ptr_hb

    clear_pixel
        ; use the existing move_right routine to clear the screen from left-to-right/top-to-bottom
        jsr move_right

        ; if we're not at the end of a block then just repeat
        lda video_memory_ptr_lb
        cmp #$ff
        bne clear_pixel

        ; we're at the of the block...
        lda video_memory_ptr_hb

        ; if we're at the end of the screen then break from loop
        cmp #video_top_hb
        beq end_clear_pixel

        ; otherwise move onto the next block
        inc video_memory_ptr_hb
        ldx #0
        stx video_memory_ptr_lb

        jmp clear_pixel

    end_clear_pixel

    ; come out of "clear screen" mode
    ldx #0
    stx is_clearing_addr

    ; move the draw position back to the top left of screen
    ldx #video_bottom_lb
    stx video_memory_ptr_lb

    ldx #video_bottom_hb
    stx video_memory_ptr_hb

    rts

; jump to here to end the process
exit