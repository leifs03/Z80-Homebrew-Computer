; FILE   : variables.asm
; PROJECT: Dice Roller
; BRIEF  : Reserves space for RAM variables
; AUTHOR : leifs
; TARGET : z80-ceres8-none, SjASMPlus

    IFNDEF VARIABLES_ASM_
    DEFINE VARIABLES_ASM_

    ORG $4000

    STRUCT ProgramState
EntrySel            BYTE                ; Menu entry selection
CursorPos           BYTE                ; Cursor position in string
MenuHandler         WORD                ; Pointer to current menu handler
    ENDS

    STRUCT ButtonState
CurrentState        BYTE                ; The current button state
LastState           BYTE                ; The previous button state
ButtonSummary       DWORD               ; Bit 0, isPressed, Bit 1, hasChanged
    ENDS

    STRUCT DiceState
DieSides            BYTE                ; Highest number a die can roll
NumDice             BYTE                ; The number of dice to roll
Modifier            BYTE                ; Roll at advantage/disadvantage
Total               WORD                ; Final dice roll
    ENDS

programState ProgramState

buttonState ButtonState

diceState DiceState

    ENDIF
