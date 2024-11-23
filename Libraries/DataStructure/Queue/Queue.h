#ifndef __ROBO_LIB_QUEUE_H__
#define __ROBO_LIB_QUEUE_H__

namespace robo_lib
{
template<typename T>
struct QUEUE_HandleTypeDef
{
  unsigned int head;                      //队列头指针
  unsigned int tail;                      //队列尾指针
  unsigned int buffer_length;             //队列缓存长度（初始化时赋值）
  T * buffer;		              //队列缓存数组（初始化时赋值）
};

typedef enum
{
  QUEUE_OK       = 0x00U,                 //队列OK
  QUEUE_ERROR    = 0x01U,                 //队列错误
  QUEUE_BUSY     = 0x02U,                 //队列忙
  QUEUE_TIMEOUT  = 0x03U,                 //队列超时
  QUEUE_OVERLOAD = 0x04U,                 //队列已满
  QUEUE_VOID     = 0x05U                  //队列已空
} QUEUE_StatusTypeDef;

template<typename T>
class Queue
{
public:

//==============================================================================
//  函数名称：Queue_Init
//  函数功能：初始化（创建）队列，每个队列必须先执行该函数才能使用。
//  函数参数：hqueue           队列变量指针
//  函数参数：buffer           队列缓存区地址
//  函数参数：len              队列缓存区长度
//  函数返回：void
//==============================================================================
  void Queue_Init(QUEUE_HandleTypeDef<T> * hqueue, T * buffer, unsigned int len)
  {
    hqueue->buffer = buffer;
    hqueue->buffer_length = len;
    Queue_Clear(hqueue);
  }

//==============================================================================
//  函数名称：Queue_Clear
//  函数功能：清空队列
//  函数参数：hqueue           队列变量指针
//  函数返回：void
//==============================================================================
  void Queue_Clear(QUEUE_HandleTypeDef<T> * hqueue)
  {
    hqueue->head = 0;
    hqueue->tail = 0;
  }

//==============================================================================
//  函数名称：Queue_Count
//  函数功能：获取队列内数据的个数
//  函数参数：hqueue           队列变量指针
//  函数返回：队列内数据的个数
//==============================================================================
  unsigned int Queue_Count(QUEUE_HandleTypeDef<T> * hqueue)
  {
    if(hqueue->head <= hqueue->tail)
    {
      return (unsigned int)(hqueue->tail - hqueue->head);
    }
    else
    {
      return (unsigned int)(hqueue->buffer_length + hqueue->tail - hqueue->head);
    }
  }

//==============================================================================
//  函数名称：Queue_Push
//  函数功能：压入数据到队列中
//  函数参数：hqueue           队列变量指针
//  函数参数：data             待压入队列的数据
//  函数返回：队列状态
//==============================================================================
  QUEUE_StatusTypeDef Queue_Push(QUEUE_HandleTypeDef<T> * hqueue, T data)
  {
    unsigned int tmp = (hqueue->tail + 1) % hqueue->buffer_length;

    if(tmp == hqueue->head)
    {
      return QUEUE_OVERLOAD;
    }
    else
    {
      hqueue->buffer[hqueue->tail] = data;
      hqueue->tail = tmp;
      return QUEUE_OK;
    }
  }

//==============================================================================
//  函数名称：Queue_Push_Array
//  函数功能：压入一组数据到队列中
//  函数参数：hqueue           队列变量指针
//  函数参数：pdatas           待压入队列的数组地址
//  函数参数：len              待压入队列的数组长度
//  函数返回：成功压入队列数据的数量
//==============================================================================
  unsigned int Queue_Push_Array(QUEUE_HandleTypeDef<T> * hqueue, T * pdatas, unsigned int len)
  {
    unsigned int i;
    for(i = 0; i < len; i++)
    {
      if(Queue_Push(hqueue, pdatas[i]) == QUEUE_OVERLOAD)
      {
        break;
      }
    }
    return i;
  }


//==============================================================================
//  函数名称：Queue_Pop
//  函数功能：从队列中弹出数据
//  函数参数：hqueue           队列变量指针
//  函数参数：pdata            待弹出队列的数据缓存地址
//  函数返回：队列状态
//==============================================================================
  QUEUE_StatusTypeDef Queue_Pop(QUEUE_HandleTypeDef<T> * hqueue, T * pdata)
  {
    if(hqueue->head == hqueue->tail)
    {
      return QUEUE_VOID;
    }
    else
    {
      *pdata = hqueue->buffer[hqueue->head];
      hqueue->head = (hqueue->head + 1) % hqueue->buffer_length;
      return QUEUE_OK;
    }
  }

//==============================================================================
//  函数名称：Queue_Pop_Array
//  函数功能：从队列中弹出一组数据
//  函数参数：hqueue           队列变量指针
//  函数参数：pdatas           待弹出队列的数据缓存地址
//  函数参数：len              待弹出队列的数据的最大长度
//  函数返回：实际弹出数据的数量
//==============================================================================
  unsigned int Queue_Pop_Array(QUEUE_HandleTypeDef<T> * hqueue, T * pdatas, unsigned int len)
  {
    unsigned int i;
    for(i = 0; i < len; i++)
    {
      if(Queue_Pop(hqueue, &pdatas[i]) == QUEUE_VOID)
      {
        break;
      }
    }
    return i;
  }


//==============================================================================
//  函数名称：Queue_Peek
//  函数功能：从队列头部返回数据（不删除队列中的数据）
//  函数参数：hqueue           队列变量指针
//  函数参数：pdata            待返回队列的数据缓存地址
//  函数返回：队列状态
//==============================================================================
  QUEUE_StatusTypeDef Queue_Peek(QUEUE_HandleTypeDef<T> * hqueue, T * pdata)
  {
    if(hqueue->head == hqueue->tail)
    {
      return QUEUE_VOID;
    }
    else
    {
      *pdata = hqueue->buffer[hqueue->head];
      return QUEUE_OK;
    }
  }

//==============================================================================
//  函数名称：Queue_Peek_Array
//  函数功能：从队列中返回一组数据（不删除队列中的数据）
//  函数参数：hqueue           队列变量指针
//  函数参数：pdatas           待返回队列的数据缓存地址
//  函数参数：len              待返回队列的数据的最大长度
//  函数返回：实际返回数据的数量
//==============================================================================
  unsigned int Queue_Peek_Array(QUEUE_HandleTypeDef<T> * hqueue, T * pdatas, unsigned int len)
  {
    unsigned int i;
    if(hqueue->head == hqueue->tail)
    {
      return 0;
    }
    if(Queue_Count(hqueue) < len)
    {
      len = Queue_Count(hqueue);
    }
    for(i = 0; i < len; i++)
    {
      pdatas[i] = hqueue->buffer[(hqueue->head + i) % hqueue->buffer_length];
    }
    return len;
  }
};
}
#endif

