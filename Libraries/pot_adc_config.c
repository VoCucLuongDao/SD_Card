#include "adc_config.h"

void ADC_init()
{
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
     GPIO_InitTypeDef GPIO_InitStruct;
     ADC_InitTypeDef  ADC_InitStruct;
     ADC_CommonInitTypeDef ADC_CommonInitStruct;
     
     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOA,&GPIO_InitStruct);

     ADC_InitStruct.ADC_ContinuousConvMode =  ENABLE;
     ADC_InitStruct.ADC_ScanConvMode = DISABLE;
     ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
     ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
     ADC_InitStruct.ADC_Resolution=ADC_Resolution_12b;
     ADC_InitStruct.ADC_NbrOfConversion = 1;
     ADC_Init(ADC1, &ADC_InitStruct);
     
     ADC_CommonInitStruct.ADC_Mode=ADC_Mode_Independent;
     ADC_CommonInitStruct.ADC_Prescaler=ADC_Prescaler_Div2;
     ADC_CommonInit(& ADC_CommonInitStruct);
     
     NVIC_InitTypeDef NVIC_InitStructure;
     NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);

     ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
     ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
     
     ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_480Cycles);
     ADC_Cmd(ADC1, ENABLE);
     ADC_SoftwareStartConv(ADC1);
}

uint16_t ReadADC1()
{
    ADC_ITConfig(ADC1, ADC_IT_EOC, DISABLE);//tat
    if(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != RESET){ 
       return (uint16_t) ADC_GetConversionValue(ADC1);
        }
}
