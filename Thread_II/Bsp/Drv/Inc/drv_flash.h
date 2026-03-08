#ifndef DRV_FLASH_H
#define DRV_FLASH_H

#include "main.h"

#define FLASH_PAGE_SIZE         ((uint32_t)0x800)    /* 2KB per page */
#define FLASH_BASE_ADDR         ((uint32_t)0x08000000)
#define FLASH_END_ADDR          ((uint32_t)0x0807FFFF)

void flash_erase_page(uint32_t PageNum);
void flash_write_words(uint32_t addr, const uint8_t *buf, uint32_t len);
uint32_t flash_read_word(uint32_t addr);
uint8_t flash_read_byte(uint32_t addr);
void flash_read_bytes(uint32_t addr, uint8_t *buf, uint32_t len);

#endif /* DRV_FLASH_H */
