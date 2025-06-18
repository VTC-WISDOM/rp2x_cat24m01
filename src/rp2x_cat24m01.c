#include "rp2x_cat24m01.h"


// r/w one byte at a time
bool cat24_write_byte(i2c_inst_t i2c_inst, uint8_t sel, int page, uint8_t addr, uint8_t src) {
	uint8_t cat24_addr = 0xA0 | (sel << 2);
	if(page > 255) cat24_addr |= 0x02;
	uint8_t _page = page & 0x00FF;

	uint8_t buffer[3];
	buffer[0] = _page;
	buffer[1] = addr;
	buffer[2] = src;

	status = i2c_write_blocking(i2c_inst, cat24_addr, buffer, 3, false);
	if(status != 3) return false;

	return true;

}



bool cat24_read_byte(uint8_t sel, int page, uint8_t addr, uint8_t *dst);


// r/w up to a full page - 256 bytes
bool cat24_write_page(uint8_t sel, int page, uint8_t addr, uint8_t *src, size_t length);
bool cat24_read_page(uint8_t sel, int page, uint8_t addr, uint8_t *dst, size_t length);
