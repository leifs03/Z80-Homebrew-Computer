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
loadMenu    RET



; FUNCTION: mhSplash
; BRIEF   : Menu handler for the Splash menu
; PARAMS  : None
; RETURN  : None
mhSplash    RET



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

    ENDIF
