/**
 * @file    busmonitor.hpp
 * @project Homebrew Computer Arduino Driver and Component Mocker
 * @brief   Uses the Serial port to print out bus states
 * @author  leifs
 * @date    10/26/2023
 */

#ifndef ARDUINO_COMPONENT_MOCKER_BUSMONITOR_HPP
#define ARDUINO_COMPONENT_MOCKER_BUSMONITOR_HPP

#include <Arduino.h>

namespace BusMonitor
{
    String readBusState();
    uint8_t readDataBus();
    uint16_t readAddressBus();
    // 0 for both disabled, 1 for R enabled, 2 for W enabled, 3 for both enabled
    uint8_t readRWPins();
    uint8_t readMREQPin();
    uint8_t readIORQPin();
    uint8_t readM1Pin();
}

#endif //ARDUINO_COMPONENT_MOCKER_BUSMONITOR_HPP
