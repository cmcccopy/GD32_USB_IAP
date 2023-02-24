/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"            /* Obtains integer types */
#include "diskio.h"        /* Declarations of disk functions */
#ifdef USE_SPI_FLASH
#include "gd25qxx.h"
#include "usbd_stroage_access.h"
#endif
#ifdef USE_INTERNAL_FLASH
#include "usbd_stroage_access.h"
#endif

/* Definitions of physical drive number for each drive */
#define DEV_RAM                     0    /* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC                     1    /* Example: Map MMC/SD card to physical drive 1 */
#define DEV_SPI_FLASH               2    /* Example: Map SPI FLASH to physical drive 2 */
#define DEV_INTERNAL_FLASH          3    /* Example: Map MCU INTERNAL FLASH to physical drive 3 */

#ifdef USE_SPI_FLASH
#define FS_FLASH_SECTOR_SIZE        IFLASH_BLOCK_SIZE
#define FS_FLASH_SECTOR_COUNT       IFLASH_BLOCK_NUM
#define FS_FLASH_BLOCK_SIZE         1
#endif

#ifdef USE_INTERNAL_FLASH
#define FS_FLASH_SECTOR_SIZE        INTERNAL_FLASH_BLOCK_SIZE
#define FS_FLASH_SECTOR_COUNT       INTERNAL_FLASH_BLOCK_NUM
#define FS_FLASH_BLOCK_SIZE         1
#endif

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
    BYTE pdrv        /* Physical drive nmuber to identify the drive */
)
{
    DSTATUS stat = STA_NOINIT;
//    int result;

    switch (pdrv) {
    case DEV_RAM :
//        result = RAM_disk_status();

        // translate the reslut code here

        return stat;

    case DEV_MMC :
//        result = MMC_disk_status();

        // translate the reslut code here

        return stat;

    case DEV_SPI_FLASH :
        // translate the reslut code here
#ifdef USE_SPI_FLASH
        if(0xC84015U == spi_flash_read_id())
        {
            stat = RES_OK;
        } 
        else 
        {
            stat = RES_ERROR;
        }
#endif
        return stat;

    case DEV_INTERNAL_FLASH :
        // translate the reslut code here
#ifdef USE_INTERNAL_FLASH

        stat = RES_OK;

#endif
        return stat;
    }
    return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
    BYTE pdrv                /* Physical drive nmuber to identify the drive */
)
{
    DSTATUS stat = STA_NOINIT;
//    int result;

    switch (pdrv) {
    case DEV_RAM :
//        result = RAM_disk_initialize();

        // translate the reslut code here

        return stat;

    case DEV_MMC :
//        result = MMC_disk_initialize();

        // translate the reslut code here

        return stat;

    case DEV_SPI_FLASH :
        
        // translate the reslut code here
#ifdef USE_SPI_FLASH
        spi_flash_init();
        stat = RES_OK;
        // translate the reslut code here
#endif
        return stat;
        
    case DEV_INTERNAL_FLASH :
        // translate the reslut code here
#ifdef USE_INTERNAL_FLASH
        fmc_unlock();
        stat = RES_OK;
        // translate the reslut code here
#endif
        return stat;
    }
    return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
    BYTE pdrv,        /* Physical drive nmuber to identify the drive */
    BYTE *buff,        /* Data buffer to store read data */
    DWORD sector,    /* Start sector in LBA */
    UINT count        /* Number of sectors to read */
)
{
    DRESULT res = RES_PARERR;
//    int result;

    switch (pdrv) {
    case DEV_RAM :
        // translate the arguments here

//        result = RAM_disk_read(buff, sector, count);

        // translate the reslut code here

        return res;

    case DEV_MMC :
        // translate the arguments here

//        result = MMC_disk_read(buff, sector, count);

        // translate the reslut code here

        return res;

    case DEV_SPI_FLASH :
        // translate the arguments here
#ifdef USE_SPI_FLASH
        spi_flash_buffer_read(buff, sector*FS_FLASH_SECTOR_SIZE, count*FS_FLASH_SECTOR_SIZE);

        // translate the reslut code here
        res = RES_OK;
#endif
        return res;
        
    case DEV_INTERNAL_FLASH :
        // translate the arguments here
#ifdef USE_INTERNAL_FLASH
        {
            uint8_t *pSource = (uint8_t *)(sector*FS_FLASH_SECTOR_SIZE + FLASH_STROAGE_START_ADDRESS);

            while (count--) {
                for (uint16_t i = 0; i < FS_FLASH_SECTOR_SIZE; i++) {
                    *buff++ = *pSource++;
                }
            }
        }

        // translate the reslut code here
        res = RES_OK;
#endif
        return res;
    }

    return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
    BYTE pdrv,            /* Physical drive nmuber to identify the drive */
    const BYTE *buff,    /* Data to be written */
    DWORD sector,        /* Start sector in LBA */
    UINT count            /* Number of sectors to write */
)
{
    DRESULT res = RES_PARERR;
//    int result;

    switch (pdrv) {
    case DEV_RAM :
        // translate the arguments here

//        result = RAM_disk_write(buff, sector, count);

        // translate the reslut code here

        return res;

    case DEV_MMC :
        // translate the arguments here

//        result = MMC_disk_write(buff, sector, count);

        // translate the reslut code here

        return res;

    case DEV_SPI_FLASH :
        // translate the arguments here
#ifdef USE_SPI_FLASH
        spi_flash_sector_erase(sector*FS_FLASH_SECTOR_SIZE);
        spi_flash_buffer_write((uint8_t *)buff, sector*FS_FLASH_SECTOR_SIZE, count*FS_FLASH_SECTOR_SIZE);
        res = RES_OK;
        // translate the reslut code here
#endif
        return res;
        
    case DEV_INTERNAL_FLASH :
        // translate the arguments here
#ifdef USE_INTERNAL_FLASH
        {
            uint32_t i, page;
            uint32_t start_page = sector*FS_FLASH_SECTOR_SIZE + FLASH_STROAGE_START_ADDRESS;
            uint32_t *ptrs = (uint32_t *)buff;

            page = count;

            for(; page > 0; page--){
                fmc_page_erase(start_page);
                i = 0;
                do{
                    fmc_word_program(start_page, *ptrs++);
                    start_page += 4;
                }while(++i < 256);
            }
        }
        res = RES_OK;
        // translate the reslut code here
#endif
        return res;
    }

    return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
    BYTE pdrv,        /* Physical drive nmuber (0..) */
    BYTE cmd,        /* Control code */
    void *buff        /* Buffer to send/receive control data */
)
{
    DRESULT res = RES_PARERR;
//    int result;

    switch (pdrv) {
    case DEV_RAM :

        // Process of the command for the RAM drive

        return res;

    case DEV_MMC :

        // Process of the command for the MMC/SD card

        return res;

    case DEV_SPI_FLASH :
#ifdef USE_SPI_FLASH
        // Process of the command the USB drive
        switch (cmd) {
        case GET_SECTOR_COUNT:
            *(DWORD * )buff = FS_FLASH_SECTOR_COUNT;
            break;

        case GET_SECTOR_SIZE :
            *(WORD * )buff = FS_FLASH_SECTOR_SIZE;
            break;

        case GET_BLOCK_SIZE :
            *(DWORD * )buff = FS_FLASH_BLOCK_SIZE;
            break;
        }

        res = RES_OK;
#endif
        return res;

    case DEV_INTERNAL_FLASH :

        // Process of the command the USB drive
#ifdef USE_INTERNAL_FLASH
        switch (cmd) {
        case GET_SECTOR_COUNT:
            *(DWORD * )buff = FS_FLASH_SECTOR_COUNT;
            break;

        case GET_SECTOR_SIZE :
            *(WORD * )buff = FS_FLASH_SECTOR_SIZE;
            break;

        case GET_BLOCK_SIZE :
            *(DWORD * )buff = FS_FLASH_BLOCK_SIZE;
            break;
        }

        res = RES_OK;
#endif
        return res;
    }

    return RES_PARERR;
}


__weak DWORD get_fattime(void) {

    return    ((DWORD)(2019 - 1980) << 25)    /* Year 2019 */
            | ((DWORD)1 << 21)                /* Month 1 */
            | ((DWORD)1 << 16)                /* Mday 1 */
            | ((DWORD)0 << 11)                /* Hour 0 */
            | ((DWORD)0 << 5)                 /* Min 0 */
            | ((DWORD)0 >> 1);                /* Sec 0 */
}
