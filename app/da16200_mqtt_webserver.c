/*
 * MIT License
 * 
 * Copyright (c) 2024 Diego Moreno
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * File:   da16200_mqtt_webserver.c
 * Author: Diego Moreno
 *
 * Created on 2024-04-08
 */

/**********************************************************************************
 * Includes
 *********************************************************************************/
#include "console.h"
#include "da16200_mqtt_webserver.h"
#include "da16200_credentials.h"
#include "utils/delay.h"
#include <stdio.h>
#include <string.h>

/**********************************************************************************
 * Defines, Macros and Typedefs
 *********************************************************************************/
typedef struct app_mqtt_webserver_s
{
    module_interface_t *module;
} app_mqtt_webserver_t;

/**********************************************************************************
 * Global variables
 *********************************************************************************/
app_mqtt_webserver_t *app_mqtt_webserver;

/**********************************************************************************
 * Function declarations
 *********************************************************************************/
static void _send_command(const char command[]);
static void _reset_module(void);
static void _connect_to_internet(const char ssid[], const char password[]);
static void _mqtt_setup(const char host[], const char port[], const char username[], const char passwork[], const char pub_topic[]);
static void _mqtt_send_data(int value);

/**********************************************************************************
 * Function definitions
 *********************************************************************************/
void mqtt_webserver_run(void)
{
    const int DELAY = 5000;
    const char HEADER_INFO[] =  "\r\n"\
                                "***************************************************\r\n"\
                                "* Sending info to Web server with MQTT            *\r\n"\
                                "***************************************************\r\n"\
                                "\r\n";

    // Initialize and start module interface
    app_mqtt_webserver->module = module_interface_init(DA16200, "da16200mqtt_web_server");
    module_interface_receive_start(app_mqtt_webserver->module);

    console_printf(HEADER_INFO);

    // Script
    _reset_module();
    delay_ms(DELAY);

    _connect_to_internet(WIFI_SSID, WIFI_PASSWORD);
    delay_ms(DELAY);

    _mqtt_setup(MQTT_HOST, MQTT_TCP_IP_PORT, MQTT_USERNAME, MQTT_PASSWORD, MQTT_TOPIC);
    delay_ms(DELAY);

    while(1)
    {
        for (int i = 15; i < 40; i++)
        {
            _mqtt_send_data(i);
            delay_ms(DELAY);
        }
    }
}

static void _send_command(const char command[])
{
    char buffer[100];
    int len = (int) strlen(command);

    strcpy(buffer, command);

    // Terminate the command string
    buffer[len++] = '\r';
    buffer[len++] = '\0';

    // Send to console and to module
    console_printf(buffer);
    module_interface_send(app_mqtt_webserver->module, buffer, len);
}

static void _reset_module(void)
{
    const char COMMANDS[] = "ATF";

    _send_command(COMMANDS);
}

static void _connect_to_internet(const char ssid[], const char password[])
{
    char buffer[100];

    // Assemble the command
    sprintf(buffer, "AT+WFJAP=%s,%d,%d,%s\r\n", ssid, 4, 2, password);

    _send_command(buffer);
}

static void _mqtt_setup(const char host[], const char port[], const char username[], const char passwork[], const char pub_topic[])
{
    const int DELAY = 5000;
    char buffer[100];
    memset(buffer, '\0', 100);

    // Set host name and port number
    sprintf(buffer, "AT+NWMQBR=%s,%s\r\n", host, port);
    _send_command(buffer);
    delay_ms(DELAY);
    memset(buffer, '\0', 100);

    // MQTT login information
    sprintf(buffer, "AT+NWMQLI=%s,%s\r\n", username, passwork);
    _send_command(buffer);
    delay_ms(DELAY);
    memset(buffer, '\0', 100);

    // Set the topic(s) of the MQTT publisher
    sprintf(buffer, "AT+NWMQTP='%s'\r\n", pub_topic);
    _send_command(buffer);
    delay_ms(DELAY);

    // Enable MQTT client
    _send_command("AT+NWMQCL=1");
    delay_ms(DELAY);
}

static void _mqtt_send_data(int value)
{
    char buffer[100];
    memset(buffer, '\0', 100);

    // Assemble the command
    sprintf(buffer, "AT+NWMQMSG='[{\"variable\":\"temperature\", \"value\":%d}]'\r\n", value);

    _send_command(buffer);
}

void da16200_mqtt_webserver_receive_callback(void)
{
    // Read the received byte
    char read_byte = module_interface_receive(app_mqtt_webserver->module);

    // Echo text in the console
    console_printf("%c", read_byte);

    // Restart receive
    module_interface_receive_start(app_mqtt_webserver->module);
}
