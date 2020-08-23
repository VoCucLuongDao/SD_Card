#ifndef _TIMER_CONFIG_H_
#define _TIMER_CONFIG_H_
#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

void TIM3_Init(void);
void TIM5_Init(void);
void TIM7_Init(void);
void TIM4_Init(void);
void TIM4_PWMCH1_Init();
#endif
