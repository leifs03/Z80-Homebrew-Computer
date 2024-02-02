/******************************************************************************
 * @file   : main.c
 * @project: DiceRollerC
 * @brief  : Handles the main program loop
 * @author : leifs
 ******************************************************************************/

#include <stdlib.h>
#include <stdbool.h>
#include "lcd.h"
#include "ceresio.h"
#include "rng.h"
#include "program.h"

ProgramState program_state = {
    Splash,             // current_menu
    0, 0, 0, 0, 0,   // Menu & Die info
    {                   // buttons
        0, 0,           // last_state and current_state
        false, false,   // l_button
        false, false,   // d_button
        false, false,   // u_button
        false, false    // r_button
    }
};

int main(void)
{
    lcd_init(true, false);

    while(true)
    {
        readButtons(&program_state.buttons);

        switch(program_state.current_menu)
        {
        case Splash:    mSplash();      break;
        case DieSelect: mDieSelect();   break;
        case DieCount:  mDieCount();    break;
        case DieMod:    mDieMod();      break;
        case DieAnim:   mDieAnim();     break;
        case DieTotal:  mTotal();       break;
        case DieZero:   mDieZero();     break;
        case DieWompWomp: mWompWomp();  break;
        }
        // Use xorshift as busy loop, prevents LCD from flickering
        for(uint8_t i = 0; i < 10; i++) { xorshift(); }
    }
}
