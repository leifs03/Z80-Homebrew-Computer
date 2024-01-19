; FILE   : menu.asm
; PROJECT: Dice Roller
; BRIEF  : Provides menu functions and handlers
; AUTHOR : leifs
; TARGET : z80-ceres8-none, SjASMPlus

    IFNDEF MENU_ASM_
    DEFINE MENU_ASM_

; FUNCTION: loadMenu
; BRIEF   : Resets the program state and loads a new menu
; PARAMS  : HL - Pointer to Menu object
; RETURN  : None
; CLOBBERS: HL
loadMenu    PUSH    BC
            PUSH    DE

            LD      BC, programState

            XOR     A                   ; Zero out program state

            LDI     (BC), A
            LDI     (BC), A
            LDI     (BC), A

            LDI     A, (HL)             ; Load func pointer from menu to state
            LDI     (BC), A
            LD      A, (HL)
            LD      (BC), A

            POP     DE
            POP     BC
            RET



; FUNCTION: mhSplash
; BRIEF   : Menu handler for the Splash menu
; PARAMS  : None
; RETURN  : None
; CLOBBERS: A, BC, HL
mhSplash    LD      HL, programState.MenuState
            LD      A, (HL)             ; Check MenuState status
            AND     A                   ; If not set, print menu string
            JR      NZ, .noprint

.print      LD      (HL), 1             ; Set MenuState so string is not redone

            CALL lcdClear

            LD      HL, mSplash+2       ; Menu object begins with function ptr
            CALL    printStr

            LD      B, 0                ; Move cursor to second row
            LD      C, 1
            CALL    lcdMovcur

            CALL    printStr            ; HL left at start of string

.noprint    LD      A, (buttonState.ButtonSummary+3) ; Load right button state
            CP      %00000011           ; See if button has just been pressed
            JP      NZ, .end

.nextmenu   LD      HL, mDieSelect      ; Load next menu
            CALL    loadMenu

.end        RET



; FUNCTION: mhDieSelect
; BRIEF   : Menu handler for the Die Select menu
; PARAMS  : None
; RETURN  : None
mhDieSelect RET



; FUNCTION: mhDieCount
; BRIEF   : Menu handler for the Die Count menu
; PARAMS  : None
; RETURN  : None
mhDieCount  RET



; FUNCTION: mhDieMod
; BRIEF   : Menu handler for the Die Modifier menu
; PARAMS  : None
; RETURN  : None
mhDieMod    RET



; FUNCTION: mhTotal
; BRIEF   : Menu handler for the Total menu
; PARAMS  : None
; RETURN  : None
mhTotal     RET



; FUNCTION: mhAnim
; BRIEF   : Menu handler for the Animation menu
; PARAMS  : None
; RETURN  : None
mhAnim      RET

    INCLUDE "io.asm"
    INCLUDE "consts.asm"
    INCLUDE "variables.asm"

    ENDIF
