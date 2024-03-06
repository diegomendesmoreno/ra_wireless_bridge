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
 * File:   app.c
 * Author: Diego Moreno
 *
 * Created on 2024-01-25
 */

/**********************************************************************************
 * Includes
 *********************************************************************************/
#include "app.h"
#include "bridge.h"
#include "console.h"

/**********************************************************************************
 * Defines, Macros and Typedefs
 *********************************************************************************/
#define HEADER_INFO     "\r\n"\
                        "***************************************************\r\n"\
                        "* Choose the wireless module:                     *\r\n"\
                        "* 1 - DA14531                                     *\r\n"\
                        "* 2 - DA16200                                     *\r\n"\
                        "***************************************************\r\n"\
                        "\r\n"

/**********************************************************************************
 * Global variables
 *********************************************************************************/


/**********************************************************************************
 * Function declarations
 *********************************************************************************/
wireless_module_t choose_module(void);

/**********************************************************************************
 * Function definitions
 *********************************************************************************/
void main_app(void)
{
    console_init();

    // Choosing which module is connected
    wireless_module_t wireless_module = choose_module();

    bridge_run(wireless_module);
}

wireless_module_t choose_module(void)
{
    wireless_module_t wireless_module = 0;
    int received_response = 0;

    console_printf(HEADER_INFO);

    while (received_response == 0)
    {
        char character = '\0';

        if (console_ready_to_read() == 1)
        {
            console_read(&character, 1);

            int number = character - 0x30;

            switch (number)
            {
                case DA14531:
                case DA16200:
                {
                    console_printf("%d\r\n", number);
                    wireless_module = number;
                    received_response = 1;
                    break;
                }

                default:
                {
                    console_printf("Invalid input\r\n");
                    console_printf(HEADER_INFO);
                    break;
                }
            }
        }
    }

    return wireless_module;
}
