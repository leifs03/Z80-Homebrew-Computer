; File   : HelloWorld.z80.asm
; Project: Hello World
; Brief  : Prints a message to the LCD
; Author : leifs
; Date   : 2023-12-26
; Target : z80-ceres8-none, RetroAssembler

.org $0000

_start:
    ld sp, $FFFF                ; Initialize SP to top of RAM

    call lcdinit

    ld hl, message
    call printstr

    halt
    jr *-1



; Function: lcdinit
; Brief   : Initializes and clears the LCD
; Params  : None
; Return  : None
lcdinit:
    ld a, %00111000             ; Function Set: 8-bit, 16x2 chars, 5x8 font
    out ($00), a
    ld b, 12                    ; Wait >37us before calling again
    djnz *                      ; Cannot check busy flag before initialization

    ld a, %00111000             ; Function Set: Datasheet says to do it again
    out ($00), a
    ld b, 12                    ; Wait >37us before calling again
    djnz *                      ; Cannot check busy flag before initialization

    ld a, %00001111             ; Display On: Cursor On + Blinking
    out ($00), a
    call lcdwait

    ld a, %00000001             ; Clear Display
    out ($00), a
    call lcdwait

    ld a, %00000110             ; Entry Mode: Increment, no shift
    out ($00), a
    call lcdwait

    ret



; Function: lcdwait
; Brief   : Waits to return until the LCD is ready for a command
; Params  : None
; Return  : 0 in A
lcdwait:
    push bc

    ld b, 25                    ; 25 * 13 cycles per loop = 81.25us at 4Mhz
    djnz *                      ; Wait >80us before polling after a command

    in a, ($00)                 ; Read LCD Status
    rlca                        ; Busy flag is in bit 7
    jr c, lcdwait               ; Flag is 0 when LCD is ready

    pop bc
    ret



; Function: printstr
; Brief   : Prints a Pascal-style string to the LCD
;           Note: This does not work with 0-length strings.
; Params  : HL - Pointer to string
; Return  : None
printstr:
    push bc
    ld b, (hl)                  ; Load size of string from pointer into B

@loop
    ld c, 9                     ; Short busy loop to wait for LCD refresh.
@delay                          ; (9 * (4 + 12)) + 7 cycles = 37.75us @ 4Mhz
    dec c                       ; My LCD seems to reset the cursor when polling
    jr nz, @delay               ; state. It shouldn't, but here I am.

    inc hl                      ; Update pointer
    ld a, (hl)                  ; Load char into A
    out ($01), a                ; Write to LCD RAM

    djnz @loop
    
    pop bc
    ret


message:
    .byte 13,"Hello, World!"
