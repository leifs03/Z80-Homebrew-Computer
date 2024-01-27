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
            LD      BC, programState

            XOR     A                   ; Zero out program state

            LDI     (BC), A
            LDI     (BC), A
            LDI     (BC), A

            LDI     A, (HL)             ; Load func pointer from menu to state
            LDI     (BC), A
            LD      A, (HL)
            LD      (BC), A

            POP     BC
            RET



; FUNCTION: loadEntires
; BRIEF   : Prints the entries in a bottom menu, based on ProgramState
; PARAMS  : HL - Pointer to Menu object
; RETURN  : None
; CLOBBERS: A
loadEntries
; Register Usage:
; A - Size
; B - Iterator
; C - Index
; D - Character
; HL - Source String Pointer
; IX - Destination String Pointer

            PUSH    BC                  ; Be nice, don't clobber all registers
            PUSH    DE
            PUSH    HL
            PUSH    IX

            LD      IX, tempString      ; Actually use IX for once
            LDI     (IX+0), 16          ; Output is always 16 chars

            XOR     A                   ; Zero reference
            LDI     B, (HL)             ; Load string size

            CP      B                   ; If size == 0, stop.
            RET     Z

            LD      A, (programState.CursorPos) ; Load string index

            CP      B                   ; If index > size, stop.
            RET     NC

            LD      A, B                ; Load string size into A
            LD      C, A                ; Load string index into C
            SUB     C                   ; Get size - index for new bounds

            LD      B, 16
.loop       LDI     D, (HL)             ; Get char from source
            CP      C                   ; Check if iterator > bounds
            JR      C, .putchar
            LD      D, ' '              ; If so, only print spaces

.putchar    LDI     (IX+0), D           ; Put char into destination
            INC     C                   ; Increment index
            DJNZ    .loop

.printstr   LD      HL, tmpString
            CALL    printStr

            POP     IX
            POP     HL
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

.print      LD      (HL), 1             ; Set MenuState so print is not redone

            CALL lcdClear

            LD      HL, mSplash+2       ; First string is after handler ptr
            CALL    printStr

            LD      B, 0                ; Move cursor to second row
            LD      C, 1
            CALL    lcdMovcur

            CALL    printStr            ; HL left at start of string

.noprint    LD      A, (buttonState.ButtonSummary+3) ; Load right button state
            CP      %00000011           ; See if button has just been pressed
            RET     NZ,

.nextmenu   LD      HL, mDieSelect      ; Load next menu
            CALL    loadMenu

            RET



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
