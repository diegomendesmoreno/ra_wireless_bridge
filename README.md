# RA Wireless Bridge

This project is an interface bridge between a RA MCU and Renesas Wireless Modules below using the SEGGER J-Link [RTT (Real Time Transfer)](https://www.segger.com/products/debug-probes/j-link/technology/about-real-time-transfer/) terminal:

- Bluetooth Low Energy (BLE) - [DA14531MOD](https://www.renesas.com/us/en/products/wireless-connectivity/bluetooth-low-energy/da14531mod-smartbond-tiny-bluetooth-low-energy-module)
- Wi-Fi - [DA16200MOD](https://www.renesas.com/us/en/products/wireless-connectivity/wi-fi/low-power-wi-fi/da16200mod-ultra-low-power-wi-fi-modules-battery-powered-iot-devices)



# How to run it

## Hardware

This project is made for running with the boards below:

- [EK-RA4M2](https://www.renesas.com/us/en/products/microcontrollers-microprocessors/ra-cortex-m-mcus/ek-ra4m2-evaluation-kit-ra4m2-mcu-group) - Evaluation Kit for [RA4M2](https://www.renesas.com/us/en/products/microcontrollers-microprocessors/ra-cortex-m-mcus/ra4m2-100mhz-arm-cortex-m33-trustzone-high-integration-lowest-active-power-consumption) MCU Group. But it is easily portable for other MCUs. See the _[How to port this project for different RA Evaluation kits (EK)](Doc/MCU_Port.md)_ guide.
![EK-RA4M2](/Doc/EK-RA4M2.png)
- [US159-DA14531EVZ](https://www.renesas.com/us/en/products/wireless-connectivity/bluetooth-low-energy/us159-da14531evz-low-power-bluetooth-pmod-board-renesas-quick-connect-iot) - Low Power Bluetooth® Pmod™ Board for _DA14531MOD_ module
![US159-DA14531EVZ](/Doc/US159-DA14531EVZ.png)
- [US159-DA16200MEVZ](https://www.renesas.com/us/en/products/wireless-connectivity/wi-fi/low-power-wi-fi/us159-da16200mevz-ultra-low-power-wi-fi-pmod-board-renesas-quick-connect-iot) - Ultra Low Power Wi-Fi Pmod™ Board for _DA16200MOD_ module
![US159-DA16200MEVZ](/Doc/US159-DA16200MEVZ.png)

### Connecting the boards

Connect either the US159-DA14531EVZ or US159-DA16200MEVZ to the `PMOD2` connector in the RA board:

![SmartConsole example](/Doc/connecting_boards.png)


## Software

### Install the software

- RTT Terminal
  - Install the [J-Link Software pack](https://www.segger.com/downloads/jlink/) (that includes the RTT terminal)
  - Check the RTTViewer installation and usage in [Example Project Usage Guide](https://github.com/renesas/ra-fsp-examples/blob/master/example_projects/Example%20Project%20Usage%20Guide.pdf)
- To flash the RA board, either:
  - Install [Renesas Flash Programmer](https://www.renesas.com/us/en/software-tool/renesas-flash-programmer-programming-gui#downloads) to directly flash the MCU with the binary image provided in the [GitHub Releases page](https://github.com/diegomendesmoreno/ra_wireless_bridge/releases)
  - Install e2studio (IDE) and FSP (SDK) version `5.x.x` to compile and flash from the source. You can get the FSP with e2 studio installer from [FSP's GitHub Release page](https://github.com/renesas/fsp/releases).

### Flash the wireless modules with the firmware image

#### Bluetooth Low Energy (BLE) - US159-DA14531EVZ

##### CodeLess, aka, AT Commands firmware image

- Download the lastest AT Command firmware image ([CodeLess™ AT Commands](https://www.renesas.com/us/en/software-tool/smartbond-codeless-commands))
- You can use a SEGGER J-Link if you have one, or use the on-board J-Link in the RA board
  - For this, change the jumpers according to _5.2.3 Debug Out_ section of the [EK-RA4M2 v1 – User's Manual](https://www.renesas.com/us/en/document/man/ek-ra4m2-v1-users-manual?r=1470206)
  - Connect the _US159-DA14531EVZ_ in the `PMOD2` connector in the RA board
  - Connect the 10-pin connector cable between the two boards
- Flash one of the provided images (e.g. `codeless_531_00_set_two_standalone.bin`) using [SmartBond™ Flash Programmer](https://www.renesas.com/us/en/software-tool/smartbond-flash-programmer)

##### Serial Port Service (SPS), aka, serial cable communication emulation

- Download the lastest SPS firmware image ([Serial Port Service (SPS)](https://www.renesas.com/us/en/software-tool/serial-port-service-sps))
- You can use a SEGGER J-Link if you have one, or use the on-board J-Link in the RA board
  - For this, change the jumpers according to _5.2.3 Debug Out_ section of the [EK-RA4M2 v1 – User's Manual](https://www.renesas.com/us/en/document/man/ek-ra4m2-v1-users-manual?r=1470206)
  - Connect the _US159-DA14531EVZ_ in the `PMOD2` connector in the RA board
  - Connect the 10-pin connector cable between the two boards
- Flash the provided image `dsps_device_531.bin` using [SmartBond™ Flash Programmer](https://www.renesas.com/us/en/software-tool/smartbond-flash-programmer)

#### Wi-Fi - US159-DA16200MEVZ

- Download the lastest AT Command firmware image _DA16200 IMG AT Command UART_ in the page [DA16200 Wi-Fi AT Command Set](https://www.renesas.com/us/en/software-tool/da16200-wi-fi-command-set)
- Follow the steps at the section _4.5 Programming Firmware Images_ of [UM-WI-056 DA16200 DA16600 FreeRTOS Getting Started Guide](https://www.renesas.com/us/en/document/qsg/um-wi-056-da16200-da16600-freertos-getting-started-guide?r=1599971)
- For firmware upgrade, you need to use the debug interface (UART0) and not the ATCMD interface (UART1).

### Flash the MCU

- If you used the on-board J-Link to flash the BLE module, change the jumper configuration back to _Table 5. Debug On-Board Jumper Configuration_ section of the [EK-RA4M2 v1 – User's Manual](https://www.renesas.com/us/en/document/man/ek-ra4m2-v1-users-manual?r=1470206)
- To flash the MCU:
  - If you're using Renesas Flash Programmer:
    - Download the firmware binary from the [GitHub Releases page](https://github.com/diegomendesmoreno/ra_wireless_bridge/releases)
    - Follow the instruction on the article _[Getting Started with Renesas Flash Programmer](https://diegomendesmoreno.github.io/the-while-loop/en/posts/2023/09/getting-started-with-renesas-flash-programmer/)_ ([link in Portuguese](https://diegomendesmoreno.github.io/the-while-loop/pt-br/posts/2023/09/primeiros-passos-com-o-renesas-flash-programmer/)).
  - If you're using e2studio:
    - Clone or download this repository to your PC
    - Open e2studio and export the project (_3.2.12 Importing an Existing Project into e² studio_ section of [FSP User's Manual](https://www.renesas.com/us/en/software-tool/flexible-software-package-fsp))
    - Open the file `configuration.xml` to open _FSP Configuration_ and press the button _Generate Project Content_
    - Build it and go into debug to flash the firmware (_3.2.9 Debugging the Project_ section of _FSP User's Manual_)


## Run the application

With one of the wireless modules flashed and connected to the MCU (also flashed and connected with USB to the PC):

- Open RTTViewer and configure it:
  - Send on Input (`Input` >> `Sending...` >> `Send on Input`)
- Click `File` >> `Connect`
  - Target Device: `R7FA4M2AD`
  - RTT Control Block: Search Range (`0x20000000 0x10000`) or look into the guide above if it doesn't work

You should see the application menu like below:

```
***************************************************
* Choose the wireless module:                     *
* 1 - DA14531 - CodeLess (AT Commands)            *
* 2 - DA14531 - SPS (Serial Port Service)         *
* 3 - DA16200                                     *
***************************************************
```

### Applications

There a few applications to run in this project for each module, see below the list and details:

- See [applcations for DA14531MOD](Doc/Apps_DA14531.md) (Bluetooth Low energy module)
- See [applications for DA16200MOD](Doc/Apps_DA16200.md) (Wi-Fi module)
