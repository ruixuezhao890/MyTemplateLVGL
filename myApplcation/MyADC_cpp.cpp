/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MyADC_cpp.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/27 
*********************************************************************
*********
*/
//


#include "MyADC_cpp.h"

MyADC::MyADC( uint16_t * adcNum,uint16_t Size,TIM_HandleTypeDef *htim, ADC_HandleTypeDef *hadc) {
    this->myADCInit(htim);
    this->hadc=hadc;
    ADCStorageBuff=adcNum;
    ADCStorageBuffSize=Size;
    this->myADCCollectData();


}
void MyADC::myADCInit(TIM_HandleTypeDef *htim)
{
    HAL_TIM_Base_Start(htim);
}

void MyADC::myADCCollectData()
{

    HAL_ADC_Start_DMA(hadc,(uint32_t *)ADCStorageBuff,ADCStorageBuffSize);

}




//或者放在发送数据之后在调用它前面加上100ms的延时
void MyADC::myADCCompareTheSize()
{

    for (int i = 0; i < ADCStorageBuffSize; ++i) {
        if (MaxValue < ADCStorageBuff[i]) {
            MaxValue = ADCStorageBuff[i];
        }
    }
    for (int i = 0; i < ADCStorageBuffSize; ++i){
        if (MinValue>ADCStorageBuff[i])
        {
            MinValue=ADCStorageBuff[i];
        }
    }
    float vmax=MaxValue*3.3/4096;

    float vmin=MinValue*3.3/4096;
    float vpp=(MaxValue-MinValue)*3.3/4096;
    lcd_show_float(60, 88, vpp,16,0,RED);//VPP峰峰值
    lcd_show_float(60, 48, vmax,  16, 0, RED);//最大值
    lcd_show_float(60, 68, vmin,  16, 0, RED);//最小值


}

void MyADC::myADCShowWaveForm() {

    uint16_t past_vol1 = 0, pre_vol1 = 0;
    uint16_t past_vol = 0, pre_vol = 0;
    for (uint16_t x = 0; x < 799; x++)
    {
        pre_vol = ADCStorageBuff[x] * (3.3 / 4096) * 60;
        //pre_vol1 = adcBuff2[x] * (3.3 / 4096) * 60;
        lcd_draw_line(x, 250, x, 480, WHITE);//刷新背景
        lcd_draw_line(x, past_vol + 260, x , pre_vol + 260,  RED);
        //lcd_draw_bline(x, past_vol1 + 280, x + 1, pre_vol1 + 280, 1, RED);
        //past_vol1 = pre_vol1;
        past_vol = pre_vol;
    }
}
MyADC::~MyADC()
{

}