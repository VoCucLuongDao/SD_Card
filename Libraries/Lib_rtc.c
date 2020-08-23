#include "Lib_rtc.h"

__IO uint32_t uwAsynchPrediv = 0;
__IO uint32_t uwSynchPrediv = 0;

void Config_RTC()
{
  /* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
  /* Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);
  /* LSE used as RTC source clock*/
  RCC_LSEConfig(RCC_LSE_ON);
  /* Wait till LSE is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
  /* ck_spre(1Hz) = RTCCLK(LSE) /(uwAsynchPrediv + 1)*(uwSynchPrediv + 1)*/
  uwSynchPrediv = 0xFF;
  uwAsynchPrediv = 0x7F;
  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);
  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();
  /* Write to the first RTC Backup Data Register */
 // RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
    
  RTC_InitTypeDef   RTC_InitStructure;
  RTC_TimeTypeDef   RTC_TimeStructure;
  RTC_DateTypeDef   RTC_DateStructure;
  
  RTC_InitStructure.RTC_AsynchPrediv = uwAsynchPrediv;
  RTC_InitStructure.RTC_SynchPrediv =  uwSynchPrediv;
  RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
  RTC_Init(&RTC_InitStructure);
  
  RTC_TimeStructure.RTC_Hours = 0x00;
  RTC_TimeStructure.RTC_Minutes = 0x00;
  RTC_TimeStructure.RTC_Seconds = 0x00;
  RTC_TimeStructInit(&RTC_TimeStructure);
  RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);  

  RTC_DateStructure.RTC_Date = 0x01;
  RTC_DateStructure.RTC_WeekDay = 0x01;
  RTC_DateStructure.RTC_Month = 0x01;  
  RTC_DateStructure.RTC_Year = 0x00; 
  RTC_DateStructInit(&RTC_DateStructure);
  RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure); 
  
  RTC_AlarmTypeDef RTC_AlarmStructure;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = 0x00;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = 0x17;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours = 0x17;
  RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay; 
  RTC_AlarmStructure.RTC_AlarmDateWeekDay= 0x00;
  RTC_AlarmStructure.RTC_AlarmDateWeekDaySel=RTC_AlarmDateWeekDaySel_Date;
  
  /* Configure the RTC Alarm A register */
  RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);
  
 // RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);

  
  /* RTC Alarm A Interrupt Configuration */
  /* EXTI configuration *******************************************************/
  EXTI_ClearITPendingBit(EXTI_Line17); 
  EXTI_InitTypeDef  EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  NVIC_InitTypeDef  NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable RTC Alarm A Interrupt */
  RTC_ITConfig(RTC_IT_ALRA, ENABLE);
  /* Enable the alarm */
  RTC_AlarmCmd(RTC_Alarm_A, ENABLE);
  
  RTC_ClearFlag(RTC_FLAG_ALRAF);
  Config_Led();
}

extern uint8_t showtime[50];
void TimeShow(void)
{
  RTC_TimeTypeDef   RTC_TimeStructure;
  /* Get the current Time */
  RTC_GetTime(RTC_Format_BIN, &RTC_TimeStructure);
  /* Display time Format : hh:mm:ss */
  sprintf((char*)showtime,"%0.2d:%0.2d:%0.2d",RTC_TimeStructure.RTC_Hours,
             RTC_TimeStructure.RTC_Minutes, RTC_TimeStructure.RTC_Seconds);
}

extern uint8_t showdate[50];
void DateShow(void)
{
  RTC_DateTypeDef   RTC_DateStructure;
  /* Get the current Date */
  RTC_GetDate(RTC_Format_BIN, &RTC_DateStructure);
  /* Display date Format : hh:mm:ss */
  sprintf((char*)showdate,"%0.2d:%0.2d:%0.2d:%0.2d",RTC_DateStructure.RTC_WeekDay,
          RTC_DateStructure.RTC_Date, RTC_DateStructure.RTC_Month, RTC_DateStructure.RTC_Year);
}

extern uint8_t showalarm[50];
void  AlarmShow(void)
{
  RTC_AlarmTypeDef RTC_AlarmStructure;
  /* Get the current Alarm */
  RTC_GetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStructure);
  sprintf((char*)showalarm,"%0.2d:%0.2d:%0.2d", RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours,
          RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes, RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds);
}

void RTC_Settime(uint8_t hours, uint8_t minutes){
  RTC_TimeTypeDef   RTC_TimeStructure;
  RTC_DateTypeDef   RTC_DateStructure;
  
  /* Set Time hh:mm:ss */
  RTC_TimeStructure.RTC_Hours   = hours;  
  RTC_TimeStructure.RTC_Minutes = minutes;
  RTC_TimeStructure.RTC_Seconds = 0x00;
  RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);

  /* Set Date Week/Date/Month/Year */
  RTC_DateStructure.RTC_WeekDay = 0x05;
  RTC_DateStructure.RTC_Date = 0x30;
  RTC_DateStructure.RTC_Month = 0x01;
  RTC_DateStructure.RTC_Year = 0x20;
  RTC_SetDate(RTC_Format_BCD, &RTC_DateStructure);
  
  RTC_AlarmTypeDef RTC_AlarmStructure;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = 0x00;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = 0x16;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours = 0x16;
  RTC_AlarmStructure.RTC_AlarmDateWeekDay= 0x01;
  RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);
  
    /* Write BkUp DR0 */
  RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);
}

uint8_t mode_wake_up=0;
void RTC_Alarm_IRQHandler(void)
{
  if(RTC_GetITStatus(RTC_IT_ALRA) != RESET)
  {
    mode_wake_up = 1;
    RTC_ClearITPendingBit(RTC_IT_ALRA);
    EXTI_ClearITPendingBit(EXTI_Line17);
  } 
}

void Config_Led()
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
  
  GPIO_InitTypeDef GPIO_Initstructure;
  GPIO_Initstructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Initstructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_Initstructure.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_Initstructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Initstructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC,&GPIO_Initstructure);
  GPIO_ResetBits(GPIOC,GPIO_Pin_10);
}


