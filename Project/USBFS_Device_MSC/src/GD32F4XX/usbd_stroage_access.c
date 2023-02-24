/*!
    \file  usbd_stroage_access.c
    \brief stroage access driver

    \version 2016-08-15, V1.0.0, firmware for GD32F4xx
    \version 2018-12-12, V2.0.0, firmware for GD32F4xx
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "usb_conf.h"
#include "gd25qxx.h"
#include "ff.h"
#include "usbd_stroage_access.h"

extern FATFS fs;
extern FIL file;
extern FRESULT res;
extern BYTE work[FF_MAX_SS];

/*!
    \brief  Initialize the storage medium
    \retval Status
*/
uint32_t STORAGE_init(void)
{
    /* mount a logical drive */
    res = f_mount(&fs, "2:", 1);

    if(res == FR_NO_FILESYSTEM){
        /* Create a FAT volume */
        res = f_mkfs("2:", FM_FAT, 0, work, sizeof(work)); 

        if(res == FR_OK){
            /* unmount a logical drive */
           f_mount(NULL, "2:", 0);

           /* mount a logical drive */
           f_mount(&fs, "2:", 1);
        }
    }

    return 0;
}

/*!
    \brief      read data from the stroage medium
    \param[in]  pbuf: pointer to user buffer
    \param[in]  read_addr: address to be read
    \param[in]  block_size: size of block
    \param[in]  block_num: number of block
    \param[out] none
    \retval     operation status
*/
uint32_t STORAGE_read (uint8_t *pbuf,
                                  uint32_t read_addr,
                                  uint16_t block_size,
                                  uint32_t block_num)
{

    spi_flash_buffer_read(pbuf, read_addr, block_size * block_num);

    return 0;
}

/*!
    \brief      write data to the stroage medium
    \param[in]  pbuf: pointer to user buffer
    \param[in]  write_addr: address to be write
    \param[in]  block_size: size of block
    \param[in]  block_num: number of block
    \param[out] none
    \retval     operation status
*/
uint32_t STORAGE_write (uint8_t *pbuf,
                                  uint32_t write_addr,
                                  uint16_t block_size,
                                  uint32_t block_num)
{
    /* erase the specified flash sector */
    spi_flash_sector_erase(write_addr);

    /* write block of data to the flash */
    spi_flash_buffer_write(pbuf, write_addr, block_size * block_num);

    return 0;
}
