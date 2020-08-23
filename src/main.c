#include "main.h"
#include "stdio.h"
#include "string.h"
        FATFS           fs;
	FIL 		myFile;	
        FRESULT         res;
	char		file_name[] = "welcome2.txt";						// SD card input buffer
        uint8_t         str[1] = {0x03};
        char            name[50];
        DIR dir;
        UINT i;
void Select_Sd_Card();        

void main(){
          
        Select_Sd_Card();
        SD_Init();
        res = f_mount(0, &fs);
        if (f_open(&myFile,file_name, FA_READ)==FR_OK)
	{ 
               while(str[0]!= '\n'){
                    f_read(&myFile, str, 1, NULL);
                    printf("%c",str[0]);
               }
              f_close(&myFile);
	} else printf("\n\r- ERROR_OPEN");
      
    
  printf("\nCLOSE!");     
  while(1);
}


void Select_Sd_Card(){
          RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
 
          GPIO_InitTypeDef  GPIO_InitStructure;
          GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
          GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
          GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
          GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
          GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
          GPIO_Init(GPIOC, &GPIO_InitStructure);
           
          GPIO_ResetBits(GPIOC, GPIO_Pin_1);
}