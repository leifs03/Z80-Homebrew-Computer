; FILE   : lcd.asm
; PROJECT: Dice Roller
; BRIEF  : Implements functions to control the LCD
; AUTHOR : leifs
; TARGET : z80-ceres8-none, SjASMPlus

    IFNDEF LCD_ASM_
    DEFINE LCD_ASM_

LCD_REG     EQU     $00
LCD_RAM     EQU     $01

; FUNCTION: lcdInit
; BRIEF   : Initializes the LCD
; PARAMS  : C - Cursor Off/On (0/1)
; RETURN  : None
; CLOBBERS: A
lcdInit     PUSH    BC                  ; Store C parameter for later

            LD      C, $08              ; Wait >15ms for LCD reset sequence
.waitloop   LD      B, $0C
            DJNZ    $
            DEC     C
            JR      NZ, .waitloop

            LD      A, %00111000        ; Set: 8-bit, 16x2 chars, 5x8 font
            OUT     (LCD_REG), A

            LD      B, 12               ; Wait >37us before next command
            DJNZ    $

            OUT     (LCD_REG), A        ; Repeat to comply with datasheet
            LD      B, 12
            DJNZ    $

            LD      A, %00001100        ; Display on, cursor off

            POP     BC                  ; Restore C for parameter
            RRC     C                   ; Check bit 0 instead of comparing to 1
            JR      NC, .nocursor       ; If C = 1, turn cursor on
            ADD     A, %00000011

.nocursor   OUT     (LCD_REG), A
            CALL    lcdWait

            LD      A, %00000001        ; Clear Display
            OUT     (LCD_REG), A
            CALL    lcdWait

            LD      A, %00000110        ; Entry Mode: Increment, no shift
            OUT     (LCD_REG), A
            CALL    lcdWait

            RET



; FUNCTION: lcdClear
; BRIEF   : Clears the LCD
; PARAMS  : None
; RETURN  : None
; CLOBBERS: A
lcdClear    LD      A, %00000001
            OUT     (LCD_REG), A
            CALL    lcdWait
            RET



; FUNCTION: lcdRethome
; BRIEF   : Returns the cursor to 0,0
; PARAMS  : None
; RETURN  : None
; CLOBBERS: A
lcdRethome  LD      A, %00000010
            OUT     (LCD_REG), A
            CALL    lcdWait
            RET



; FUNCTION: lcdMovcur
; BRIEF   : Moves the cursor to a new position
; PARAMS  : B - Column: 0-15, C - Row 0-1
; RETURN  : None
; CLOBBERS: A, B, C
lcdMovcur   LD      B, A                ; Load column
            AND     $0F                 ; Keep within screen bounds

            RRC     C                   ; Check if on second row
            JR      NC, .firstrow
            ADD     A, $40              ; Second row starts at $40

.firstrow   OR      A, %10000000        ; Set bit 7 to format as LCD instruction
            OUT     (LCD_REG), A

            LD      B, 12               ; Busy wait, since polling resets cursor
            DJNZ    $

            RET



; FUNCTION: lcdWait
; BRIEF   : Waits until LCD is not busy
; PARAMS  : None
; RETURN  : None
; CLOBBERS: A
lcdWait     PUSH    BC

            LD      B, 12               ; Wait >80us before polling again
            DJNZ    $

            IN      A, (LCD_REG)        ; Read LCD Status, busy flag is bit 7
            RLCA
            JR      C, lcdWait

            POP     BC
            RET

    ENDIF
