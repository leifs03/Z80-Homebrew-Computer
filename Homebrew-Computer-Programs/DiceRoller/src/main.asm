; FILE   : main.asm
; PROJECT: Dice Roller
; BRIEF  : Handles the main program loop
; AUTHOR : leifs
; TARGET : z80-ceres8-none, SjASMPlus

    DEVICE NOSLOT64K
    ORG $0000

start       LD	    SP, $FFFF           ; Set stack to top of RAM
            CALL    memInit
            CALL    lcdInit

.loop
            CALL    readButtons

.fakecall   ; Fakes a function call by manually pushing an address before jump,
            ; Because there is no register-addressed CALL instruction.
            LD      BC, .afterfake
            PUSH    BC
            LD      HL, (programState.MenuHandler)
            JP      (HL)

.afterfake  JP	    .loop



; FUNCTION: memInit
; BRIEF   : Initializes variables
; PARAMS  : None
; RETURN  : None
memInit     PUSH    BC
            PUSH    HL

            LD      HL, diceState       ; Zero out dice state
            LD      B, 4
.clrdice    LDI     (HL), 0
            DJNZ    .clrdice

            LD      HL, buttonState
            LD      B, 6
.clrbtn     LDI     (HL), 0
            DJNZ    .clrbtn

.initprgm   LD      HL, programState    ; Initialize program state
            LDI     (HL), 0
            LDI     (HL), 0

            LD      BC, mhSplash        ; Initial menu handler
            LD      (HL), BC

            POP     HL
            POP     BC
            RET



    ; Includes put at the end b/c SjASM doesn't support linking
    INCLUDE "lcd.asm"
    INCLUDE "menu.asm"
    INCLUDE "consts.asm"
    INCLUDE "io.asm"
    INCLUDE "variables.asm"