/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MyLCD.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/28 
*********************************************************************
*********
*/
//

#include "MyLCD.h"
#include "Myapplication.h"
#include "MyUsart.h"


void MyLCD::MyLCDInit() {

    lcd_init();
    lcd_display_dir(0);

}
void MyLCD::MyLCDDrawCoorDinat() {
    lcd_draw_line(287, 0, 287, 230, RED);
    lcd_draw_line(287, 230, 800, 230, RED);
//    lcd_draw_line(5, 470, 800, 470, RED);
//    lcd_draw_line(5, 460, 5, 280, RED);

}
void MyLCD::MyLDshowLable() {

    lcd_show_string(5, 8, 200, 16, 16, "My_project:", GREEN);
    lcd_show_string(5, 28, 200, 16, 16, "div/(mv)", GRAY);
    lcd_show_string(5, 48, 200, 16, 16, "max(mv):", GRAY);
    lcd_show_string(5, 68, 200, 16, 16, "min(mv):", GRAY);
    lcd_show_string(5, 88, 200, 16, 16, "vpp(mv):", GRAY);
    lcd_show_string(5, 108, 200, 16, 16, "f(Hz):", GRAY);
    lcd_show_string(5, 128, 200, 16, 16, "WAVE:", GRAY);  //²ÉÑùÂÊ
    lcd_show_string(5, 148, 200, 16, 16, "Hz:", GRAY);
    lcd_show_string(5,168,200,16,16,"Pha",GRAY);
    lcd_show_string(100, 13, 200, 16, 16, "IN:PA6", BRRED);
    //lcd_show_xnum(5, 28, 12345, 5, 16, 1, BLUE);



}