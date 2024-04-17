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

// UART Configuration
uart_cfg_t g_uart_config =
{
    .channel = 0,
    .data_bits = UART_DATA_BITS_8,
    .parity = UART_PARITY_OFF,
    .stop_bits = UART_STOP_BITS_1,
    .p_callback = g_uart0_callback,
    .p_context = NULL,
    .p_transfer_tx = NULL,
    .p_transfer_rx = NULL,
    .rxi_ipl = (12),
    .txi_ipl = (12),
    .tei_ipl = (12),
    .eri_ipl = (12),
    .rxi_irq = VECTOR_NUMBER_SCI0_RXI,
    .txi_irq = VECTOR_NUMBER_SCI0_TXI,
    .tei_irq = VECTOR_NUMBER_SCI0_TEI,
    .eri_irq = VECTOR_NUMBER_SCI0_ERI,
};

// DA14531_CODELESS
baud_setting_t baud_setting_da14531_codeless = // Baud rate: 57600
{
    .semr_baudrate_bits_b.abcse = 0,
    .semr_baudrate_bits_b.abcs = 0,
    .semr_baudrate_bits_b.bgdm = 1,
    .cks = 0,
    .brr = 107,
    .mddr = (uint8_t) 256,
    .semr_baudrate_bits_b.brme = false
};

sci_uart_extended_cfg_t g_uart0_cfg_extend_da14531_codeless =
{
    .clock = SCI_UART_CLOCK_INT,
    .rx_edge_start = SCI_UART_START_BIT_FALLING_EDGE,
    .noise_cancel = SCI_UART_NOISE_CANCELLATION_DISABLE,
    .rx_fifo_trigger = SCI_UART_RX_FIFO_TRIGGER_MAX,
    .p_baud_setting = &baud_setting_da14531_codeless,
    .flow_control = SCI_UART_FLOW_CONTROL_RTS,
    .flow_control_pin = (bsp_io_port_pin_t) UINT16_MAX,
    .rs485_setting =
    {
        .enable = SCI_UART_RS485_DISABLE,
        .polarity = SCI_UART_RS485_DE_POLARITY_HIGH,
        .de_control_pin = (bsp_io_port_pin_t) UINT16_MAX,
    },
};

// DA14531_SPS
baud_setting_t baud_setting_da14531_sps = // Baud rate: 921600
{
    .semr_baudrate_bits_b.abcse = 1,
    .semr_baudrate_bits_b.abcs = 0,
    .semr_baudrate_bits_b.bgdm = 0,
    .cks = 0,
    .brr = 17,
    .mddr = (uint8_t) 256,
    .semr_baudrate_bits_b.brme = false
};

sci_uart_extended_cfg_t g_uart0_cfg_extend_da14531_sps =
{
    .clock = SCI_UART_CLOCK_INT,
    .rx_edge_start = SCI_UART_START_BIT_FALLING_EDGE,
    .noise_cancel = SCI_UART_NOISE_CANCELLATION_DISABLE,
    .rx_fifo_trigger = SCI_UART_RX_FIFO_TRIGGER_MAX,
    .p_baud_setting = &baud_setting_da14531_sps,
    .flow_control = SCI_UART_FLOW_CONTROL_CTSRTS,
    .flow_control_pin = BSP_IO_PORT_04_PIN_12,
    .rs485_setting =
    {
        .enable = SCI_UART_RS485_DISABLE,
        .polarity = SCI_UART_RS485_DE_POLARITY_HIGH,
        .de_control_pin = (bsp_io_port_pin_t) UINT16_MAX,
    },
};

const ioport_pin_cfg_t g_bsp_pin_cfg_data_da14531_sps[] =
{
    {
        .pin = BSP_IO_PORT_04_PIN_12,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PORT_DIRECTION_OUTPUT | (uint32_t) IOPORT_CFG_PORT_OUTPUT_LOW)
    },
    {
        .pin = BSP_IO_PORT_04_PIN_13,
        .pin_cfg = ((uint32_t) IOPORT_CFG_PERIPHERAL_PIN | (uint32_t) IOPORT_PERIPHERAL_SCI0_2_4_6_8)
    },
};

ioport_cfg_t g_bsp_pin_cfg_da14531_sps =
{
    .number_of_pins = 2,
    .p_pin_cfg_data = &g_bsp_pin_cfg_data_da14531_sps[0],
};

// DA16200
baud_setting_t baud_setting_da16200 = // Baud rate: 115200
{
    .semr_baudrate_bits_b.abcse = 0,
    .semr_baudrate_bits_b.abcs = 0,
    .semr_baudrate_bits_b.bgdm = 1,
    .cks = 0,
    .brr = 53,
    .mddr = (uint8_t) 256,
    .semr_baudrate_bits_b.brme = false
};

sci_uart_extended_cfg_t g_uart0_cfg_extend_da16200 =
{
    .clock = SCI_UART_CLOCK_INT,
    .rx_edge_start = SCI_UART_START_BIT_FALLING_EDGE,
    .noise_cancel = SCI_UART_NOISE_CANCELLATION_DISABLE,
    .rx_fifo_trigger = SCI_UART_RX_FIFO_TRIGGER_MAX,
    .p_baud_setting = &baud_setting_da16200,
    .flow_control = SCI_UART_FLOW_CONTROL_RTS,
    .flow_control_pin = (bsp_io_port_pin_t) UINT16_MAX,
    .rs485_setting =
    {
        .enable = SCI_UART_RS485_DISABLE,
        .polarity = SCI_UART_RS485_DE_POLARITY_HIGH,
        .de_control_pin = (bsp_io_port_pin_t) UINT16_MAX,
    },
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
    switch (wireless_module)
    {
        case DA14531_CODELESS:
        {
            // Configuration
            g_uart_config.p_extend = &g_uart0_cfg_extend_da14531_codeless;

            status = R_SCI_UART_Open(&g_uart0_ctrl, &g_uart_config);
            assert(status == FSP_SUCCESS);
            break;
        }

        case DA14531_SPS:
        {
            // Configuration
            g_uart_config.p_extend = &g_uart0_cfg_extend_da14531_sps;

            status = R_IOPORT_Open(&g_ioport_ctrl, &g_bsp_pin_cfg_da14531_sps);
            assert(status == FSP_SUCCESS);

            status = R_SCI_UART_Open(&g_uart0_ctrl, &g_uart_config);
            assert(status == FSP_SUCCESS);
            break;
        }

        case DA16200:
        {
            // Configuration
            g_uart_config.p_extend = &g_uart0_cfg_extend_da16200;

            status = R_SCI_UART_Open(&g_uart0_ctrl, &g_uart_config);
            assert(status == FSP_SUCCESS);
            break;
        }

        default:
        {
            break;
        }
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
