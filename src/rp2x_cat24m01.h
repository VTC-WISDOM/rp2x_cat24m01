#include "hardware/i2c.h"
#include <stdbool.h>

// r/w one byte at a time
bool cat24_write_byte(int i2c_inst, uint8_t sel, int page, uint8_t addr, uint8_t src);

bool cat24_read_byte(int i2c_inst, uint8_t sel, int page, uint8_t addr, uint8_t *dst);


// r/w up to a full page - 256 bytes
bool cat24_write_page(uint8_t sel, int page, uint8_t addr, uint8_t *src, size_t length);
bool cat24_read_page(uint8_t sel, int page, uint8_t addr, uint8_t *dst, size_t length);
