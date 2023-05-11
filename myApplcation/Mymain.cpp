/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : Mymain.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/27 
*********************************************************************
*********
*/
//
#include "Myapplication.h"
#include "IncludeALL.h"
#include "examples/get_started/lv_example_get_started.h"

#define SIZE 1024
#define LVGL_TICK 	5
LED led;
MyLCD myLcd;
MyFFT myFFT;
float *adc;
//���������������ֻ�������ֲ����� ��������ȫ�ַ�����Ҳ�����ַ
void Mymain()
{
    myLcd.MyLCDInit();
    lv_init();
    lv_port_disp_init();
    lv_example_get_started_1();

    for(;;)
    {
//        lv_tick_inc(LVGL_TICK);
       lv_timer_handler();
//        HAL_Delay(LVGL_TICK);
    }
}