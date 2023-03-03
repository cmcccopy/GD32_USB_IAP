/*!
    \file  iap.c
    \brief in application program file

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

#include "iap.h"
#include "ff.h"
#include "led.h"

FATFS fs;
FIL file;
FRESULT res;
BYTE work[FF_MAX_SS];

#ifdef  __ICCARM__ 
  #pragma optimize = none
#endif
/*!
    \brief      check and update the application
    \param[in]  none
    \param[out] none
    \retval     update state: NO_APP, APP_UPDATED, APP_UPDATEFAILD
*/
UPDATE_STATE update_application(void)
{
    UPDATE_STATE update_state;
    uint32_t applen, readnum, start_sector, end_sector, write_addr = APPLICATIONADDRESS;

    /* mount a logical drive */
    f_mount(&fs, "2:", 1);

    /* Open the file of "update.bin" */
    res = f_open(&file, "2:update.bin", FA_READ);

    if(FR_OK == res){
        /* get size of the file */
        applen = f_size(&file);

        /* unlock the flash program erase controller */
        fmc_unlock();

        /* erase the internal flash of GDMCU */
        start_sector = fmc_sector_get(APPLICATIONADDRESS);
        end_sector = fmc_sector_get(APPLICATIONADDRESS + applen);

        for(uint32_t erase_sector = start_sector; erase_sector <= end_sector; erase_sector += 8){
            fmc_erase_sector(erase_sector);
        }

        /* reads the target BIN and writes it to internal flash */
        for(uint32_t i = 0; i < applen; i += readnum){
            res = f_read(&file, work, sizeof(work), &readnum);

            if(FR_OK != res){
                break;
            }

            fmc_write_32bit_data(write_addr, readnum/4, (uint32_t*)work);
            write_addr += readnum;
        }

        /* judge the update state */
        if(FR_OK == res){
            update_state = APP_UPDATED;

            /* delete update.bin */
            f_unlink("2:update.bin");

            /* update success, LED1 glitter 3 times */
            for(uint8_t i = 0; i < 6; i++){
                led1_open(G);
               // for(uint32_t j = 0; j < 10000000; j++);
            }
        } else {
            update_state = APP_UPDATEFAILD;

            /* delete update.bin */
           f_unlink("2:update.bin");

            /* update fail, erase internal flash of written */
            for(uint32_t erase_sector = start_sector; erase_sector <= end_sector; erase_sector += 8){
                fmc_erase_sector(erase_sector);
            }
        }

        /* lock the flash program erase controller */
        fmc_lock();
    } else {
        update_state = NO_APP;
    }

    return update_state;
}

/*!
    \brief      gets the sector of a given address
    \param[in]  addr: a given address(0x08000000~0x080FFFFF)
    \param[out] none
    \retval     the sector of a given address
*/
uint32_t fmc_sector_get(uint32_t addr)
{
    uint32_t sector = 0;

    if ((addr < ADDR_FMC_SECTOR_1) && (addr >= ADDR_FMC_SECTOR_0)) {
        sector = CTL_SECTOR_NUMBER_0;
    } else if ((addr < ADDR_FMC_SECTOR_2) && (addr >= ADDR_FMC_SECTOR_1)) {
        sector = CTL_SECTOR_NUMBER_1;
    } else if ((addr < ADDR_FMC_SECTOR_3) && (addr >= ADDR_FMC_SECTOR_2)) {
        sector = CTL_SECTOR_NUMBER_2;
    } else if ((addr < ADDR_FMC_SECTOR_4) && (addr >= ADDR_FMC_SECTOR_3)) {
        sector = CTL_SECTOR_NUMBER_3;
    } else if ((addr < ADDR_FMC_SECTOR_5) && (addr >= ADDR_FMC_SECTOR_4)) {
        sector = CTL_SECTOR_NUMBER_4;
    } else if ((addr < ADDR_FMC_SECTOR_6) && (addr >= ADDR_FMC_SECTOR_5)) {
        sector = CTL_SECTOR_NUMBER_5;
    } else if ((addr < ADDR_FMC_SECTOR_7) && (addr >= ADDR_FMC_SECTOR_6)) {
        sector = CTL_SECTOR_NUMBER_6;
    } else if ((addr < ADDR_FMC_SECTOR_8) && (addr >= ADDR_FMC_SECTOR_7)) {
        sector = CTL_SECTOR_NUMBER_7;
    } else if ((addr < ADDR_FMC_SECTOR_9) && (addr >= ADDR_FMC_SECTOR_8)) {
        sector = CTL_SECTOR_NUMBER_8;
    } else if ((addr < ADDR_FMC_SECTOR_10) && (addr >= ADDR_FMC_SECTOR_9)) {
        sector = CTL_SECTOR_NUMBER_9;
    } else if ((addr < ADDR_FMC_SECTOR_11) && (addr >= ADDR_FMC_SECTOR_10)) {
        sector = CTL_SECTOR_NUMBER_10;
    } else {
        sector = CTL_SECTOR_NUMBER_11;
    }

    return sector;
}

/*!
    \brief      erases the sector of a given sector number
    \param[in]  fmc_sector: a given sector number
      \arg        CTL_SECTOR_NUMBER_0: sector 0
      \arg        CTL_SECTOR_NUMBER_1: sector 1
      \arg        CTL_SECTOR_NUMBER_2: sector 2
      \arg        CTL_SECTOR_NUMBER_3: sector 3
      \arg        CTL_SECTOR_NUMBER_4: sector 4
      \arg        CTL_SECTOR_NUMBER_5: sector 5
      \arg        CTL_SECTOR_NUMBER_6: sector 6
      \arg        CTL_SECTOR_NUMBER_7: sector 7
      \arg        CTL_SECTOR_NUMBER_8: sector 8
      \arg        CTL_SECTOR_NUMBER_9: sector 9
      \arg        CTL_SECTOR_NUMBER_10: sector 10
      \arg        CTL_SECTOR_NUMBER_11: sector 11
    \param[out] none
    \retval     none
*/
void fmc_erase_sector(uint32_t fmc_sector)
{
    /* unlock the flash program erase controller */
    fmc_unlock(); 
    /* clear pending flags */
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);
    /* wait the erase operation complete*/
    if(FMC_READY != fmc_sector_erase(fmc_sector)){
        while(1);
    }
    /* lock the flash program erase controller */
    fmc_lock();
}

/*!
    \brief      write 32 bit length data to a given address
    \param[in]  address: a given address(0x08000000~0x080FFFFF)
    \param[in]  length: data length
    \param[in]  data_32: data pointer
    \param[out] none
    \retval     none
*/
void fmc_write_32bit_data(uint32_t address, uint16_t length, uint32_t* data_32)
{
    /* unlock the flash program erase controller */
    fmc_unlock();
    /* clear pending flags */
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);
    /* write data_32 to the corresponding address */
    for(uint16_t i=0; i<length; i++){
        if(FMC_READY == fmc_word_program(address, data_32[i])){
            address = address + 4;
        }else{ 
            while(1);
        }
    }
    /* lock the flash program erase controller */
    fmc_lock();
}
