//      Copyright (C) 2025
//      Evan Morse
//      Amelia Vlahogiannis
//      Sam Cowan
//      Marin Bove

//      This program is free software: you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation, either version 3 of the License, or
//      (at your option) any later version.

//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.

//      You should have received a copy of the GNU General Public License
//      along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include "hardware/i2c.h"
#include <stdbool.h>


/*
 sample procedure to init:
 i2c_init(I2C_INST, 100 * 1000);
 gpio_set_function(PIN_SCL, GPIO_FUNC_I2C);
 gpio_set_function(PIN_SDA, GPIO_FUNC_I2C);
 gpio_pull_up(PIN_SCL);
 gpio_pull_up(PIN_SDA);
 uint index = I2C_NUM(I2C_INST);
*/

/*
 * using this library:
 * the device is very simple and can perform either read or write operations and not much else
 * read/write_byte functions take a single bit at a time- 
 * 	usage:
 * 	cat24_write_byte(index, 0x00, 420, 0x45, write_buffer);
 * 	where:
 * 		index is the i2c number (see init procedure above)
 * 		sel (0x00) is the device address set by resistors on A2 and A1
 * 		420 is the page number (0-511)
 * 		0x45 is the address within that page (0-255)
 * 		write_buffer is a uint8_t to write to that address
 *
 * 	or:
 * 	cat24_write_page(index, 0x00, 0x01, 0x00, write_string, sizeof(write_string));
 * 	where:
 * 		write_string is a uint8_t array up to 255 elements
 * 	
 *
 * read/write functions return a 1 if i2c communication is successful and a 0 if not.
 * cat24_is_busy returns the opposite, because that made more sense to me when i wrote this
 */




// check if an internal write operation is happening
bool cat24_is_busy(int i2c_inst, uint8_t sel);

// r/w one byte at a time
bool cat24_write_byte(int i2c_inst, uint8_t sel, int page, uint8_t addr, uint8_t src);
bool cat24_read_byte(int i2c_inst, uint8_t sel, int page, uint8_t addr, uint8_t *dst);


// r/w up to a full page - 256 bytes
bool cat24_write_page(int i2c_inst, uint8_t sel, int page, uint8_t addr, uint8_t *src, size_t length);
bool cat24_read_page(int i2c_inst, uint8_t sel, int page, uint8_t addr, uint8_t *dst, size_t length);
