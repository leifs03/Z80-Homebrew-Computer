; File   : PrintMem.z80.asm
; Project: Print Memory
; Brief  : Prints the contents of memory to the LCD
; Author : leifs
; Date   : 2024-01-02
; Target : z80-ceres8-none, RetroAssembler

LCD_REG: .equ $00
LCD_RAM: .equ $01

CHAR_JMP: .equ 7

.org $0000

_start:
    ld sp, $FFFF            ; Set stack to top of RAM
    ld hl, $8000            ; Set HL to bottom of RAM

    call lcdinit


@printaddr:                 ; Prints out HL in the format "$HHLL: "
    ld a, '$'
    call printchar

    ld a, h
    call byte2hex
    call printchar          ; Upper nibble already in A
    ld a, b
    call printchar          ; Lower nibble in B

    ld a, l
    call byte2hex
    call printchar
    ld a, b
    call printchar

    ld a, ':'               ; Could have a printstr routine, but this works.
    call printchar
    ld a, ' '
    call printchar

@printbyte:
    ld a, (hl)              ; Load byte HL points to
    call byte2hex
    call printchar          ; Print value
    ld a, b
    call printchar

    inc hl                  ; Increment pointer

    ld de, 1024
@longwait
    ld b, 255
    djnz *
    dec e
    jr nz, @longwait
    dec d
    jr nz, @longwait

@resetcursor
    call rethome            ; Reset cursor

    jp @printaddr



; Routine : lcdinit
; Brief   : Initializes and clears the LCD
; Params  : None
; Return  : None
lcdinit:
    push bc
    ld c, 20

@initloop:
    ld b, 255               ; Wait for >15ms to wait for LCD reset routine
    djnz *
    dec c
    jr nz, @initloop

    ld a, %00111000         ; Function Set: 8-bit, 16x2 chars, 5x8 font
    out (LCD_REG), a
    ld b, 255               ; Wait >37us before calling again
    djnz *                  ; Cannot check busy flag before initialization

    ld a, %00111000         ; Function Set: Datasheet says to do it again
    out (LCD_REG), a
    ld b, 255               ; Wait >37us before calling again
    djnz *                  ; Cannot check busy flag before initialization

    ld a, %00001111         ; Display On: Cursor On + Blinking
    out (LCD_REG), a
    call lcdwait

    ld a, %00000001         ; Clear Display
    out (LCD_REG), a
    call lcdwait

    ld a, %00000110         ; Entry Mode: Increment, no shift
    out (LCD_REG), a
    call lcdwait

    pop bc
    ret



; Routine : lcdwait
; Brief   : Waits to return until the LCD is ready for a command
; Params  : None
; Return  : 0 in A
lcdwait:
    push bc

    ld b, 255               ; 25 * 13 cycles per loop = 81.25us at 4Mhz
    djnz *                  ; Wait >80us before polling after a command

    in a, (LCD_REG)         ; Read LCD Status
    rlca                    ; Busy flag is in bit 7
    jr c, lcdwait           ; Flag is 0 when LCD is ready

    pop bc
    ret



; Routine : byte2hex
; Brief   : Converts a byte into two hexadecimal chars
; Params  : A - Number to convert
; Return  : A - Upper Char, B - Lower Char
; Clobbers: C
byte2hex:
@lnibble
    ld c, a                 ; Store number for upper nibble
    and $0F                 ; Isolate lower nibble

    add a, '0'              ; Convert to ASCII number
    cp a, ':'               ; Check if digit is 'A' through 'F'
    jr c, @unibble          ; If not, skip to upper nibble calculation

    add a, CHAR_JMP         ; Add difference between chars '9' and 'A'

@unibble
    ld b, a                 ; Store finished lower nibble
    ld a, c                 ; Restore full value

    rra                     ; Push upper nibble down
    rra                     ; This is cheaper than a loop
    rra
    rra
    and $0F                 ; Isolate upper nibble

    add a, '0'              ; Convert to ASCII number
    cp a, ':'               ; Check if digit is 'A' through 'F'
    jr c, @end              ; If not, skip to end

    add a, CHAR_JMP         ; Add difference between chars '9' and 'A'

@end
    ret



; Routine : printchar
; Brief   : Prints a character to the LCD
; Params  : A - Character to print
; Return  : None
printchar:
    push bc

    ld b, 255               ; Wait for >37us to wait for LCD delay
    djnz *

    out (LCD_RAM), a        ; Send character to LCD

    pop bc
    ret



; Routine : rethome
; Brief   : Returns the LCD cursor to 0, 0
; Params  : None
; Return  : None
rethome:
    push bc

    ld b, 255               ; Wait for >37us to wait for LCD delay
    djnz *

    ld a, %00000010
    out (LCD_REG), a

    ld b, 255               ; Wait for >1.52ms to wait for LCD processing
    djnz *
    ld b, 255
    djnz *

    pop bc
    ret
