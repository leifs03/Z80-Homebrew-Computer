; File   : LCDLib.z80.inc
; Project: LCD Library
; Brief  : Provides a standard set of
;          functions for the LCD
; Author : leifs
; Date   : 2024-01-09
; Target : z80-ceres8-none, RetroAssembler

LCD_REG: .equ $00
LCD_RAM: .equ $01



; FUNCTION: lcd_init
; BRIEF   : Initializes the LCD
; PARAMS  : C - Cursor Off/On (0/1)
; RETURN  : None
; CLOBBERS: A
lcd_init:
.region
    
    push bc
  
    ld c, 8                             ; Wait >15ms for LCD reset sequence
@waitloop:
    djnz *
    dec c
    jr nz, @waitloop
    
    ld a, %00111000                     ; Set: 8-bit, 16x2 chars, 5x8 font
    out (LCD_REG), a

    ld b, 12                            ; Wait >37us before next command
    djnz *

    out (LCD_REG), a                    ; Repeat to comply with datasheet
    ld b, 12
    djnz *

    ld a, %00001100                     ; Display on, cursor off
    rrc c                               ; If C = 1, turn cursor on
    jr nc, @nocursor
    add a, %00000011
  
@nocursor:
    out (LCD_REG), a
    call lcd_wait
  
    ; Clear Display
    ld a, %00000001
    out (LCD_REG), a
    call lcd_wait
  
    ; Entry Mode: Increment, no shift
    ld a, %00000110
    out (LCD_REG), a
    call lcd_wait
  
    pop bc
    ret
.endregion



; FUNCTION: lcd_clear
; BRIEF   : Clears the LCD
; PARAMS  : None
; RETURN  : None
; CLOBBERS: A
lcd_clear:
.region
    ld a, %00000001
    out (LCD_REG), a
    call lcd_wait
    ret
.endregion



; FUNCTION: lcd_rethome
; BRIEF   : Returns the cursor to 0,0
; PARAMS  : None
; RETURN  : None
; CLOBBERS: A
lcd_rethome:
.region
    ld a, %00000010
    out (LCD_REG), a
    call lcd_wait
    ret
.endregion



; FUNCTION: lcd_movecursor
; BRIEF   : Moves the cursor to a new
; position
; PARAMS  : B - Column: 0-15, C - Row 0-1
; RETURN  : None
; CLOBBERS: A, B, C
lcd_movecursor:
.region
    ld b, a                             ; Load column
    and $0F                             ; Make sure it is within bounds
    
    rrc c                               ; Check if on second row
    jr nc, @firstrow
    add a, $40                          ; Second row starts at $40
    
@firstrow
    or a, %10000000                     ; Set bit 7 for LCD Function call
    out (LCD_REG), a
    
    ld b, 12                            ; Polling LCD resets cursor pos
    djnz *
    
    ret
.endregion



; FUNCTION: lcd_wait
; BRIEF   : Waits until LCD is not busy
; PARAMS  : None
; RETURN  : None
; CLOBBERS: A
lcd_wait:
.region
    push bc
  
    ld b, 12                            ; Wait >80us before polling again           
    djnz *

    in a, (LCD_REG)                     ; Read LCD Status, busy flag is bit 7
    rlca
    jr c, lcd_wait

    pop bc
    ret
.endregion
