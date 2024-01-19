; FILE   : main.asm
; PROJECT: Dice Roller
; BRIEF  : Handles the main program loop
; AUTHOR : leifs
; TARGET : z80-ceres8-none, SjASMPlus

    ORG $0000

start       LD	    SP, $FFFF           ; Set stack to top of RAM
            CALL    memInit
            CALL    lcdInit

.loop
.fakecall   ; Fakes a function call by manually pushing an address before jump,
            ; Because there is no register-addressed CALL instruction.
            LD      BC, .afterfake
            PUSH    BC
            LD      HL, programState.MenuHandler
            JP      (HL)

.afterfake  JP	    .loop



; FUNCTION: memInit
; BRIEF   : Initializes variables
; PARAMS  : None
; RETURN  : None
memInit     PUSH    BC

            LD      HL, diceState       ; Zero out dice and button states
            LD      B, 8                ; 3 bytes in buttons, 5 in dice
.clrstates  LDI     (HL), 0
            DJNZ    .clrstates

.initprgm   LD      HL, programState    ; Initialize program state
            LDI     (HL), 0

            LD      BC, mhSplash        ; Initial menu handler
            LD      (HL), BC

            POP     BC
            RET



    ; Includes put at the end b/c SjASM doesn't support linking
    INCLUDE "lcd.asm"
    INCLUDE "menu.asm"
    INCLUDE "consts.asm"
    INCLUDE "variables.asm"
