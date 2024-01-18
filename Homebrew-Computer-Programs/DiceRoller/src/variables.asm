; FILE   : variables.asm
; PROJECT: Dice Roller
; BRIEF  : Reserves space for RAM variables
; AUTHOR : leifs
; TARGET : z80-ceres8-none, SjASMPlus

    IFNDEF VARIABLES_ASM_
    DEFINE VARIABLES_ASM_

    ORG $4000

    STRUCT ButtonState
LastState           BYTE                ; The previous button state
CurrentState        BYTE                ; The current button state
ButtonSummary       BYTE                ; Bit 0, isPressed, Bit 1, hasChanged
    ENDS

    STRUCT DiceState
DieSides            BYTE                ; Highest number a die can roll
NumDice             BYTE                ; The number of dice to roll
Modifier            BYTE                ; Roll at advantage/disadvantage
Total               WORD                ; Final dice roll
    ENDS

    STRUCT ProgramState
CursorPos   BYTE
Menu        WORD
    ENDS

diceState DiceState

buttonState ButtonState

programState ProgramState

    ENDIF