#ifndef CAT24M01_GENERIC
#define CAT24M01_GENERIC

#include <stdbool.h>
#include <stdint.h>

//all functions return true if successful, false if unsuccessful

//the address of the device is 0xA followed by bits A2, A1, MSB of internal address, and r/w(1/0)

//base read operations (may not actually need this actually)
//ex: status = cat24_byte_read(i2c0, 0x01, 0xAA, 0x45, &dest);
bool cat24_reg_get(uint i2c_inst, uint8_t sel, uint8_t reg, uint8_t *dst);
bool cat24_reg_set(uint i2c_inst, uint8_t sel, uint8_t reg, uint8_t src);


//performs a selective read (why not just the first address then?
bool cat24_is_busy(uint i2c_inst, uint8_t sel); 


bool cat24_byte_read(uint i2c_inst, uint8_t sel, uint32_t page, uint8_t addr, uint8_t *dst);

