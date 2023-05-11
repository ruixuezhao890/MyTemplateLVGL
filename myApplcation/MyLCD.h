/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : MyLCD.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/28 
*********************************************************************
*********
*/
//

#ifndef TEMPLATEDEVELOPMENT_MYLCD_H
#define TEMPLATEDEVELOPMENT_MYLCD_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "Myapplication.h"
//#include "IncludeALL.h"
/*______________________类的声明在这下面________________:*/
class MyLCD{
public:

    void MyLCDInit();
    void MyLCDDrawCoorDinat();
    void MyLDshowLable();
};
#ifdef __cplusplus
}
#endif
#endif //TEMPLATEDEVELOPMENT_MYLCD_H
