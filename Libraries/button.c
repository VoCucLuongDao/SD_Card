#include "button.h"

void Button_Cf(void)
{
  EXTI_InitTypeDef   EXTI_InitStruct_PA0;
  EXTI_InitTypeDef   EXTI_InitStruct_PB7;
  GPIO_InitTypeDef   GPIO_InitStruct;
  NVIC_InitTypeDef   NVIC_InitStruct_PA0;
  NVIC_InitTypeDef   NVIC_InitStruct_PB7;
  
          //enable GPIOA, GPIOB clock
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
          //enable syscfg clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
          //config pin PA0, PB7 as input 
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_Init(GPIOB, &GPIO_InitStruct);
  
         //connect EXTI line 0 to pin PA0
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
		 //connect EXTI line 7 to pin PB7
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource7);
  
        //config EXIT line 0
  EXTI_InitStruct_PA0.EXTI_Line = EXTI_Line0;
  EXTI_InitStruct_PA0.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct_PA0.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStruct_PA0.EXTI_LineCmd = ENABLE;
  
  EXTI_Init(&EXTI_InitStruct_PA0);
  
       /* Config EXTI line 7 */
  EXTI_InitStruct_PB7.EXTI_Line = EXTI_Line7;
  EXTI_InitStruct_PB7.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct_PB7.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStruct_PB7.EXTI_LineCmd = ENABLE;
  
  EXTI_Init(&EXTI_InitStruct_PB7);
      
        //enable and set EXTI Line 0 Interrupt to the lowest priority
  NVIC_InitStruct_PA0.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStruct_PA0.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStruct_PA0.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStruct_PA0.NVIC_IRQChannelCmd = ENABLE; 
  
  NVIC_Init(&NVIC_InitStruct_PA0);
  
   /*PB7 is connect to EXTI Line 7, which has EXTI9_5_TRQn*/
  NVIC_InitStruct_PB7.NVIC_IRQChannel = EXTI9_5_IRQn;
  NVIC_InitStruct_PB7.NVIC_IRQChannelPreemptionPriority = 0x02;
  NVIC_InitStruct_PB7.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStruct_PB7.NVIC_IRQChannelCmd = ENABLE;
  
  NVIC_Init(&NVIC_InitStruct_PB7);
   
}
int value_minutes;
void EXTI0_IRQHandler(void)
{
   RTC_TimeTypeDef   RTC_TimeStructure;
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    RTC_GetTime(RTC_Format_BCD, &RTC_TimeStructure);
    value_minutes=(RTC_TimeStructure.RTC_Minutes&0x0f)              //chuyen ma BCD ve DEC(dang HEX) sau do cong 1;
                   +(RTC_TimeStructure.RTC_Minutes>>4&0x0f)*16+1; // vd BCD 0x20 ->32+1=33 -> 0x21
    RTC_Settime(0x21,value_minutes);                                //setup phut
    // Clear the EXTI line 0 pending bit
    int i=8400000;
    while(i--); 
    EXTI_ClearITPendingBit(EXTI_Line0);
  
  }
}
void EXTI9_5_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line7) != RESET)
  {
    
    EXTI_ClearITPendingBit(EXTI_Line7);
  }
}
