; File   : ButtonTest.z80.asm
; Project: Print Memory
; Brief  : Prints the state of buttons to the LCD
; Author : leifs
; Date   : 2024-01-05
; Target : z80-ceres8-none, RetroAssembler

LCD_REG: .equ $00
LCD_RAM: .equ $01
BUTTONS: .equ $02

.org $0000

_start:
    ld sp, $FFFF            ; Set stack to top of RAM
    call lcdinit

@loop:
	in a, (BUTTONS)         ; Read button state

@printleft:
	rrca                    ; Bit 0, Left Button
	jr c, @printdown        ; If not pressed, skip
	ld b, a                 ; Preserve A
	ld a, 'L'               ; Load and print 'L'
	call printchar
	ld a, b                 ; Restore A

@printdown:
    rrca                    ; Bit 1, Down Button
    jr c, @printup          ; If not pressed, skip
    ld b, a                 ; Preserve A
    ld a, 'D'               ; Load and print 'D'
    call printchar
    ld a, b                 ; Restore A

@printup:
    rrca                    ; Bit 2, Up Button
    jr c, @printright       ; If not pressed, skip
    ld b, a                 ; Preserve A
    ld a, 'U'               ; Load and print 'U'
    call printchar
    ld a, b                 ; Restore A

@printright:
    rrca                    ; Bit 3, Right Button
    jr c, @resetcursor      ; If not pressed, skip
    ld b, a                 ; Preserve A
    ld a, 'R'               ; Load and print 'R'
    call printchar
    ld a, b                 ; Restore A

    ld b, 4
@resetcursor
    ld a, ' '               ; Print ' ' to clear previous text
    call printchar
    djnz @resetcursor

    call rethome            ; Reset cursor

    jp @loop



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

    ld a, %00001100         ; Display On: Cursor Off
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
