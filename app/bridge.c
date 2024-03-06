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
 * File:   bridge.c
 * Author: Diego Moreno
 *
 * Created on 2024-03-05
 */

/**********************************************************************************
 * Includes
 *********************************************************************************/
#include "bridge.h"
#include "console.h"

/**********************************************************************************
 * Defines, Macros and Typedefs
 *********************************************************************************/
#define COMMAND_SIZE    512
#define HEADER_INFO     "\r\n"\
                        "***************************************************\r\n"\
                        "* Bridge Application for Renesas Wireless Modules *\r\n"\
                        "***************************************************\r\n"\
                        "\r\n"

/**********************************************************************************
 * Global variables
 *********************************************************************************/
module_interface_t *module;

/**********************************************************************************
 * Function declarations
 *********************************************************************************/


/**********************************************************************************
 * Function definitions
 *********************************************************************************/
void bridge_run(wireless_module_t wireless_module)
{
    char command[COMMAND_SIZE];
    int command_size = 0;
    char character = '\0';

    // Initialize and start module interface
    module = module_interface_init(wireless_module);
    module_interface_receive_start(module);

    console_printf(HEADER_INFO);

    while(1)
    {
        // Get command from console
        if (console_ready_to_read() == 1)
        {
            console_read(&character, 1);

            // Build command until it gets a LF
            if (character == '\n')
            {
                // Terminate the command string
                command[command_size]   = '\r';
                command[++command_size] = '\0';

                // Line feed (LF) in the console
                console_printf("\n");

                // Send it to Module
                module_interface_send(module, command, command_size);
                command_size = 0;
            }
            else
            {
                command[command_size] = character;
                command_size++;

                // Local echo
                if (wireless_module == DA16200)
                {
                    console_printf("%c", character);
                }
            }
        }
    }
}

void module_interface_receive_callback(void)
{
    // Read the received byte
    char read_byte = module_interface_receive(module);

    // Echo text in the console
    console_printf("%c", read_byte);

    // Restart receive
    module_interface_receive_start(module);
}
