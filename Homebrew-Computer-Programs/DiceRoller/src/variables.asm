; FILE   : variables.asm
; PROJECT: Dice Roller
; BRIEF  : Reserves space for RAM variables
; AUTHOR : leifs
; TARGET : z80-ceres8-none, SjASMPlus

    ORG $4000

    STRUCT ButtonState
        BYTE LastState                  ; The previous button state
        BYTE CurrentState               ; The current button state
        BYTE ButtonSummary              ; Bit 0, isPressed, Bit 1, hasChanged
    ENDS

    STRUCT DiceState
        BYTE DieSides                   ; Highest number a die can roll
        BYTE NumDice                    ; The number of dice to roll
        BYTE Modifier                   ; Roll at advantage/disadvantage
        WORD Total                      ; Final dice roll
    ENDS

    STRUCT ProgramState
        BYTE CurrentMenu
        WORD MenuHandler
    ENDS

diceState DiceState

buttonState ButtonState
