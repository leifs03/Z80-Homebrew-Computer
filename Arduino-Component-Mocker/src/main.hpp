/**
 * @file    main.hpp
 * @project Homebrew Computer Arduino Driver and Component Mocker
 * @brief   Uses an Arduino Mega to drive, monitor, and mock components in the
 * system. Mocks the clock, address decoder, and DMA controller.
 * @author  leifs
 * @date    2023-10-26
 */

#ifndef ARDUINO_COMPONENT_MOCKER_MAIN_HPP
#define ARDUINO_COMPONENT_MOCKER_MAIN_HPP

void initializePins();
void processClock();

#endif //ARDUINO_COMPONENT_MOCKER_MAIN_HPP
