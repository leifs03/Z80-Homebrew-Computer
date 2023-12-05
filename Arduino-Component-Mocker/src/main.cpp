/**
 * @file    main.cpp
 * @project Homebrew Computer Arduino Driver and Component Mocker
 * @brief   Uses an Arduino Mega to drive, monitor, and mock components in the
 * system. Mocks the clock, address decoder, and DMA controller.
 * @author  leifs
 * @date    2023-10-26
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

#include <Arduino.h>
#include "main.hpp"
#include "pindefs.hpp"
#include "busmonitor.hpp"
#include "addressdecoder.hpp"

// NOTE: Clock speeds greater than 500 Hz are not supported.
#define Z80_CLK_HZ 3

constexpr unsigned int Z80_CLK_PERIOD_MS = (1.0 / Z80_CLK_HZ) * 1000;
constexpr unsigned int Z80_CLK_HALF_PERIOD_MS = Z80_CLK_PERIOD_MS / 2;

void setup()
{
    Serial.begin(9600);

    initializePins();
}



void loop()
{
    // If clock is set over 500 Hz, this will always run as fast as possible.
    digitalWrite(Z80_CLK, HIGH);
    // At these speeds, all of the logic can be handled in the high cycle
    processClock();
    delay(Z80_CLK_HALF_PERIOD_MS);
    digitalWrite(Z80_CLK, LOW);
    delay(Z80_CLK_HALF_PERIOD_MS);
}


void initializePins()
{
    // Set pinmodes
    pinMode(Z80_CLK, OUTPUT);
    pinMode(Z80_M1B, INPUT);
    pinMode(Z80_MREQB, INPUT);
    pinMode(Z80_IORQB, INPUT);
    pinMode(Z80_RDB, INPUT);
    pinMode(Z80_WRB, INPUT);
    pinMode(Z80_WAITB, OUTPUT);
    pinMode(Z80_BUSREQB, OUTPUT);
    pinMode(Z80_BUSACKB, INPUT);
    pinMode(RAM_CEB, OUTPUT);
    pinMode(ROM_CEB, OUTPUT);
    pinMode(ROM_OEB, INPUT);    // CPU also uses this
    pinMode(ROM_WEB, OUTPUT);
    pinMode(AY_CLK, OUTPUT);
    pinMode(AY_BDIR, OUTPUT);
    pinMode(AY_BC1, OUTPUT);
    pinMode(SERIAL_CONTROL, INPUT);

    // All the bus pins start as INPUT to not short the bus
    for(uint8_t i = 22; i < 53; i++)
    {
        pinMode(i, INPUT);
    }

    // Set values to do nothing
    digitalWrite(Z80_WAITB, HIGH);
    digitalWrite(Z80_BUSREQB, HIGH);
    digitalWrite(RAM_CEB, HIGH);
    digitalWrite(ROM_CEB, HIGH);
    digitalWrite(ROM_WEB, HIGH);
    digitalWrite(AY_BDIR, LOW);
    digitalWrite(AY_BC1, LOW);

    // AY-3-8910 has to be run between 0.1 Mhz and 4 Mhz
    // Set up pin 11 to output 1 Mhz clock
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0;
    TCCR1A |= (1 << COM1A0); // Toggle OC1A on Compare Match.
    TCCR1B |= (1 << WGM12);  // CTC mode
    TCCR1B |= (1 << CS10);   // clock on, no pre-scaler
    OCR1A = 7; // Toggle every 8 cycles for 1Mhz
}



void processClock()
{
    AddressDecoder::setCEPins();

    if(digitalRead(SERIAL_CONTROL))
    {
        Serial.print(BusMonitor::readBusState());
    }
}