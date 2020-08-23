#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "delay.h"
#include "Lib_rtc.h"
#include "stdlib.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"

void Button_Cf(void);
void EXTI0_IRQHandler(void);
void EXTI9_5_IRQHandler(void);

#endif