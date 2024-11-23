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


#include "Libraries/RCProtocol/RCProtocol.h"
#include "Libraries/RCProtocol/RCProtocol_Backend.h"
#include "Libraries/RCProtocol/RCProtocol_CAN.h"
#include "Libraries/RCProtocol/RCProtocol_IBUS.h"
#include "Libraries/RCProtocol/RCProtocol_DBUS.h"
#include "Libraries/RCProtocol/RCProtocol_WBUS.h"
#include "stdarg.h"

extern UART_HandleTypeDef huart3;
extern DMA_HandleTypeDef hdma_usart3_rx;

namespace robo_lib
{

//uint8_t sbus_rx_buf[2][SBUS_RX_BUF_NUM];

/***********************************************************************
** 函 数 名： RCProtocol::init
** 函数说明： huart3与DMA初始化，实例化后台，并添加
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void RCProtocol::init()
{
    #ifdef USE_IBUS
    addBackend(new RCProtocol_IBUS(*this));
    #endif
    #ifdef USE_DBUS
    addBackend(new RCProtocol_DBUS(*this));
    #endif
    #ifdef USE_WBUS
    addBackend(new RCProtocol_WBUS(*this));
    #endif
    backend->init();//初始化DBUS(空)
    //enable the DMA transfer for the receiver request
    //使能DMA串口接收
    SET_BIT(huart3.Instance->CR3, USART_CR3_DMAR);

    //enalbe idle interrupt
    //使能空闲中断
    __HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);

    //disable DMA
    //失效DMA
    __HAL_DMA_DISABLE(&hdma_usart3_rx);

    while(hdma_usart3_rx.Instance->CR & DMA_SxCR_EN)
    {
        __HAL_DMA_DISABLE(&hdma_usart3_rx);
    }

    hdma_usart3_rx.Instance->PAR = (uint32_t) & (USART3->DR);
    //memory buffer 1

    //memory buffer 2

    //内存缓冲区1
    hdma_usart3_rx.Instance->M0AR = (uint32_t)(sbus_rx_buf[0]);
    //内存缓冲区2
    hdma_usart3_rx.Instance->M1AR = (uint32_t)(sbus_rx_buf[1]);
    //data length
    //数据长度
    hdma_usart3_rx.Instance->NDTR = SBUS_RX_BUF_NUM;
    //enable double memory buffer
    //使能双缓冲区
    SET_BIT(hdma_usart3_rx.Instance->CR, DMA_SxCR_DBM);

    //enable DMA
    //使能DMA
    __HAL_DMA_ENABLE(&hdma_usart3_rx);


}

void RCProtocol::init(CanDevice &_can_device)
{
    addBackend(new RCProtocol_CAN(*this, _can_device));
    backend->init();
}

/***********************************************************************
** 函 数 名： RCProtocol::processByte
** 函数说明： 调用后台的processByte函数
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void RCProtocol::processByte(volatile const uint8_t *buf)
{
    if(backend != NULL)
    {
        backend->processByte(buf);
    }
}

/***********************************************************************
** 函 数 名： RCProtocol::addBackend
** 函数说明： 在前台添加新后台
**---------------------------------------------------------------------
** 输入参数： 后台类指针backend0
** 返回参数： 无
***********************************************************************/
void RCProtocol::addBackend(RCProtocol_Backend *backend0)
{
    backend = backend0;
}

/***********************************************************************
** 函 数 名： RCProtocol::uninit
** 函数说明： 在前台调用后台的去初始化
**---------------------------------------------------------------------
** 输入参数： 无
** 返回参数： 无
***********************************************************************/
void RCProtocol::uninit(void)
{
    backend->uninit();
}
}