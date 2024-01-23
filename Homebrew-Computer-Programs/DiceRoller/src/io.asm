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
; CLOBBERS: A, HL
readButtons ; Purpose: Read in button states, write to vars if each button
            ; has been pressed and if its state has changed since last poll.
            PUSH    BC
            LD      C, 0                ; Use C as 0 register

            LD      HL, buttonState
            LDI     A, (HL)             ; Load old CurrentState
            LDD     (HL), A             ; Store in LastState

            IN      A, (BUTTONS)
            LD      (HL), A             ; Store new CurrentState

            LD      HL, buttonState.ButtonSummary

            LD      B, 4
.pressloop  LD      (HL), C             ; Reset summary entry
            RRCA                        ; Check if button is pressed
            JR      C, .ploopchk        ; If not, move to next iteration
            INC     (HL)                ; Set Bit 0 (isPressed)

.ploopchk   INC     HL
            DJNZ    .pressloop

            LD      HL, buttonState.CurrentState
            LDI     A, (HL)             ; Load CurrentState
            XOR     (HL)                ; Load changes from LastState

            LD      B, 4
.changeloop RRCA                        ; Check if button has changed
            JR      NC, .cloopchk       ; If not, move to next iteration
            SET     1, (HL)             ; Set Bit 1 (hasChanged)

.cloopchk   INC     HL
            DJNZ    .changeloop

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
; RETURN  : HL - Pointer to 1 byte after string
; CLOBBERS: A
printStr    PUSH    BC

            XOR     A                   ; Clear A

            LDI     B, (HL)             ; Load size of string into B
            CP      B                   ; Check if 0
            JR      Z, .end             ; If size 0, skip to end

.loop       LD      C, 8                ; Wait for LCD
.busywait   DEC     C
            JR      NZ, .busywait

            LDI     A, (HL)             ; Load character
            OUT     (LCD_RAM), A        ; Print character

            DJNZ    .loop

.end        POP     BC
            RET



    INCLUDE "lcd.asm"
    INCLUDE "variables.asm"

    ENDIF
