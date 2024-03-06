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
 * File:   console.c
 * Author: Diego Moreno
 *
 * Created on 2024-03-05
 */

/**********************************************************************************
 * Includes
 *********************************************************************************/
#include "console.h"
#include "stdarg.h"
#include "SEGGER_RTT/SEGGER_RTT.h"

/**********************************************************************************
 * Defines, Macros and Typedefs
 *********************************************************************************/


/**********************************************************************************
 * Global variables
 *********************************************************************************/


/**********************************************************************************
 * Function declarations
 *********************************************************************************/


/**********************************************************************************
 * Function definitions
 *********************************************************************************/

void console_init(void)
{
#ifdef USE_RTT
    SEGGER_RTT_Init();
#endif
}

int console_printf(const char * str_format, ...)
{
    int number_bytes = 1;

#ifdef USE_RTT
    va_list args;
    va_start(args, str_format);
    number_bytes = SEGGER_RTT_vprintf(0, str_format, &args);
    va_end(args);
#endif

    return number_bytes;
}

int console_read(char *p_buffer, int buffer_size)
{
    int number_bytes = 0;

#ifdef USE_RTT
    SEGGER_RTT_Read(0, (void*) p_buffer, (unsigned) buffer_size);
#endif

    return number_bytes;
}

int console_ready_to_read(void)
{
    int success = 0;

#ifdef USE_RTT
    if (SEGGER_RTT_HasKey() == 1)
    {
        // At least one character is available
        success = 1;
    }
    else
    {
        // No characters are available to read
        success = 0;
    }
#endif

    return success;
}

