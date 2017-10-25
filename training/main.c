//
//  main.c
//  training
//
//  Created by zhaoli on 2017/8/23.
//  Copyright © 2017年 zhaoli. All rights reserved.
//
#if 1

#include "app_cfg.h"
#include <stdarg.h>
#include "test4B.h"
//#include "test4B_echo.h"
#include "t_pool.h"
#include "byte_queue.h"
#define BYTE_QUE_BUF_LEN        4
static uint8_t s_tBuf[BYTE_QUE_BUF_LEN];
static byte_queue_t *s_ptByteQueue = NULL;


 
int main(int argc, const char * argv[])
{
    uint8_t dataBuf = 1;
    uint8_t result = 1;
 
    init_pool_cfg();
 
    init_test4B();
 
    s_ptByteQueue = new_byte_queue(s_tBuf, BYTE_QUE_BUF_LEN);   
    if (NULL == s_ptByteQueue) {
        return 0;
    }
 
    dataBuf += 2;
    s_ptByteQueue->base__queue_t.base__i_queue_t.Enqueue(&(s_ptByteQueue->base__queue_t), &dataBuf);
    dataBuf += 2;
    s_ptByteQueue->base__queue_t.base__i_queue_t.Enqueue(&(s_ptByteQueue->base__queue_t), &dataBuf);
    s_ptByteQueue->base__queue_t.base__i_queue_t.Dequeue(&(s_ptByteQueue->base__queue_t), &result);
    printf("%d\r\n",result);
    s_ptByteQueue->base__queue_t.base__i_queue_t.Dequeue(&(s_ptByteQueue->base__queue_t), &result);
    printf("%d\r\n",result);
    
    dataBuf += 2;
    s_ptByteQueue->base__queue_t.base__i_queue_t.Enqueue(&(s_ptByteQueue->base__queue_t), &dataBuf);
    s_ptByteQueue->base__queue_t.base__i_queue_t.Dequeue(&(s_ptByteQueue->base__queue_t), &result);
    printf("%d\r\n",result);
    
    
    dataBuf += 2;
    s_ptByteQueue->base__queue_t.base__i_queue_t.Enqueue(&(s_ptByteQueue->base__queue_t), &dataBuf);
    s_ptByteQueue->base__queue_t.base__i_queue_t.Dequeue(&(s_ptByteQueue->base__queue_t), &result);
    printf("%d\r\n",result);
    
    dataBuf += 2;
    s_ptByteQueue->base__queue_t.base__i_queue_t.Enqueue(&(s_ptByteQueue->base__queue_t), &dataBuf);
    s_ptByteQueue->base__queue_t.base__i_queue_t.Dequeue(&(s_ptByteQueue->base__queue_t), &result);
    printf("%d\r\n",result);
    
    dataBuf += 2;
    s_ptByteQueue->base__queue_t.base__i_queue_t.Enqueue(&(s_ptByteQueue->base__queue_t), &dataBuf);
    s_ptByteQueue->base__queue_t.base__i_queue_t.Dequeue(&(s_ptByteQueue->base__queue_t), &result);
    printf("%d\r\n",result);
    
    dataBuf += 2;
    s_ptByteQueue->base__queue_t.base__i_queue_t.Enqueue(&(s_ptByteQueue->base__queue_t), &dataBuf);
    s_ptByteQueue->base__queue_t.base__i_queue_t.Dequeue(&(s_ptByteQueue->base__queue_t), &result);
    printf("%d\r\n",result);
    
    dataBuf += 2;
    s_ptByteQueue->base__queue_t.base__i_queue_t.Enqueue(&(s_ptByteQueue->base__queue_t), &dataBuf);
    s_ptByteQueue->base__queue_t.base__i_queue_t.Dequeue(&(s_ptByteQueue->base__queue_t), &result);
    printf("%d\r\n",result);
    
    dataBuf += 2;
    s_ptByteQueue->base__queue_t.base__i_queue_t.Enqueue(&(s_ptByteQueue->base__queue_t), &dataBuf);
    s_ptByteQueue->base__queue_t.base__i_queue_t.Dequeue(&(s_ptByteQueue->base__queue_t), &result);
    printf("%d\r\n",result);
    
    dataBuf += 2;
    s_ptByteQueue->base__queue_t.base__i_queue_t.Enqueue(&(s_ptByteQueue->base__queue_t), &dataBuf);
    s_ptByteQueue->base__queue_t.base__i_queue_t.Dequeue(&(s_ptByteQueue->base__queue_t), &result);
    printf("%d\r\n",result);
    
    
    delete_byte_queue(s_ptByteQueue);
    
    while (1) {
        test4B();
    }
 
    return 0;
}

#else
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
typedef void constructor_func(void* ptQueue, va_list *ptArg);

static void constructor(void* ptQueue, va_list *ptArg)
{
    uint8_t *pchBuffer = va_arg(*ptArg, uint8_t *);
    uint16_t hwSize = va_arg(*ptArg, uint16_t);
    
    printf("ptQueue: %s - \tpchBuffer: %s  - \thwSize:%d  \r\n", ptQueue,  pchBuffer, hwSize);
}

void wrapper(constructor_func *fnFunction, ...)
{
    va_list args;
    
    va_start(args, fnFunction );
    void *pstr = va_arg(args, void *);
    fnFunction(pstr, &args);
    va_end(args);
}


static uint8_t s_chQueue[] = "23r2r";
static uint8_t s_chBuffer[] = "23";
static uint16_t s_hwSize = 234;
static constructor_func *s_fnConstructor = NULL;


#define RUN (...) wrapper(__VA_ARGS__)


int main(int argc, const char * argv[])
{
    s_fnConstructor = constructor;
    wrapper(s_fnConstructor,s_chQueue, s_chBuffer, s_hwSize);
 
    
    
    RUN(s_fnConstructor,s_chQueue, s_chBuffer, s_hwSize);
    return 0;
}


#endif

