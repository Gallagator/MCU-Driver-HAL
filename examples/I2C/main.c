/* Copyright (c) 2021 Arm Limited
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "bootstrap/mbed_trace.h"
#include "hal/serial_api.h"

#define TRACE_GROUP "main"

static serial_t stdio_uart;

static void serial_print(const char *string);
static void begin_trace(void);

int main()
{
    begin_trace();
    
    tr_info("TEST");

    return 0;
}

static void serial_print(const char *string)
{
    while (*string != '\0') {
        serial_putc(&stdio_uart, *string);
        string++;
    }
    serial_putc(&stdio_uart, '\n');
}

static void begin_trace(void) 
{
    serial_init(&stdio_uart, CONSOLE_TX, CONSOLE_RX);
    serial_baud(&stdio_uart, MBED_CONF_PLATFORM_STDIO_BAUD_RATE);

    mbed_trace_init();
    mbed_trace_print_function_set(serial_print);
}

