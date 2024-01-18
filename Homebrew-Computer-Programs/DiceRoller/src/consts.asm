; FILE   : consts.asm
; PROJECT: Dice Roller
; BRIEF  : Defines several data constants
; AUTHOR : leifs
; TARGET : z80-ceres8-none, SjASMPlus

; *** CHARS ***
U_ARROW     EQU     $5C
D_ARROW     EQU     $6C
L_ARROW     EQU     $7C
R_ARROW     EQU     $8C

; *** STRUCTS ***

    ; MACRO: Menu
    ; BRIEF: Data structure for a Menu object
    ; PARAM: Handler, Address to menu handler function
    ; PARAM: TopStr, Pascal-style string to display on first row
    ; PARAM: BotStr, Pascal-style string of entries to display on second row.
    ; PARAM: EntryCount, Number of entries in menu. Can be 0.
    ; PARAM: EntryPos, Array of positions of each entry in the menu.
    MACRO Menu Handler, TopStr, BotStr, EntryCount, EntryPos
        WORD Handler
        BYTE TopStr
        BYTE BotStr
        BYTE EntryCount
        BYTE EntryPos
    ENDM

; *** MENUS ***

; Splash screen at system startup
mSplash:    Menu    $0000,\
                    <15,"DnD Dice Roller">,\
                    <16,"By Leif :)     ",D_ARROW>,\
                    0,\
                    0

; Select die to roll
mDieSelect: Menu    $0000,\
                    <16,"Die Select:    ",D_ARROW>,\
                    <31,"D4 D6 D8 D10 D12 D20 D100 Custom">,\
                    8,\
                    <0,3,6,9,13,17,21,26>

; Select number of dice to roll
mDieCount:  Menu    $0000,\
                    <16,"Num. Dice:   ",L_ARROW,' ',R_ARROW>,\
                    "\0",\
                    1,\
                    0

; Die modifier, only displayed when rolling one die
mDieMod:    Menu    $0000,\
                    <16,"Roll As:       ",D_ARROW>,\
                    <11,"Reg Adv Dis">,\
                    3,\
                    <0,4,8>

; Display total rolled
mTotal:     Menu    $0000,\
                    <13,"You Rolled...">,\
                    "\0",\
                    0,\
                    0

; Rolling animation. May be used if I feel like it.
mAnim:      Menu    $0000,\
                    "\0",\
                    "\0",\
                    0,\
                    0
