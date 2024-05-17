# Applications for DA14531MOD (Bluetooth Low Energy module)

There are a few choices of applications with the Bluetooth Low Energy module [DA14531MOD](https://www.renesas.com/us/en/products/wireless-connectivity/bluetooth-low-energy/da14531mod-smartbond-tiny-bluetooth-low-energy-module). The applications are divided in the firmware image that is flashed in the module.


## CodeLess (AT Commands)

These are the applications available if you flashed the module with the AT Command firmware image ([CodeLess™ AT Commands](https://www.renesas.com/us/en/software-tool/smartbond-codeless-commands)). See below them listed in the console menu and each of them in detail.

```
***************************************************
* Choose the wireless module:                     *
* 1 - DA14531 - CodeLess (AT Commands)            *
* 2 - DA14531 - SPS (Serial Port Service)         *
* 3 - DA16200                                     *
***************************************************

1

***************************************************
*     DA14531 - CodeLess (AT Commands)            *
*                                                 *
* Choose the application:                         *
* 0 - Example application - echo "DA14531 CL"     *
* 1 - UART Bridge to send AT Commands             *
* 2 - Sending/receiving data with SmartConsole    *
***************************************************
```

### `1 - UART Bridge to send AT Commands`

You can type the AT commands in the console and they are transmitted to and from the module through the MCU via UART. See example below:

```
***************************************************
* Bridge Application for Renesas Wireless Modules *
***************************************************


AT


OK
```


### `2 - Sending/receiving data with SmartConsole`



## Serial Port Service (SPS), aka, serial cable communication emulation

These are the applications available if you flashed the module with the SPS firmware image ([Serial Port Service (SPS)](https://www.renesas.com/us/en/software-tool/serial-port-service-sps)). See below them listed in the console menu and each of them in detail.

```
***************************************************
* Choose the wireless module:                     *
* 1 - DA14531 - CodeLess (AT Commands)            *
* 2 - DA14531 - SPS (Serial Port Service)         *
* 3 - DA16200                                     *
***************************************************

2

***************************************************
*     DA14531 - SPS (Serial Port Service)         *
*                                                 *
* Choose the application:                         *
* 0 - Example application - echo "DA14531 SPS"    *
* 1 - UART Bridge                                 *
***************************************************
```

### `1 - UART Bridge`

You can connect to a cellphone with the [SmartConsole app](https://lpccs-docs.renesas.com/UM-B-088-DA1453x-Serial-Port-Service-Reference-Application/SmartConsole/SmartConsole.html) (Android/iOS) and send and receive data directly into the console and have it be transmitted through Bluetooth directly.

```
***************************************************
* Bridge Application for Renesas Wireless Modules *
***************************************************

Sending information

Information received
```

![SmartConsole example](/Doc/sps_app.jpeg)
