; FILE   : main.asm
; PROJECT: Dice Roller
; BRIEF  : Handles the main program loop
; AUTHOR : leifs
; TARGET : z80-ceres8-none, SjASMPlus

    ORG $0000

start       LD	    SP, $FFFF           ; Set stack to top of RAM
            CALL    memInit
            CALL    lcdInit

.loop       JP	    .loop



; FUNCTION: memInit
; BRIEF   : Initializes variables
; PARAMS  : None
; RETURN  : None
memInit     PUSH    BC

            LD      HL, diceState
            LD      B, 5
.clrdice    LDI     (HL), 0             ; Zero out dice state
            DJNZ    .clrdice

            LD      HL, buttonState
            LD      B, 3
.clrbutton  LDI     (HL), 0             ; Zero out button state
            DJNZ    .clrbutton

.initprgm   LD      HL, programState    ; Initialize program state
            LDI     (HL), 0

            LD      BC, mhSplash        ; Store menu handler address
            LD      (HL), BC

            POP     BC
            RET



    ; Includes put at the end b/c SjASM doesn't support linking
    INCLUDE "lcd.asm"
    INCLUDE "menu.asm"
    INCLUDE "consts.asm"
    INCLUDE "variables.asm"
