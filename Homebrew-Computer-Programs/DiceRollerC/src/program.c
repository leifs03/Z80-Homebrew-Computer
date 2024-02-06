/******************************************************************************
 * @file   : program.c
 * @project: DiceRollerC
 * @brief  : Provides menu data and handlers
 * @author : leifs
 ******************************************************************************/

#include "program.h"
#include "lcd.h"
#include "ceresio.h"
#include "rng.h"

// Buffer for menus to place formatted strings
char fstr[17] = "                "; // Spaces + null terminator
extern ProgramState program_state; // To avoid pointers slowing down code

/**
 * @brief Clears the ProgramState for a new menu
 */
void reset_menu(void)
{
    lcd_clear();
    program_state.is_rendered = false;
    program_state.current_entry = 0;
}



/**
 * @brief Splash screen
 */
void mSplash(void)
{
    if(!program_state.is_rendered)
    {
        program_state.is_rendered = true;

        lcd_clear();
        print("DnD Dice Thing");

        lcd_movcur(1, 0);
        print("By Leif");

        lcd_movcur(1, 16); // Move cursor off-screen
    }

    if(anyButtonPressed())
    {
        reset_menu();
        program_state.current_menu = DieSelect;
    }
}



// Compiler *really* wants to do heavy stack allocation if these aren't global.
const char mdieselect_entry_str[] = "D20 D12 D10 D8 D6 D4 D100";
const uint8_t mdieselect_cursor_positions[7] = { 0, 4, 8, 12, 15, 18, 21 };
const uint8_t mdieselect_entry_vals[7] = { 20, 12, 10, 8, 6, 4, 100 };



/**
 * @brief Die select screen
 */
void mDieSelect(void)
{
    const uint8_t max_entry = 6;

    if(!program_state.is_rendered)
    {
        program_state.is_rendered = true;
        print("Select Die:");
    }

    // Format bottom string
    uint8_t cursor_pos = mdieselect_cursor_positions[program_state.current_entry];
    uint8_t fstr_index = 0;
    while(fstr_index < 16)
    {
        if((cursor_pos + fstr_index) < (sizeof(mdieselect_entry_str) - 1))
        {
            fstr[fstr_index] = mdieselect_entry_str[cursor_pos + fstr_index];
        } else
        {
            fstr[fstr_index] = ' ';
        }
        fstr_index++;
    }

    lcd_movcur(1, 0);
    print(fstr);
    lcd_movcur(1, 0);

    if(program_state.buttons.u_pressed && program_state.buttons.u_changed)
    {
        reset_menu();
        program_state.current_menu = Splash;
    }

    if(program_state.buttons.r_pressed && program_state.buttons.r_changed)
    {
        if(program_state.current_entry < max_entry)
        {
            program_state.current_entry++;
        } else
        {
            program_state.current_entry = 0;
        }
    }

    if(program_state.buttons.l_pressed && program_state.buttons.l_changed)
    {
        if(program_state.current_entry > 0)
        {
            program_state.current_entry--;
        } else
        {
            program_state.current_entry = max_entry;
        }
    }

    // Down pressed, choose option
    if(program_state.buttons.d_pressed && program_state.buttons.d_changed)
    {
        uint8_t entry = program_state.current_entry;

        reset_menu();
        program_state.die_sides = mdieselect_entry_vals[entry];
        program_state.die_count = 1;
        program_state.current_menu = DieCount;
    }
}



/**
 * @brief Die count screen
 */
void mDieCount(void)
{
    if(!program_state.is_rendered)
    {
        program_state.is_rendered = true;
        print("Number of Dice:");
    }

    // Print die count, increment index
    uitoa(program_state.die_count, fstr);
    uint8_t fstr_index = numdigits(program_state.die_count);
    // Print 'd'
    fstr[fstr_index++] = 'd';
    // Print die sides, increment index
    uitoa(program_state.die_sides, &fstr[fstr_index]);
    fstr_index += numdigits(program_state.die_sides);

    for(; fstr_index < 16; fstr_index++)
    {
        fstr[fstr_index] = ' ';
    }

    lcd_movcur(1, 0);
    print(fstr);
    lcd_movcur(1, 0);

    // Increase die count
    if(program_state.buttons.u_pressed && program_state.buttons.u_changed)
    {
        program_state.die_count++;
    }

    // Decrease die count
    if(program_state.buttons.d_pressed && program_state.buttons.d_changed)
    {
        program_state.die_count--;
    }

    // Go back
    if(program_state.buttons.l_pressed && program_state.buttons.l_changed)
    {
        reset_menu();
        program_state.die_count = 0;
        program_state.current_menu = DieSelect;
    }

    // Go forward
    if(program_state.buttons.r_pressed && program_state.buttons.r_changed)
    {
        reset_menu();
        if(program_state.die_count == 1 && program_state.die_sides == 20)
        {
            program_state.current_menu = DieMod;
        } else
        {
            program_state.current_menu = DieAnim;
        }
    }
}



const char mdiemod_entry_str[] = "Reg Adv Dis     ";
const uint8_t mdiemod_cursor_positions[3] = { 0, 4, 8 };
const ModEnum mdiemod_entry_vals[3] = { Reg, Adv, Dis };



