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
 * File:   module.h
 * Author: Diego Moreno
 *
 * Created on 2024-04-08
 */

#ifndef MODULE_H_
#define MODULE_H_

/**********************************************************************************
 * Includes
 *********************************************************************************/
#include "interface.h"

/**********************************************************************************
 * Defines, Macros and Typedefs
 *********************************************************************************/
typedef struct module_s module_t;

/**********************************************************************************
 * Function declarations
 *********************************************************************************/
module_t* module_init(wireless_module_t wireless_module, char called_from_app[]);
void module_receive_start(module_t *module);
char module_receive(module_t *module);
void module_send(const char p_message[], const int size);

#endif // MODULE_H_
