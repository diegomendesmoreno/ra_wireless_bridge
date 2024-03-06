# RA Wireless Bridge

This project is an interface bridge between a RA MCU and Renesas Wireless Modules below:
- Bluetooth Low Energy (BLE) - [DA14531MOD](https://www.renesas.com/us/en/products/wireless-connectivity/bluetooth-low-energy/da14531mod-smartbond-tiny-bluetooth-low-energy-module)
- Wi-Fi - [DA16200MOD](https://www.renesas.com/us/en/products/wireless-connectivity/wi-fi/low-power-wi-fi/da16200mod-ultra-low-power-wi-fi-modules-battery-powered-iot-devices)

You can type the AT commands in a console (two options below) and they are transmitted to and from the module through the MCU via UART.

- [RTT (Real Time Transfer)](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) through SEGGER J-Link
- Terminal emulator (communications) program such as Tera Term through a COM Port (USB device/peripheral CDC)


# How to run the project

## Hardware

This project is made for running with the boards below:

- [EK-RA4M2](https://www.renesas.com/us/en/products/microcontrollers-microprocessors/ra-cortex-m-mcus/ek-ra4m2-evaluation-kit-ra4m2-mcu-group) - Evaluation Kit for [RA4M2](https://www.renesas.com/us/en/products/microcontrollers-microprocessors/ra-cortex-m-mcus/ra4m2-100mhz-arm-cortex-m33-trustzone-high-integration-lowest-active-power-consumption) MCU Group. But it is easily portable for other MCUs. See the `How to port this project for different RA Evaluation kits (EK)` guide.
- [US159-DA14531EVZ](https://www.renesas.com/us/en/products/wireless-connectivity/bluetooth-low-energy/us159-da14531evz-low-power-bluetooth-pmod-board-renesas-quick-connect-iot) - Low Power Bluetooth® Pmod™ Board for _DA14531MOD_ module
- [US159-DA16200MEVZ](https://www.renesas.com/us/en/products/wireless-connectivity/wi-fi/low-power-wi-fi/us159-da16200mevz-ultra-low-power-wi-fi-pmod-board-renesas-quick-connect-iot) - Ultra Low Power Wi-Fi Pmod™ Board for _DA16200MOD_ module

## Setup

### Flashing the wireless modules with the AT Commands firmware

#### Bluetooth Low Energy (BLE) - US159-DA14531EVZ
- Download the lastest AT Command firmware image ([CodeLess™ AT Commands](https://www.renesas.com/us/en/software-tool/smartbond-codeless-commands))
- You can use a SEGGER J-Link if you have one, or use the on-board J-Link in the RA board
  - For this, change the jumpers according to _5.2.3 Debug Out_ section of the [EK-RA4M2 v1 – User's Manual](https://www.renesas.com/us/en/document/man/ek-ra4m2-v1-users-manual?r=1470206)
  - Connect the _US159-DA14531EVZ_ in the `PMOD2` connector in the RA board
  - Connect the 10-pin connector cable between the two boards
- Flash one of the provided images (e.g. `codeless_531_00_set_two_standalone`) using [SmartBond™ Flash Programmer](https://www.renesas.com/us/en/software-tool/smartbond-flash-programmer)

#### Wi-Fi - US159-DA16200MEVZ

- Download the lastest AT Command firmware image _DA16200 IMG AT Command UART_ in the page [DA16200 Wi-Fi AT Command Set](https://www.renesas.com/us/en/software-tool/da16200-wi-fi-command-set)
- Follow the steps at the section _4.5 Programming Firmware Images_ of [UM-WI-056 DA16200 DA16600 FreeRTOS Getting Started Guide](https://www.renesas.com/us/en/document/qsg/um-wi-056-da16200-da16600-freertos-getting-started-guide?r=1599971)
- For firmware upgrade, you need to use the debug interface (UART0) and not the ATCMD interface (UART1).


### MCU - EK-RA4M2 and connecting the boards

- If you used the on-board J-Link to flash the BLE module, change the jumper configuration back to _Table 5. Debug On-Board Jumper Configuration_ section of the [EK-RA4M2 v1 – User's Manual](https://www.renesas.com/us/en/document/man/ek-ra4m2-v1-users-manual?r=1470206)
- For USB, change the jumpers according to the _USB Device configuration_ described in _5.4.1 USB Full Speed_ section of the _EK-RA4M2 v1 – User's Manual_
- Connect either the US159-DA14531EVZ or US159-DA16200MEVZ to the `PMOD2` connector in the RA board


## Running the application

#### Building and flashing the application

- Clone or download this repository to your PC
- Open e2studio and export the project (_3.2.12 Importing an Existing Project into e² studio_ section of [FSP User's Manual](https://www.renesas.com/us/en/software-tool/flexible-software-package-fsp))
- Open the file `configuration.xml` to open _FSP Configuration_ and press the button _Generate Project Content_
- Leave `#define USE_RTT` at `app/console.h` to use RTT and comment it out to use Terminal through USB CDC as console
- Build it and go into debug to flash the firmware (_3.2.9 Debugging the Project_ section of _FSP User's Manual_)

#### Console - If you're using RTT

- Check the RTTViewer installation and usage in [Example Project Usage Guide](https://github.com/renesas/ra-fsp-examples/blob/master/example_projects/Example%20Project%20Usage%20Guide.pdf)
- RTTViewer configs:
  - Send on Input (`Input` >> `Sending...` >> `Send on Input`)

#### Console - If you're using Terminal through USB CDC

- Open a terminal communication program (such as Tera Term) and connect to the newly opened COM Port


### Example

```
***************************************************
* Choose the wireless module:                     *
* 1 - DA14531                                     *
* 2 - DA16200                                     *
***************************************************

1

***************************************************
* Console2Bridge Application for Wireless Modules *
***************************************************


AT


OK
```

## How to port this project for different RA Evaluation kits (EK)

- Import the Application software (`app` folder)
- Add some Heap (e.g. `0x100`) in `FSP Configuration` >> `BSP` (tab) >> `Properties` >> `RA Common` >> `Heap size (bytes)`
- Setup UART pins connected to the PMOD2 connector (see the evaluation kit user's manual or schematics)
- Setup USB peripheral CDC (if present) to get the Terminal COM Port console option with the provided descriptor
