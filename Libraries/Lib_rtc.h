#ifndef _LIB_RTC_H_
#define _LIB_RTC_H_
#include "stm32f4xx_rtc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_exti.h"
#include "LCD_txt.h"
#include "stdio.h"
void Config_RTC();
void TimeShow(void);
void DateShow(void);
void AlarmShow();
void Config_Led();
void RTC_Settime(uint8_t hours, uint8_t minutes);

#endif