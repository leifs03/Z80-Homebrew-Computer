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
.fakecall   ; Fakes a function call by manually pushing an address, and then
            ; doing nested indirection to jump to the menu's function pointer.
            ; Note: I hate this.
            LD      BC, .afterfake
            PUSH    BC
            LD      HL, (programState.Menu)
            ; HL has a pointer to a Menu Object
            ; At (HL), there is a function pointer
            LD      DE, (HL)            ; DE indirectly loads the function ptr
            EX      DE, HL              ; HL has the function ptr
            JP      (HL)                ; Jump to the loaded function ptr

.afterfake  JP	    .loop



; FUNCTION: memInit
; BRIEF   : Initializes variables
; PARAMS  : None
; RETURN  : None
memInit     PUSH    BC

            LD      HL, diceState       ; Zero out dice and button states
            LD      B, 8                ; 3 bytes in buttons, 5 in dice
.clrbtndice LDI     (HL), 0
            DJNZ    .clrbtndice

.initprgm   LD      HL, programState    ; Initialize program state
            LDI     (HL), 0

            LD      BC, mSplash         ; Initial menu
            LD      (HL), BC

            POP     BC
            RET



    ; Includes put at the end b/c SjASM doesn't support linking
    INCLUDE "lcd.asm"
    INCLUDE "menu.asm"
    INCLUDE "consts.asm"
    INCLUDE "variables.asm"
