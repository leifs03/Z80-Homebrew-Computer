/**
 * @file    addressdecoder.cpp
 * @project Homebrew Computer Arduino Driver and Component Mocker
 * @brief   Mocks the address decoder logic
 * @author  leifs
 * @date    10/27/2023
 */

#include "addressdecoder.hpp"
#include "pindefs.hpp"
#include "busmonitor.hpp"

namespace AddressDecoder
{
    void setCEPins()
    {
        // $0000-$7FFF : ROM (8KB Shadowed)
        // $8000-$FFFF : RAM
        // Port 0 : AY3 Latch Address
        // Port 1 : AY3 Write
        // Port 2 : AY3 Read

        resetCEPins();

        // Based off of logic gates
        digitalWrite(ROM_CEB, !(BusMonitor::readMREQPin() && !digitalRead(AD15)));
        digitalWrite(RAM_CEB, !(BusMonitor::readMREQPin() && digitalRead(AD15)));
        digitalWrite(AY_BDIR, !(BusMonitor::readIORQPin() && digitalRead(AD1)));
        digitalWrite(AY_BC1, !(BusMonitor::readIORQPin() && !digitalRead(AD1)));
    }

    void resetCEPins()
    {
        digitalWrite(RAM_CEB, HIGH);
        digitalWrite(ROM_CEB, HIGH);
        digitalWrite(AY_BC1, LOW);
        digitalWrite(AY_BDIR, LOW);
    }
}