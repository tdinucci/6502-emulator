; head position
ldx #$00
stx $00             ; head position low
ldx #$e0
stx $01             ; head position high

; old head position
ldx #$ff            ; start one behind head
stx $02             ; old head position low
ldx #$e0
stx $03             ; old head position high

; colours
ldx #$f0
stx $04             ; paint colour
ldx #$00
stx $05             ; rubber colour

move_head_right
    inc $00

    lda $04
    ldx #$00
    sta ($00, x)

    clv
    bvc move_rubber_right

after_rubbed
    ldx $00
    cpx #$ff
    beq move_head_down
    bne move_head_right

move_rubber_right
    inc $02

    lda $05
    ldx #$02
    sta ($00, x)

;    ldx $02
;    cpx #$40
;    bne continue_rubbing
;    dec $02
    clv
;    bvc continue_rubbing

;continue_rubbing
    ldx $02
    cpx #$ff
    beq move_rubber_down
    clv
    bvc after_rubbed

move_head_down
    inc $01

    ldx $00
    stx $00

    clv
    bvc move_head_right

move_rubber_down
    inc $03
    ldx $00
    stx $02
    bvc after_rubbed



