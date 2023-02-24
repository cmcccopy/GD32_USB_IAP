/**
  ******************************************************************************
  * @file    gd32f450I_eval_exmc_sdram.h
  * @author  MCU SD
  * @version V1.0.0
  * @date    15-Jul-2015
  * @brief   The header file of the read and write sdram.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef GD32F450I_EXMC_SDRAM_H
#define GD32F450I_EXMC_SDRAM_H

#include "gd32f4xx.h"

/* sdram peripheral initialize */
void exmc_synchronous_dynamic_ram_init(uint32_t sdram_device);

/* fill the buffer with specified value */
void fill_buffer(uint8_t *pbuffer, uint16_t buffer_lengh, uint16_t offset);

/* write a byte buffer(data is 8 bits) to the EXMC SDRAM memory */
void sdram_writebuffer_8(uint32_t sdram_device, uint8_t* pbuffer, uint32_t writeaddr, uint32_t numbytetowrite);

/* read a block of 8-bit data from the EXMC SDRAM memory */
void sdram_readbuffer_8(uint32_t sdram_device, uint8_t* pbuffer, uint32_t readaddr, uint32_t numbytetoread);

#define SDRAM_DEVICE0_ADDR                         ((uint32_t)0xC0000000)
#define SDRAM_DEVICE1_ADDR                         ((uint32_t)0xD0000000)

#endif /* GD32F450I_EXMC_SDRAM_H */

/******************* (C) COPYRIGHT 2015 GIGADEVICE *****END OF FILE****/
