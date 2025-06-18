#include "rp2x_cat24m01.h"


// r/w one byte at a time
bool cat24_write_byte(int i2c_inst, uint8_t sel, int page, uint8_t addr, uint8_t src) {
	uint8_t cat24_addr = 0xA0 | (sel << 2);
	if(page > 255) cat24_addr |= 0x02;
	uint8_t _page = page & 0x00FF;

	uint8_t buffer[3] = {_page, addr, src};

	int status = i2c_write_blocking(i2c_get_instance(i2c_inst), cat24_addr, buffer, 3, false);
	if(status != 3) return false;

	return true;
}



bool cat24_read_byte(int i2c_inst, uint8_t sel, int page, uint8_t addr, uint8_t *dst) {
	uint8_t cat24_addr = 0xA0 | (sel << 2);
	if(page > 255) cat24_addr |= 0x02;
	uint8_t _page = page & 0x00FF;

	uint8_t wbuffer[2] = {_page, addr};
	int status = i2c_write_blocking(i2c_get_instance(i2c_inst), cat24_addr, wbuffer, 2, false);
	if(status != 2) return false;

	status = i2c_read_blocking(i2c_get_instance(i2c_inst), cat24_addr, dst, 1, false);
	if(status != 1) return false;

	return true;

}


// r/w up to a full page - 256 bytes
bool cat24_write_page(uint8_t sel, int page, uint8_t addr, uint8_t *src, size_t length);
bool cat24_read_page(uint8_t sel, int page, uint8_t addr, uint8_t *dst, size_t length);
