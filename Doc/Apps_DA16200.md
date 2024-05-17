# Applications for DA16200MOD (Wi-Fi module)

There are a few choices of applications with the Wi-Fi module [DA16200MOD](https://www.renesas.com/us/en/products/wireless-connectivity/wi-fi/low-power-wi-fi/da16200mod-ultra-low-power-wi-fi-modules-battery-powered-iot-devices). See below them listed in the console menu and each of them in detail.

```
***************************************************
* Choose the wireless module:                     *
* 1 - DA14531 - CodeLess (AT Commands)            *
* 2 - DA14531 - SPS (Serial Port Service)         * 
* 3 - DA16200                                     *
***************************************************

3

***************************************************
*     DA16200                                     *
*                                                 *
* Choose the application:                         *
* 0 - Example application - echo "DA16200 app"    *
* 1 - UART Bridge to send AT Commands             *
* 2 - Sending info to Web server with MQTT        *
***************************************************
```

### `1 - UART Bridge to send AT Commands`

You can type the AT commands in the console and they are transmitted to and from the module through the MCU via UART. See example below:

```
***************************************************
* Bridge Application for Renesas Wireless Modules *
***************************************************

at

OK
```


### `2 - Sending info to Web server with MQTT`

This application sends data (mock temperature data) to a MQTT broker setup at [Tagio.io](https://tago.io/) (IoT Cloud Platform) via MQTT.

#### Preparing Tago

- Create an account at [Tago.io](https://admin.tago.io/auth/login)
- Device
  - Go to _Devices_ and create a _Custom MQTT_ type device called `DA16200MOD`
  - Enter your newly created device and copy the Token at _Token & Serial Number_
- Action (Topic)
  - Go to _Actions_ and add a _MQTT Topic_ action
  - Select the `DA16200MOD` device
  - Name the action something like `topic_temperature_bucket`
  - Choose `Insert to Device Bucket` as _Type of action_
  - Put `temperature` as the _MQTT Topic_

#### Preparing the project

- Rename the file `app/da16200_credentials.h.template` to `da16200_credentials.h`
- Fill in the the Wi-Fi netword credentials (SSID and password) of the Access Point (router) you want to connect to the internet from.
- Fill in your copied Token in `MQTT_PASSWORD`
- Fill in `temperature` in `MQTT_TOPIC`
- Compile the code and flash it to the MCU
- Run the `2 - Sending info to Web server with MQTT` application from the console

#### Creating the dashboard data view

- Go to the _Dashboards_ menu, and click `+` to add a dashboard
- Add a _Line_ widget and go to _Data from_ menu
- Choose the `DA16200MOD` device
- Choose `temperature` as the variable (you need to have received data as `temperature` to set up this)
- See the data being received every couple of seconds

![Tago Dashboard](/Doc/tago_graph.jpg)
