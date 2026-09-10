# STM32 Bootloader

This repository contains the code for a stm32f446RE bootloader. It has two STM32CubeIDE projects (application and bootloader). These are used to generate the .bin or .elf files to flash in the stm using CubeProgrammer for setup.


## Features

- Jump to application
- Flash new firmware to board
- Ensure that updates are not corrupted and have a fallback if so
- 