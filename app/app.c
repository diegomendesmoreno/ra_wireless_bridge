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
#include "da16200_mqtt_webserver.h"

/**********************************************************************************
 * Defines, Macros and Typedefs
 *********************************************************************************/


/**********************************************************************************
 * Global variables
 *********************************************************************************/


/**********************************************************************************
 * Function declarations
 *********************************************************************************/
static wireless_module_t menu_choose_module(void);
static void menu_choose_application(wireless_module_t module);

/**********************************************************************************
 * Function definitions
 *********************************************************************************/
void main_app(void)
{
    console_init();

    // Choosing which module is connected
    wireless_module_t wireless_module = menu_choose_module();

    menu_choose_application(wireless_module);
}

static wireless_module_t menu_choose_module(void)
{
    wireless_module_t wireless_module = 0;
    int received_response = 0;
    const char MENU_MODULE_HEADER[] =   "\r\n"\
                                        "***************************************************\r\n"\
                                        "* Choose the wireless module:                     *\r\n"\
                                        "* 1 - DA14531 - CodeLess (AT Commands)            *\r\n"\
                                        "* 2 - DA14531 - SPS (Serial Port Service)         *\r\n"\
                                        "* 3 - DA16200                                     *\r\n"\
                                        "***************************************************\r\n"\
                                        "\r\n";

    // print header
    console_printf(MENU_MODULE_HEADER);

    while (received_response == 0)
    {
        char character = '\0';

        if (console_ready_to_read() == 1)
        {
            console_read(&character, 1);

            int option = character - 0x30;

            switch (option)
            {
                case DA14531_CODELESS:
                case DA14531_SPS:
                case DA16200:
                {
                    // echo choice
                    console_printf("%d\r\n", option);

                    wireless_module = option;
                    received_response = 1;
                    break;
                }

                default:
                {
                    console_printf("Invalid input\r\n");

                    // print header
                    console_printf(MENU_MODULE_HEADER);
                    break;
                }
            }
        }
    }

    return wireless_module;
}

static void menu_choose_application(wireless_module_t module)
{
    int received_response = 0;
    const char MENU_APPS_DA14531_CODELESS_HEADER[] =    "\r\n"\
                                                        "***************************************************\r\n"\
                                                        "*     DA14531 - CodeLess (AT Commands)            *\r\n"\
                                                        "*                                                 *\r\n"\
                                                        "* Choose the application:                         *\r\n"\
                                                        "* 0 - Example application - echo \"DA14531 CL\"     *\r\n"\
                                                        "* 1 - UART Bridge to send AT Commands             *\r\n"\
                                                        "* 2 - Sending/receiving data with SmartConsole    *\r\n"\
                                                        "***************************************************\r\n"\
                                                        "\r\n";

    const char MENU_APPS_DA14531_SPS_HEADER[] =         "\r\n"\
                                                        "***************************************************\r\n"\
                                                        "*     DA14531 - SPS (Serial Port Service)         *\r\n"\
                                                        "*                                                 *\r\n"\
                                                        "* Choose the application:                         *\r\n"\
                                                        "* 0 - Example application - echo \"DA14531 SPS\"    *\r\n"\
                                                        "* 1 - UART Bridge                                 *\r\n"\
                                                        "***************************************************\r\n"\
                                                        "\r\n";

    const char MENU_APPS_DA16200_HEADER[] =             "\r\n"\
                                                        "***************************************************\r\n"\
                                                        "*     DA16200                                     *\r\n"\
                                                        "*                                                 *\r\n"\
                                                        "* Choose the application:                         *\r\n"\
                                                        "* 0 - Example application - echo \"DA16200 app\"    *\r\n"\
                                                        "* 1 - UART Bridge to send AT Commands             *\r\n"\
                                                        "* 2 - Sending info to Web server with MQTT        *\r\n"\
                                                        "***************************************************\r\n"\
                                                        "\r\n";

    switch (module)
    {
        case DA14531_CODELESS:
        {
            // print header
            console_printf(MENU_APPS_DA14531_CODELESS_HEADER);

            while (received_response == 0)
            {
                char character = '\0';

                if (console_ready_to_read() == 1)
                {
                    console_read(&character, 1);

                    int option = character - 0x30;

                    switch (option)
                    {
                        case 0:
                        {
                            // echo choice
                            console_printf("%d\r\n", option);

                            console_printf("\r\nDA14531 CL\r\n", option);

                            // print header
                            console_printf(MENU_APPS_DA14531_CODELESS_HEADER);
                            break;
                        }

                        case 1:
                        {
                            // echo choice
                            console_printf("%d\r\n", option);

                            bridge_run(module);

                            received_response = 1;
                            break;
                        }

                        case 2:
                        {
                            // echo choice
                            console_printf("%d\r\n", option);

                            console_printf("\r\nSending/receiving data with SmartConsole\r\n", option);

                            received_response = 1;
                            break;
                        }

                        default:
                        {
                            console_printf("Invalid input\r\n");

                            // print header
                            console_printf(MENU_APPS_DA14531_CODELESS_HEADER);
                            break;
                        }
                    }
                }
            }
            break;
        }

        case DA14531_SPS:
        {
            // print header
            console_printf(MENU_APPS_DA14531_SPS_HEADER);

            while (received_response == 0)
            {
                char character = '\0';

                if (console_ready_to_read() == 1)
                {
                    console_read(&character, 1);

                    int option = character - 0x30;

                    switch (option)
                    {
                        case 0:
                        {
                            // echo choice
                            console_printf("%d\r\n", option);

                            console_printf("\r\nDA14531 SPS\r\n", option);

                            // print header
                            console_printf(MENU_APPS_DA14531_SPS_HEADER);
                            break;
                        }

                        case 1:
                        {
                            // echo choice
                            console_printf("%d\r\n", option);

                            bridge_run(module);

                            received_response = 1;
                            break;
                        }

                        default:
                        {
                            console_printf("Invalid input\r\n");

                            // print header
                            console_printf(MENU_APPS_DA14531_SPS_HEADER);
                            break;
                        }
                    }
                }
            }
            break;
        }

        case DA16200:
        {
            // print header
            console_printf(MENU_APPS_DA16200_HEADER);

            while (received_response == 0)
            {
                char character = '\0';

                if (console_ready_to_read() == 1)
                {
                    console_read(&character, 1);

                    int option = character - 0x30;

                    switch (option)
                    {
                        case 0:
                        {
                            // echo choice
                            console_printf("%d\r\n", option);

                            console_printf("\r\nDA16200 app\r\n", option);

                            // print header
                            console_printf(MENU_APPS_DA16200_HEADER);
                            break;
                        }

                        case 1:
                        {
                            // echo choice
                            console_printf("%d\r\n", option);

                            bridge_run(module);

                            received_response = 1;
                            break;
                        }

                        case 2:
                        {
                            // echo choice
                            console_printf("%d\r\n", option);

                            mqtt_webserver_run();

                            received_response = 1;
                            break;
                        }

                        default:
                        {
                            console_printf("Invalid input\r\n");

                            // print header
                            console_printf(MENU_APPS_DA16200_HEADER);
                            break;
                        }
                    }
                }
            }
            break;
        }

        default:
        {
            break;
        }
    }
}
