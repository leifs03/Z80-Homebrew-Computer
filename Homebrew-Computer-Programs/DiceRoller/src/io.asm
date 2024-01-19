; FILE   : io.asm
; PROJECT: Dice Roller
; BRIEF  : Provides input/output functions
; AUTHOR : leifs
; TARGET : z80-ceres8-none, SjASMPlus

    IFNDEF IO_ASM_
    DEFINE IO_ASM_

BUTTONS     EQU     $02

; FUNCTION: readButtons
; BRIEF   : Updates the program's button state
; PARAMS  : None
; RETURN  : None
; CLOBBERS: A
readButtons PUSH    BC
            PUSH    DE
            PUSH    HL

            LD      HL, buttonState

            LDI     A, (HL)             ; Load old CurrentState
            LDD     (HL), A             ; Store in LastState

.readin     IN      A, (BUTTONS)
            CPL                         ; Buttons inverted (pulled high)
            AND     A, $0F              ; Only lower 4 bits are mapped

            LD      (HL), A             ; Store new CurrentState

.updatesumm LD      HL, buttonState.ButtonSummary
            LD      C, 0

.pressloop  LDI     (HL), C             ; Reset summary entry
            RRCA                        ; Check if button is pressed
            JR      NC, .ploopchk       ; If not, move to next iteration

            INC     (HL)                ; Set Bit 0 (isPressed)
.ploopchk   DJNZ    .pressloop

            LD      HL, buttonState.CurrentState

.changes    LDI     A, (HL)             ; Load CurrentState
            LDI     B, (HL)             ; Load LastState
            XOR     A, B                ; Only set changed bits

            LD      B, 4
.changeloop RRCA                        ; Check if button has changed
            JR      NC, .cloopchk       ; If not, move to next iteration

            SET     1, (HL)             ; Set Bit 1 (hasChanged)
.cloopchk   DJNZ    .changeloop

            POP     HL
            POP     DE
            POP     BC
            RET



; FUNCTION: printChar
; BRIEF   : Prints a single character to the LCD
; PARAMS  : A - Character to print
; RETURN  : None
; CLOBBERS: None
printChar   PUSH    BC

            LD      B, 12               ; Busy wait to make sure LCD is ready
            DJNZ    $
            OUT     (LCD_RAM), A        ; Write character out

            POP     BC
            RET



; FUNCTION: printStr
; BRIEF   : Prints a pascal-style string to the LCD
; PARAMS  : HL - Pointer to string
; RETURN  : None
; CLOBBERS: A
printStr    PUSH    BC

            LDI     B, (HL)             ; Load size of string into B
            JR      Z, .end             ; If size 0, skip to end

.loop       LDI     A, (HL)             ; Load character
            OUT     (LCD_RAM), A        ; Print character

            LD      C, 8                ; Wait for LCD
.busywait   DEC     C
            JR      NZ, .busywait

            DJNZ    .loop

.end        POP     BC
            RET



    INCLUDE "lcd.asm"
    INCLUDE "variables.asm"

    ENDIF