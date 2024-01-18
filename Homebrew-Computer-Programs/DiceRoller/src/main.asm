; FILE   : main.asm
; PROJECT: Dice Roller
; BRIEF  : Handles the main program loop
; AUTHOR : leifs
; TARGET : z80-ceres8-none, SjASMPlus

    ORG $0000

start       LD	    SP, $FFFF           ; Set stack to top of RAM
            CALL    lcdInit

.loop       JP	    .loop


    ; Includes put at the end b/c SjASM doesn't support linking
    INCLUDE "lcd.asm"
    INCLUDE "consts.asm"
    INCLUDE "variables.asm"
