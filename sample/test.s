; head position
ldx #$00
stx $00             ; head position low
ldx #$e0
stx $01             ; head position high

; colours
ldx #$f0
stx $04             ; paint colour
ldx #$00
stx $05             ; rubber colour

jsr one
jsr two
jsr three
jsr four

clv
bvc end

one
    lda #$50
    ldx #$00
    sta ($00, x)
    inc $00
    rts

two
    lda #$F0
    ldx #$00
    sta ($00, x)
    inc $00
    rts

three
    lda #$FF
    ldx #$00
    sta ($00, x)
    inc $00
    rts

four
    lda #$af
    ldx #$00
    sta ($00, x)
    inc $00
    rts

end
