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
 * File:   interface.h
 * Author: Diego Moreno
 *
 * Created on 2024-03-05
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

/**********************************************************************************
 * Includes
 *********************************************************************************/


/**********************************************************************************
 * Defines, Macros and Typedefs
 *********************************************************************************/
typedef enum wireless_module_e {DA14531_CODELESS = 1, DA14531_SPS, DA16200} wireless_module_t;
typedef struct interface_s interface_t;

/**********************************************************************************
 * Function declarations
 *********************************************************************************/
interface_t* interface_init(wireless_module_t wireless_module, char called_from_app[]);
int interface_receive_start(char *response);
int interface_send(const char p_message[], const int size);
#ifndef bridge_receive_callback
void bridge_receive_callback(void);
#endif
#ifndef da16200_mqtt_webserver_receive_callback
void da16200_mqtt_webserver_receive_callback(void);
#endif

#endif // MODULE_INTERFACE_H_