/**
 * @brief Die modifier screen (advantage, disadvantage)
 */
void mDieMod(void)
{
    const uint8_t max_entry = 2;

    if(!program_state.is_rendered)
    {
        program_state.is_rendered = true;

        print("Die Modifier:");
        lcd_movcur(1, 0);
        print((char*)(mdiemod_entry_str));
    }

    lcd_movcur(1, mdiemod_cursor_positions[program_state.current_entry]);

    if(program_state.buttons.u_pressed && program_state.buttons.u_changed)
    {
        reset_menu();
        program_state.current_menu = DieCount;
    }

    if(program_state.buttons.r_pressed && program_state.buttons.r_changed)
    {
        if(program_state.current_entry < max_entry)
        {
            program_state.current_entry++;
        } else
        {
            program_state.current_entry = 0;
        }
    }

    if(program_state.buttons.l_pressed && program_state.buttons.l_changed)
    {
        if(program_state.current_entry > 0)
        {
            program_state.current_entry--;
        } else
        {
            program_state.current_entry = max_entry;
        }
    }

    if(program_state.buttons.d_pressed && program_state.buttons.d_changed)
    {
        program_state.die_mod = mdiemod_entry_vals[program_state.current_entry];
        reset_menu();
        program_state.current_menu = DieAnim;
    }
}



/**
 * @brief Small waiting animation for suspense
 */
void mDieAnim(void)
{
    print(".");
    program_state.current_entry++;

    // Busy wait
    for(volatile uint16_t i = 0; i < 20000; i++) {}

    if(program_state.current_entry == 3)
    {
        reset_menu();
        if(program_state.die_count == 0 || program_state.die_sides == 0)
        {
            program_state.current_menu = DieZero;
        } else
        {
            program_state.current_menu = DieTotal;
        }
    }
}



/**
 * @brief Screen to display the total
 */
void mTotal(void)
{
    bool extreme_difference = false;

    if(!program_state.is_rendered)
    {
        uint16_t roll_a;
        uint16_t roll_b;
        char roll_str[6];

        program_state.is_rendered = true;
        print("You Rolled...");
        lcd_movcur(1, 0);

        roll_a = roll(program_state.die_count, program_state.die_sides);
        roll_b = roll(program_state.die_count, program_state.die_sides);

        if((roll_a == 1 && roll_b == 20) || (roll_b == 1 && roll_a == 20))
        {
            extreme_difference = true;
        }

        // Usually want separate rolls with multiple D20s
        // Limit of 5 because advanced string rendering is annoying.
        if(
            program_state.die_count > 1 &&
                program_state.die_count < 6 &&
                program_state.die_sides == 20
            )
        {
            for(uint8_t i = 0; i < program_state.die_count; i++)
            {
                uitoa(roll(1, 20), roll_str);
                print(roll_str);
                print(" ");
            }
        } else
        {
            switch(program_state.die_mod)
            {
            case Reg:
            {
                uitoa(roll_a, roll_str);
                print(roll_str);
                break;
            }
            case Adv:
            {
                uitoa(max16(roll_a, roll_b), roll_str);
                print(roll_str);
                print(" instead of ");
                uitoa(min16(roll_a, roll_b), roll_str);
                print(roll_str);
                break;
            }
            case Dis:
            {
                uitoa(min16(roll_a, roll_b), roll_str);
                print(roll_str);
                print(" instead of ");
                uitoa(max16(roll_a, roll_b), roll_str);
                print(roll_str);
                break;
            }
            }
        }

        lcd_movcur(1, 16);
    }

    if(anyButtonPressed())
    {
        reset_menu();
        if(extreme_difference && program_state.die_mod == Dis)
        {
            program_state.die_mod = Reg;
            program_state.current_menu = DieWompWomp;
        } else
        {
            program_state.die_mod = Reg;
            program_state.current_menu = DieSelect;
        }
    }
}



/**
 * @brief Easter egg for having a custom Zero die
 */
void mDieZero(void)
{
    if(!program_state.is_rendered)
    {
        program_state.is_rendered = true;
        print("And nothing");
        lcd_movcur(1, 0);
        print("happened...");
        lcd_movcur(1, 16);
    }

    if(anyButtonPressed())
    {
        reset_menu();
        program_state.die_mod = Reg;
        program_state.current_menu = DieSelect;
    }
}



/**
 * @brief Easter egg for rolling a 1 and 20 at disadvantage
 */
void mWompWomp(void)
{
    if(!program_state.is_rendered)
    {
        program_state.is_rendered = true;
        print("Womp");
        // Busy wait
        for(volatile uint16_t i = 0; i < 20000; i++) {}
        lcd_movcur(1, 3);
        print("Womp...");
        lcd_movcur(1, 16);
    }

    if(anyButtonPressed())
    {
        reset_menu();
        program_state.current_menu = DieSelect;
    }
}



/**
 * @return Whether any button is newly pressed
 */
bool anyButtonPressed(void)
{
    return
        (program_state.buttons.l_pressed && program_state.buttons.l_changed) ||
        (program_state.buttons.d_pressed && program_state.buttons.d_changed) ||
        (program_state.buttons.u_pressed && program_state.buttons.u_changed) ||
        (program_state.buttons.r_pressed && program_state.buttons.r_changed);
}
