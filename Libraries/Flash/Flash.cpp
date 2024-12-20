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

#include "Libraries/Flash/Flash.h"
namespace robo_lib
{
/***********************************************************************
** 函 数 名： flash_ger_sector()
** 函数说明： 获取flash地址所在的扇区号
**---------------------------------------------------------------------
** 输入参数： flash地址
** 返回参数： 无
***********************************************************************/
uint32_t flash_getSector(uint32_t address)
{
  if(address < ADDR_FLASH_SECTOR_1)
  {
    return FLASH_SECTOR_0;
  }
  else if(address < ADDR_FLASH_SECTOR_2)
  {
    return FLASH_SECTOR_1;
  }
  else if(address < ADDR_FLASH_SECTOR_3)
  {
    return FLASH_SECTOR_2;
  }
  else if(address < ADDR_FLASH_SECTOR_4)
  {
    return FLASH_SECTOR_3;
  }
  else if(address < ADDR_FLASH_SECTOR_5)
  {
    return FLASH_SECTOR_4;
  }
  else if(address < ADDR_FLASH_SECTOR_6)
  {
    return FLASH_SECTOR_5;
  }
  else if(address < ADDR_FLASH_SECTOR_7)
  {
    return FLASH_SECTOR_6;
  }
  else if(address < ADDR_FLASH_SECTOR_8)
  {
    return FLASH_SECTOR_7;
  }
  else if(address < ADDR_FLASH_SECTOR_9)
  {
    return FLASH_SECTOR_8;
  }
  else if(address < ADDR_FLASH_SECTOR_10)
  {
    return FLASH_SECTOR_9;
  }
  else if(address < ADDR_FLASH_SECTOR_11)
  {
    return FLASH_SECTOR_10;
  }
  else
  {
    return FLASH_SECTOR_11;
  }
}

/***********************************************************************
** 函 数 名： flash_erase_address()
** 函数说明： 擦除flash
**---------------------------------------------------------------------
** 输入参数： flash起始地址,擦除扇区数
** 返回参数： 无
***********************************************************************/
void flash_eraseAddress(uint32_t address, uint16_t num)
{
  FLASH_EraseInitTypeDef flash_erase;
  uint32_t error;

  flash_erase.TypeErase = FLASH_TYPEERASE_SECTORS;
  flash_erase.Sector = flash_getSector(address);
  flash_erase.NbSectors = num;
  flash_erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;

  HAL_FLASH_Unlock();
  HAL_FLASHEx_Erase(&flash_erase, &error);
  HAL_FLASH_Lock();
}

/***********************************************************************
** 函 数 名： flash_write_address()
** 函数说明： 往flash写数据
**---------------------------------------------------------------------
** 输入参数： 写入flah的起始地址,写入数据的源地址,写入32位数据的个数
** 返回参数： 无
***********************************************************************/
void flash_writeAddress(uint32_t address, uint32_t *buf, uint16_t num)
{
  uint16_t i;

  HAL_FLASH_Unlock();

  for(i = 0; i < num; i++)
  {
    HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, address + 4 * i, buf[i]);
  }

  HAL_FLASH_Lock();
}

/***********************************************************************
** 函 数 名： flash_read_address()
** 函数说明： 从flash读数据
**---------------------------------------------------------------------
** 输入参数： 读取flash的起始地址,存入的目标地址,读取32位数据的个数
** 返回参数： 无
***********************************************************************/
void flash_readAddress(uint32_t address, uint32_t *buf, uint16_t num)
{
  memcpy(buf, (void*)address, num * 4);
}
}