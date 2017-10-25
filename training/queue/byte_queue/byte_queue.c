//
//  byte_queue.c
//  training
//
//  Created by zhaoli on 2017/9/27.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

/*============================ INCLUDES ======================================*/
#include "./app_cfg.h"
#include "./__protected_byte_queue.h"
#include "../__protected_queue.h"


/*============================ MACROS ========================================*/

/*============================ MACROFIED FUNCTIONS ===========================*/
 
/*============================ TYPES =========================================*/

DECLARE_CLASS(byte_queue_t)

DEF_CLASS(byte_queue_t, INHERIT(queue_t))

END_DEF_CLASS(byte_queue_t, INHERIT(queue_t))

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
static byte_queue_t* alloc_memory(void);
static void free_memory(byte_queue_t* ptItem);

/*============================ IMPLEMENTATION ================================*/

class_derived_cfg(byte_queue_t, queue_t)

implement_constructor(byte_queue_t)

    constructor_body(
        
        read_param(uint8_t*, pchBuffer);
        read_param(uint16_t, hwSize);
 
        if ((NULL == pchBuffer) || (0 == hwSize)) {
            return;
        }

        // 1、调用父类构造方法
        base_constructor(byte_queue_t, REF_OBJ_AS(this, queue_t), pchBuffer, hwSize);

        // 2、构造当
        base_protected(queue_t)->hwItemSize = 1;
    )

implement_destructors(byte_queue_t)

    destructors_body(
        // 1、析构当前类
                     
        // 2、调用父类析构，析构父类
        base_destructors(byte_queue_t, REF_OBJ_AS(this, queue_t));
    )

byte_queue_t* new_byte_queue(uint8_t *pchBuffer, uint16_t hwSize)
{
    if ((NULL == pchBuffer) || (0 == hwSize)) {
        return NULL;
    }

    // 1、申请内存
    byte_queue_t *ptThis = alloc_memory();
    if (NULL == ptThis) {
        return NULL;
    }
    
    // 2、构造
    this_constructor(ptThis, pchBuffer, hwSize);
    
    return ptThis;
}

void delete_byte_queue(byte_queue_t *ptQueue)
{
    CLASS(byte_queue_t) *ptThis = (CLASS(byte_queue_t) *)ptQueue;
    
    if (NULL == ptThis) {
        return;
    }
    
    // 1、析构
    this_destructors(ptQueue);
    
    // 2、释放内存
    free_memory(ptQueue);
}


/////////////////////////////// 对象内存池操作 /////////////////////////////////
DEF_POOL(BYTE_QUEUE, byte_queue_t, uint8_t, uint8_t);

static POOL(BYTE_QUEUE) s_tByteQueueObjPool;

void init_pool_cfg(void)
{
    static POOL_ITEM(BYTE_QUEUE) s_tPoolItem[4];
    
    POOL_INIT(BYTE_QUEUE, &s_tByteQueueObjPool);
 
    POOL_ADD_HEAP(BYTE_QUEUE, &s_tByteQueueObjPool, s_tPoolItem, 4);
}

static byte_queue_t* alloc_memory(void)
{
    return POOL_NEW(BYTE_QUEUE, &s_tByteQueueObjPool);
}

static void free_memory(byte_queue_t* ptItem)
{
    POOL_FREE(BYTE_QUEUE, &s_tByteQueueObjPool, ptItem);
}

/* EOF */
