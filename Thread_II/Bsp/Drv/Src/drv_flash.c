/**
 * @file drv_flash.c
 * @author A-rtos (A-rtos@outlook.com)
 * @brief Flash读写驱动
 * @version 0.1
 * @date 2026-03-08
 * 
 * @copyright Copyright (c) 2026 A-rtos
 * 
 */

#include "drv_flash.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Flash 擦除指定页
 * @param page_addr 页地址（页内任意地址）
 * @return flash_status_t 状态
 */
void flash_erase_page(uint32_t PageNum)
{
    /* 解锁 Flash */
    fmc_unlock();
    
    /* 清除所有标志位 */
    fmc_flag_clear(FMC_FLAG_BANK0_END);
    fmc_flag_clear(FMC_FLAG_BANK0_WPERR);
    fmc_flag_clear(FMC_FLAG_BANK0_PGERR);
    
    /* 擦除页 */
    fmc_page_erase(FLASH_BASE_ADDR + (FLASH_PAGE_SIZE * PageNum));
    
    /* 锁定 Flash */
    fmc_lock();
}

/**
 * @brief Flash 按字写入多个字节
 * @param addr 写入地址（必须为4字节对齐）
 * @param buf 数据缓冲区
 * @param len 写入长度（字节数）
 * @note 写入前必须先擦除对应页，地址必须4字节对齐
 */
void flash_write_words(uint32_t addr, const uint8_t *buf, uint32_t len)
{
    uint32_t i;
    uint32_t word_data;
    uint32_t current_addr = addr;
    uint32_t bytes_written = 0;
    
    /* 参数检查 */
    if (buf == NULL || len == 0) {
        return;
    }
    
    /* 地址必须4字节对齐 */
    if (addr & 0x03) {
        return;
    }
    
    /* unlock the flash program/erase controller */
    fmc_unlock();

    /* clear all pending flags */
    fmc_flag_clear(FMC_FLAG_BANK0_END);
    fmc_flag_clear(FMC_FLAG_BANK0_WPERR);
    fmc_flag_clear(FMC_FLAG_BANK0_PGERR);

    /* program flash by word (32-bit) */
    while (bytes_written < len) {
        word_data = 0xFFFFFFFF;  /* 默认填充0xFF */
        
        /* 组装一个字（4字节） */
        for (i = 0; i < 4 && bytes_written < len; i++) {
            word_data &= ~(0xFF << (i * 8));
            word_data |= ((uint32_t)buf[bytes_written] << (i * 8));
            bytes_written++;
        }
        
        /* 写入一个字 */
        fmc_word_program(current_addr, word_data);
        current_addr += 4;
    }

    /* lock the main FMC after the program operation */
    fmc_lock();
}

/**
 * @brief Flash 读取一个字（32位）
 * @param addr 读取地址
 * @return 读取的数据
 */
uint32_t flash_read_word(uint32_t addr)
{
    return (*(__IO uint32_t *)addr);
}

/**
 * @brief Flash 读取一个字节
 * @param addr 读取地址
 * @return 读取的数据
 */
uint8_t flash_read_byte(uint32_t addr)
{
    return (*(__IO uint8_t *)addr);
}

/**
 * @brief Flash 读取多个字节
 * @param addr 读取地址
 * @param buf 数据缓冲区
 * @param len 读取长度
 */
void flash_read_bytes(uint32_t addr, uint8_t *buf, uint32_t len)
{
    uint32_t i;

    for (i = 0; i < len; i++)
    {
        buf[i] = *(__IO uint8_t *)(addr + i);
    }
}
