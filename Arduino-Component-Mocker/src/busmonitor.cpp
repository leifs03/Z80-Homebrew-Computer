/**
 * @file    busmonitor.cpp
 * @project Homebrew Computer Arduino Driver and Component Mocker
 * @brief   Uses the Serial port to print out bus states
 * @author  leifs
 * @date    10/26/2023
 */

#include "busmonitor.hpp"
#include <stdio.h>
#include "pindefs.hpp"

namespace BusMonitor
{
    String readBusState()
    {
        // Example: Read value $80 from address $AFAF
        //          R $80 @ $AFAF
        // Example: Read opcode $15 from address $FAFA
        //          PR $15 @ $FAFA
        // ID: R, W, I, O (Read, Write, Input, Output)

        char str[16]{};
        char id;

        uint8_t RWStatus = readRWPins();
        uint8_t MREQStatus = readMREQPin();
        uint8_t IORQStatus = readIORQPin();
        uint8_t M1Status = readM1Pin();

        // Bus Conflict (Severe CPU Issue!)
        if(RWStatus == 3 || (MREQStatus != 0 && IORQStatus != 0))
        {
            snprintf(str, sizeof(str), "BUS CONFLICT!");
            return str;
        }

        // Idle Bus (when CPU is internally processing)
        if(RWStatus == 0 || (MREQStatus == 0 && IORQStatus == 0))
        {
            return str;
        }

        if(MREQStatus)
        {
            id = (RWStatus - 1) ? 'R' : 'W';
        } else
        {
            id = (RWStatus - 1) ? 'I' : 'O';
        }

        snprintf(str, sizeof(str), "%c%c $%02hx @ $%04hhx\n",
                 M1Status ? 'P' : ' ', id, readDataBus(), readAddressBus()
        );

        return str;
    }



    uint8_t readDataBus()
    {
        uint8_t data = 0;
        uint8_t i = 0;
        // Data pins are interleaved with address pins b/c of physical wiring
        for(uint8_t pin = D0; pin <= D7; pin += 2)
        {
            data |= (digitalRead(pin) << i);
            i++;
        }

        return data;
    }



    uint16_t readAddressBus()
    {
        uint16_t address = 0;
        uint8_t i = 0;
        // Address pins are interleaved with address pins b/c of physical wiring
        for(uint8_t pin = AD0; pin <= AD15; pin += 2)
        {
            address |= (digitalRead(pin) << i);
            i++;
        }

        return address;
    }



    // 0 for both disabled, 1 for R enabled, 2 for W enabled, 3 for both enabled
    uint8_t readRWPins()
    {
        bool read, write;
        read = !digitalRead(Z80_RDB);  // Active low
        write = !digitalRead(Z80_WRB);

        uint8_t val = read;
        val += (write * 2);

        return val;
    }



    uint8_t readMREQPin()
    {
        return !digitalRead(Z80_MREQB); // Active low
    }



    uint8_t readIORQPin()
    {
        return !digitalRead(Z80_IORQB); // Active low
    }


    uint8_t readM1Pin()
    {
        return !digitalRead(Z80_M1B); // Active low
    }
}