/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2013        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control module to the FatFs module with a defined API.        */
/*-----------------------------------------------------------------------*/
/* Angepasst von UB                                                      */
/* V:1.0 / 26.02.2013                                                    */
/*-----------------------------------------------------------------------*/



#include "diskio.h"		// FatFs lower layer API
#include "stm32_ub_sdcard.h"	// UB: MMC/SDC control

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber (0..) */
)
{
        SD_Error res = SD_OK;
        res=SD_Init();
        return res;
}



/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber (0..) */
)
{
	  uint8_t state;
          state=SD_Detect();
	  return state;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..128) */
)
{
	SD_Error status = SD_OK;
        SD_ReadMultiBlocks(buff, sector << 9, 512, 1);
        status =  SD_WaitReadOperation();
        while(SD_GetStatus() != SD_TRANSFER_OK);
        if(!status) return RES_OK;
	return RES_ERROR;

}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	         /* Data to be written */
	DWORD sector,		         /* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..128) */
)
{
	SD_Error status = SD_OK;
        SD_WriteMultiBlocks((BYTE *)buff, sector << 9, 512, 1);
        status = SD_WaitWriteOperation();
        while(SD_GetStatus() != SD_TRANSFER_OK);     
        if(!status) return RES_OK;
	return RES_ERROR;

}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DWORD get_fattime (void)
{
	return	((2006UL-1980) << 25)	      // Year = 2006
			| (2UL << 21)	      // Month = Feb
			| (9UL << 16)	      // Day = 9
			| (22U << 11)	      // Hour = 22
			| (30U << 5)	      // Min = 30
			| (0U >> 1)	      // Sec = 0
			;
}


#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	 switch (cmd) {
            case GET_SECTOR_COUNT :    // Get number of sectors on the disk (DWORD)
              *(DWORD*)buff = 131072;  // 4*1024*32 = 131072
            break;
            case GET_SECTOR_SIZE :     // Get R/W sector size (WORD) 
              *(WORD*)buff = 512;
            break;
            case GET_BLOCK_SIZE :      // Get erase block size in unit of sector (DWORD)
              *(DWORD*)buff = 32;
            break;
          }
        return RES_OK;

}
#endif
