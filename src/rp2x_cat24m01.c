#include "rp2x_cat24m01.h"

//this is the only function that returns true if it fails - for obvious reasons
//datasheet says to perform a selective read because the i2c simply wont ACK if it is busy with an internal write
//instead we skip the read part and just try to write the address pointer because the rp2040 i2c will
//still return an error if it cant communicate
bool cat24_is_busy(int i2c_inst, uint8_t sel) {
	uint8_t cat24_addr = 0x50 | (sel << 1);

	uint8_t buffer[2] = {0x00};
	
	int status = i2c_write_blocking(i2c_get_instance(i2c_inst), cat24_addr, buffer, 2, false);
	if(status != 2) return true;

	return false;
}


// write one byte at a time
bool cat24_write_byte(int i2c_inst, uint8_t sel, int page, uint8_t addr, uint8_t src) {
	uint8_t cat24_addr = 0x50 | (sel << 1);
	if(page > 255) cat24_addr |= 0x01;
	uint8_t _page = page & 0x00FF;

	uint8_t buffer[3] = {0x01, addr, src};

	int status = i2c_write_blocking(i2c_get_instance(i2c_inst), cat24_addr, buffer, 3, false);
	if(status != 3) return false;

	return true;
}


// read one byte at a time
bool cat24_read_byte(int i2c_inst, uint8_t sel, int page, uint8_t addr, uint8_t *dst) {
	uint8_t cat24_addr = 0x50 | (sel << 1);
	if(page > 255) cat24_addr |= 0x01;
	uint8_t _page = page & 0x00FF;

	uint8_t buffer[2] = {_page, addr};
	int status = i2c_write_blocking(i2c_get_instance(i2c_inst), cat24_addr, buffer, 2, true);
	if(status != 2) return false;

	status = i2c_read_blocking(i2c_get_instance(i2c_inst), cat24_addr, dst, 1, false);
	if(status != 1) return false;

	return true;

}


// write up to a full page - 256 bytes
bool cat24_write_page(int i2c_inst, uint8_t sel, int page, uint8_t addr, uint8_t *src, size_t length) {
	uint8_t cat24_addr = 0x50 | (sel << 1);
	if(page > 255) cat24_addr |= 0x01;
	uint8_t _page = page & 0x00FF;

	//this gets weird; we have to slide the provided array over a little bit
	uint8_t buffer[2 + length];
	for(int i = 0; i < length; i++) {
		buffer[i+2] = src[i];
	}
	buffer[0] = _page;
	buffer[1] = addr;

	int l = sizeof(buffer);

	int status = i2c_write_blocking(i2c_get_instance(i2c_inst), cat24_addr, buffer, l, false);
	if(status != l) return false;

	return true;

}


// read up tp a full page - 256 bytes
bool cat24_read_page(int i2c_inst, uint8_t sel, int page, uint8_t addr, uint8_t *dst, size_t length) {
	uint8_t cat24_addr = 0x50 | (sel << 1);
	if(page > 255) cat24_addr |= 0x01;
	uint8_t _page = page & 0x00FF;

	uint8_t buffer[2] = {_page, addr};
	int status = i2c_write_blocking(i2c_get_instance(i2c_inst), cat24_addr, buffer, 2, true);
	if(status != 2) return false;

	status = i2c_read_blocking(i2c_get_instance(i2c_inst), cat24_addr, dst, length, false);
	if(status != length) return false;

	return true;

}
