#include "timer_config.h"
#include "main.h"

extern uint16_t period_config;
void TIM7_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_InitStructure; 
    TIM_InitStructure.TIM_Prescaler =1000-1;
    TIM_InitStructure.TIM_Period =42-1;        
    TIM_InitStructure.TIM_ClockDivision = 0;
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM7, &TIM_InitStructure);
    TIM_SelectOutputTrigger (TIM7, TIM_TRGOSource_Update);
    TIM_ITConfig(TIM7,TIM_IT_Update, ENABLE);
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM7_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct); 
    TIM_Cmd(TIM7, ENABLE);   
   
}

void TIM5_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    TIM_InitStructure.TIM_Period =period_config-1;        //f=82k*128
    TIM_InitStructure.TIM_Prescaler =1-1;
    TIM_InitStructure.TIM_ClockDivision = 0;
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5, &TIM_InitStructure);
    TIM_SelectOutputTrigger (TIM5, TIM_TRGOSource_Update); 
   
    TIM_ITConfig(TIM5,TIM_IT_Update, ENABLE);
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM5_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct); 
    
    TIM_Cmd(TIM5, ENABLE); 
}

void TIM3_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    TIM_InitStructure.TIM_Period =10-1;        //f=82k*128
    TIM_InitStructure.TIM_Prescaler =5-1;
    TIM_InitStructure.TIM_ClockDivision = 0;
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_InitStructure);
    TIM_SelectOutputTrigger (TIM3, TIM_TRGOSource_Update); 
    TIM_Cmd(TIM3, ENABLE);   
}

void TIM4_Init() 
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Period =  52-1; 
    TIM_TimeBaseInitStruct.TIM_Prescaler =8-1;       
    TIM_TimeBaseInitStruct.TIM_CounterMode =TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);  
    TIM_SelectOutputTrigger (TIM4, TIM_TRGOSource_Update); 

    TIM_Cmd(TIM4,ENABLE);  
}


void TIM4_PWMCH1_Init()
{
      TIM4_Init() ;
      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
      GPIO_InitTypeDef GPIO_InitStructure;
      GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_12 );
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
      GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
      GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
      GPIO_Init(GPIOD, &GPIO_InitStructure);
      GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
      
      TIM_OCInitTypeDef TIM_OCInitStruct;
      TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
      TIM_OCInitStruct.TIM_Pulse=26-1;
      TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
      TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Set;
      TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
     
      TIM_OC1Init(TIM4, &TIM_OCInitStruct);
      TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
      TIM_CtrlPWMOutputs(TIM4, ENABLE);
}