/**
*********************************************************************
*********
* @project_name :templateDevelopment
* @file : seriall_Port.c
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/4/26 
*********************************************************************
*********
*/
//

#include "seriall_Port.h"
 uint8_t    re_len=0;
 uint8_t    recv_end_flag=0;
uint8_t     re_Buff[200];
//��ʹ�ó�ʼ��
void ReceiveInit()
{
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);//ʹ��idle�ж�
    HAL_UART_Receive_DMA(&huart1, re_Buff, RELENTH);
}

void SendReceive(UART_HandleTypeDef *huart)
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
void Send(uint8_t * sendBuf,UART_HandleTypeDef *huart)
{

    HAL_UART_Transmit(huart,sendBuf,sizeof(sendBuf)+1,50);

}

void SendString(uint8_t * stringBuf,uint16_t Length,UART_HandleTypeDef *huart)
{

    HAL_UART_Transmit(huart,stringBuf,Length,50);
    HAL_UART_Transmit(huart,"\n",sizeof("\n"),50);
}

void SendOneInt(uint16_t IntBuf,UART_HandleTypeDef *huart)
{
    char temp[RELENTH]={0};
    sprintf(temp,"%d\n",IntBuf);
    Send((uint8_t *)temp,huart);
//    Send("\n",huart);
}
void SendInt(uint16_t* IntBuf,uint16_t Length,UART_HandleTypeDef *huart)
{
    char temp[RELENTH]={0};
    for (int i = 0; i < Length; ++i) {
        sprintf(temp,"%d\n",IntBuf[i]);
        Send((uint8_t *)temp,huart);
//        Send("\n",huart);
    }


}
void SendOneFloat(float FloatBuf,UART_HandleTypeDef *huart)
{
    char temp[RELENTH]={0};
    sprintf(temp,"%f\n",FloatBuf);
    Send(temp,huart);
//    SendString("\n",huart);
}
void SendFloat(float * FloatBuf,uint16_t Length,UART_HandleTypeDef *huart)
{
    char temp[RELENTH]={0};
    for (int i = 0; i < Length; ++i) {
        sprintf(temp,"%f",FloatBuf[i]);
        Send(temp,huart);
        SendString("\n",2,huart);
    }
}
//����"stm32f4xx_it.c�ļ���USART1_IRQHandler(void)��
void ReceiveDataCallBack(DMA_HandleTypeDef*  hdma_usart1_rx)
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

