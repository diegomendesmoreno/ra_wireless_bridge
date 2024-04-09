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
 * File:   module_interface.c
 * Author: Diego Moreno
 *
 * Created on 2024-03-05
 */

/**********************************************************************************
 * Includes
 *********************************************************************************/
#include "interface.h"
#include "hal_data.h"
#include <stdlib.h>

/**********************************************************************************
 * Defines, Macros and Typedefs
 *********************************************************************************/


/**********************************************************************************
 * Global variables
 *********************************************************************************/
struct interface_s
{
    void *instance;
    wireless_module_t module;
    char *called_from_app;
};

const baud_setting_t baud_setting_da14531 =
{
    .semr_baudrate_bits_b.abcse = 0,
    .semr_baudrate_bits_b.abcs = 0,
    .semr_baudrate_bits_b.bgdm = 1,
    .cks = 0,
    .brr = 107,
    .mddr = (uint8_t) 256,
    .semr_baudrate_bits_b.brme = false
};

const baud_setting_t baud_setting_da16200 =
{
    .semr_baudrate_bits_b.abcse = 0,
    .semr_baudrate_bits_b.abcs = 0,
    .semr_baudrate_bits_b.bgdm = 1,
    .cks = 0,
    .brr = 53,
    .mddr = (uint8_t) 256,
    .semr_baudrate_bits_b.brme = false
};

interface_t *interface;

/**********************************************************************************
 * Function declarations
 *********************************************************************************/


/**********************************************************************************
 * Function definitions
 *********************************************************************************/
interface_t* interface_init(wireless_module_t wireless_module, char called_from_app[])
{
    fsp_err_t status;
    interface = (interface_t *) malloc(sizeof(interface_t));
    assert(interface != NULL);

    // Initialize object
    interface->instance = &g_uart0_ctrl;
    interface->module = wireless_module;
    interface->called_from_app = called_from_app;

    // Initialize UART
    status = R_SCI_UART_Open(&g_uart0_ctrl, &g_uart0_cfg);
    assert(status == FSP_SUCCESS);

    // Set baud rate
    if (wireless_module ==  DA14531)
    {
        status = R_SCI_UART_BaudSet(&g_uart0_ctrl, &baud_setting_da14531);
        assert(status == FSP_SUCCESS);
    }
    else if (wireless_module ==  DA16200)
    {
        status = R_SCI_UART_BaudSet(&g_uart0_ctrl, &baud_setting_da16200);
        assert(status == FSP_SUCCESS);
    }

    return interface;
}

int interface_receive_start(char *response)
{
    fsp_err_t status;

    // Start UART
    status = R_SCI_UART_Read(&g_uart0_ctrl, (uint8_t *) response, (uint32_t) 1);
    assert(status == FSP_SUCCESS);

    return (int) status;
}

int interface_send(const char p_message[], const int size)
{
    fsp_err_t status;

    // Transmit via UART
    status = R_SCI_UART_Write(interface->instance, (uint8_t const * const) p_message, (uint32_t) size);
    assert(status == FSP_SUCCESS);

    return (int) status;
}

/* Callback UART function */
void g_uart0_callback(uart_callback_args_t *p_args)
{
    if (p_args->event == UART_EVENT_RX_COMPLETE)
    {
        // Call module_interface callback
        if (strcmp(interface->called_from_app, "bridge") == 0)
        {
            bridge_receive_callback();
        }
        else if (strcmp(interface->called_from_app, "da16200mqtt_web_server") == 0)
        {
            da16200_mqtt_webserver_receive_callback();
        }
    }
}
