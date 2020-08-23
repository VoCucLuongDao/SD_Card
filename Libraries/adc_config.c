#include "adc_config.h"
#include "main.h"

void ADC_init()
{
     TIM3_Init();
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
     GPIO_InitTypeDef GPIO_InitStruct;
     ADC_InitTypeDef  ADC_InitStruct;
     
     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOA,&GPIO_InitStruct);

     ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
     ADC_InitStruct.ADC_ScanConvMode = DISABLE;
     ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;
     ADC_InitStruct.ADC_ExternalTrigConvEdge =ADC_ExternalTrigConvEdge_Rising;
     ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
     ADC_InitStruct.ADC_Resolution=ADC_Resolution_12b;
     ADC_InitStruct.ADC_NbrOfConversion = 1;
     ADC_Init(ADC1, &ADC_InitStruct);
           
     NVIC_InitTypeDef NVIC_InitStructure;
     NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);

     ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
     
     ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_15Cycles);
     ADC_Cmd(ADC1, ENABLE);
     ADC_SoftwareStartConv(ADC1);
}