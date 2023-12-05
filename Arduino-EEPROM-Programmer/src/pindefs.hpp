/**
 * @file    pindefs.hpp
 * @project Arduino EEPROM Programmer
 * @brief   Defines pinout names
 * @author  leifs
 * @date    2023-10-27
 */

/**
 * Expected pinout:
 * - Z80        : Arduino Mega
 *     - CLK    : A0
 *     - M1     : D10
 *     - MREQ   : D12
 *     - IORQ   : D13
 *     - BUSREQ : D2
 *     - WAIT   : D3
 *     - BUSACK : D4
 *     - RD     : D5
 *     - WR     : D6
 *     - D0-D7  : D23,25,27,29,31,33,35,37 (Z80 D0 to Arduino D23)
 *     - A0-A15 : D22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52 (A0 to D22)
 * - RAM        :
 *     - CS/CE  : D7
 * - ROM        :
 *     - CS/CE  : D8
 *     - WE     : D9
 *     - OE     : D14
 * - AY-3-8910  :
 *     - CLK    : D11
 *     - BDIR   : D16
 *     - BC1    : D17
 * - Control    :
 *     - Serial Output : D15
 *
 * Implementation details:
 *     - Data bus is connected to bottom row of MEGA digital pins
 *     - Address bus is connected to top row of MEGA digital pins
 *     - Serial is used to monitor address, data, and bus states each clock cycle.
 */

#ifndef ARDUINO_COMPONENT_MOCKER_PINDEFS_HPP
#define ARDUINO_COMPONENT_MOCKER_PINDEFS_HPP

// TODO: Figure out better pinout for all components, possibly use reset+upload

#define Z80_CLK     A0
#define Z80_BUSREQB 2
#define Z80_BUSACKB 4
#define ROM_CEB     8
#define ROM_OEB     14
#define ROM_WEB     9
#define RAM_CEB     7

enum DATA_BUS_PINS
{
    D0 = 23,
    D1 = 25,
    D2 = 27,
    D3 = 29,
    D4 = 31,
    D5 = 33,
    D6 = 35,
    D7 = 37
};

enum ADDRESS_BUS_PINS
{
    AD0 = 22,
    AD1 = 24,
    AD2 = 26,
    AD3 = 28,
    AD4 = 30,
    AD5 = 32,
    AD6 = 34,
    AD7 = 36,
    AD8 = 38,
    AD9 = 40,
    AD10 = 42,
    AD11 = 44,
    AD12 = 46,
    AD13 = 48,
    AD14 = 50,
    AD15 = 52
};

#endif //ARDUINO_COMPONENT_MOCKER_PINDEFS_HPP
