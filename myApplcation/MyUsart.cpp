/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : myUsart.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/27 
*********************************************************************
*********
*/
//

#include "MyUsart.h"

MyUsart::MyUsart()
{

}
MyUsart::MyUsart(UART_HandleTypeDef *huart)
{
    this->huart=huart;
}
MyUsart::MyUsart(uint16_t Enable)
{
    this->ReceiveInit();
}
void MyUsart::ReceiveInit()
{
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);//ʹ��idle�ж�
    HAL_UART_Receive_DMA(&huart1, re_Buff, RELENTH);
}
void MyUsart::Send(uint8_t * sendBuf)
{
    HAL_UART_Transmit(huart,sendBuf,sizeof(sendBuf)+1,50);
}

void MyUsart::SendString(uint8_t * stringBuf,uint16_t Length)
{
    HAL_UART_Transmit(huart,stringBuf,Length,50);
    HAL_UART_Transmit(huart,(uint8_t *)"\n",2,50);
}
void MyUsart::SendString(char* stringBuf,uint16_t Length)
{
    HAL_UART_Transmit(huart,(uint8_t *)stringBuf,Length,50);
    HAL_UART_Transmit(huart,(uint8_t *)"\n",2,50);
}

void MyUsart::SendOneInt(uint16_t IntBuf)
{
    char temp[RELENTH]={0};
    sprintf(temp,"%d\n",IntBuf);
    Send((uint8_t *)temp);
}
void MyUsart::SendInt(uint16_t* IntBuf,uint16_t Length)
{
    char temp[RELENTH]={0};
    for (int i = 0; i < Length; ++i) {
        sprintf(temp,"%d\n",IntBuf[i]);
        Send((uint8_t *)temp);
//        Send("\n",huart);
    }
}
void MyUsart::SendOneFloat(float FloatBuf)
{
    char temp[RELENTH]={0};
    sprintf(temp,"%f\n",FloatBuf);
    Send((uint8_t *)temp);
//    SendString("\n",huart);
}
void MyUsart::SendFloat(float* FloatBuf,uint16_t Length)
{
    char temp[RELENTH]={0};
    for (int i = 0; i < Length; ++i) {
        sprintf(temp,"%lf",FloatBuf[i]);
        Send((uint8_t *)temp);
        SendString((uint8_t *)"\n",2);
    }
}

//����"stm32f4xx_it.c�ļ���USART1_IRQHandler(void)��
void MyUsart::ReceiveDataCallBack(DMA_HandleTypeDef * hdma_usart1_rx)
{
    uint32_t tmp_flag = 0;
    uint32_t temp;
    tmp_flag =__HAL_UART_GET_FLAG(&huart1,UART_FLAG_IDLE); //��ȡIDLE��־λ
    if((tmp_flag != RESET))//idle��־����λ
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart1);//�����־λ
        temp = huart1.Instance->SR;  //���״̬�Ĵ���SR,��ȡSR�Ĵ�������ʵ�����SR�Ĵ����Ĺ���
        temp = huart1.Instance->DR; //��ȡ���ݼĴ����е�����
        HAL_UART_DMAStop(&huart1); //
        temp  = __HAL_DMA_GET_COUNTER(hdma_usart1_rx); // ��ȡDMA��δ��������ݸ�����NDTR�Ĵ�������������
        re_len = RELENTH - temp; //�ܼ�����ȥδ��������ݸ������õ��Ѿ����յ����ݸ���
        recv_end_flag = 1;	// ������ɱ�־λ��1
    }
}
void MyUsart::SendReceive()
{
    if(recv_end_flag ==1)
    {
        HAL_UART_DMAStop(huart);

        //��ӡ��������
        HAL_UART_Transmit(huart, re_Buff, re_len, 50);

        for(uint8_t i=0; i < re_len; i++)
        {
            re_Buff[i]=0;//����ջ���
        }
        re_len=0;//�������
        recv_end_flag=0;//������ս�����־λ
    }

    HAL_UART_Receive_DMA(&huart1, re_Buff, RELENTH);
}
MyUsart::~MyUsart() {

}
