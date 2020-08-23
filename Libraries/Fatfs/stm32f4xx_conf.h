
/* Define to prevent recursive inclusion */
#ifndef __STM32F4xx_CONF_H
#define __STM32F4xx_CONF_H

// Add missing defines for Peripheral Standard Lib
#undef  HSE_VALUE
#define HSE_VALUE    ((uint32_t)8000000) 				/*!< Value of the External oscillator in Hz */
#define HSE_STARTUP_TIMEOUT    ((uint16_t)0x0500)   	/*!< Time out for HSE start up */
#define HSI_VALUE    ((uint32_t)16000000) 				/*!< Value of the Internal oscillator in Hz*/

// Add includes
#include "stm32f4xx_dma.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_sdio.h"
#include "misc.h"

// Neutralize assertion
#define assert_param(expr) ((void)0)


#endif /* __STM32F4xx_CONF_H */
