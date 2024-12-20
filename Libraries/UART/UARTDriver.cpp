/**
  ******************************************************************************
  * @file    AHRS.cpp
  * @version 2.0
  * @author  DUT-Lingbug Embedded Group
  * @brief   姿态解算AHRS基类
  *
  ******************************************************************************
  * @attention
  *
  * Copyright 2023 DUT-Lingbug.
  * All rights reserved.
  *
  ******************************************************************************
  */
#include "Libraries/UART/UARTDriver.h"
namespace robo_lib
{
/***********************************************************************
** 函 数 名： USART1_DMA_Tx_Init()
** 函数说明： USART1
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void USART1_DMA_Tx_Init(void)
{
  // 使能发送
  SET_BIT(huart1.Instance->CR3, USART_CR3_DMAT);
}

/***********************************************************************
** 函 数 名： USART1_DMA_Send_String()
** 函数说明： USART1 DMA发送字符串（注意内存覆盖问题）
**---------------------------------------------------------------------
** 输入参数： 要发送的字符串内容
** 返回参数： 无
***********************************************************************/
void USART1_DMA_Send_String(const uint8_t * str)
{
  if(HAL_DMA_GetState(&hdma_usart1_tx) == HAL_DMA_STATE_READY)
  {
    __HAL_DMA_DISABLE(&hdma_usart1_tx);
    HAL_UART_Transmit_DMA(&huart1, (uint8_t *)str, strlen((char*)str));
  }
}

/***********************************************************************
** 函 数 名： USART1_DMA_Send_Char()
** 函数说明： USART1发送字符
**---------------------------------------------------------------------
** 输入参数： 要发送的字符（注意内存覆盖问题）
** 返回参数： 无
***********************************************************************/
void USART1_DMA_Send_Char(uint8_t * c)
{
  HAL_UART_Transmit_DMA(&huart1, (uint8_t *)c, 1);
}

/***********************************************************************
** 函 数 名： USART1_DMA_Debug_Printf()
** 函数说明： 类似printf函数
**---------------------------------------------------------------------
** 输入参数： *format
** 返回参数： 无
***********************************************************************/
void USART1_DMA_Debug_Printf(const char *format, ...)
{
#ifdef DEBUG_MODE
  static uint8_t buf[256] = {0};
  static va_list ap;
  va_start(ap, format);

  vsprintf((char*)buf, format, ap);
  va_end(ap);
  USART1_DMA_Send_String(buf);

#endif
}

/***********************************************************************
** 函 数 名： USART1_DMA_Debug_Plot()
** 函数说明： 绘制
**---------------------------------------------------------------------
** 输入参数： 数据名称，数据值
** 返回参数： 无
***********************************************************************/
void USART1_DMA_Debug_Plot(uint8_t name, int16_t value)
{
  char buf[20];
  sprintf(buf, "Line%d=%d,", name, value);
  USART1_DMA_Debug_Printf(buf);
}
}