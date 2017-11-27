//
//  byte_queue.c
//  training
//
//  Created by zhaoli on 2017/9/27.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

/*============================ INCLUDES ======================================*/
#include "./app_cfg.h"
#include "__common_peek_queue.h"
#include "__protected_byte_queue.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

declare_class(peek_queue_t)
def_class(peek_queue_t, which(inherit(byte_queue_t) implement(i_peek_queue_t)) )
    uint16_t hwPeekHead;
    uint16_t hwPeekTail;
    uint16_t hwPeekLen;
end_def_class(peek_queue_t, which(inherit(byte_queue_t) implement(i_peek_queue_t)))

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
static peek_queue_t* alloc_memory(void);
static void free_memory(peek_queue_t* ptItem);
static bool reset_peek_byte(peek_queue_t *ptQueue);
static bool get_all_peek_byte(peek_queue_t *ptQueue);
static bool peek_byte_queue(peek_queue_t *ptQueue, uint8_t *pchObj);
static bool peek_dequeue(peek_queue_t *ptQueue, void *ptStream);
static bool peek_enqueue(peek_queue_t *ptQueue, void *ptStream);

// 重写方法列表
def_structure(overwrite_t)
    bool (*Dequeue)(queue_t *ptQueue, void *ptStream);
    bool (*Enqueue)(queue_t *ptQueue, void *ptStream);
end_def_structure(overwrite_t)

static overwrite_t s_tOverWriteMethod;

/*============================ IMPLEMENTATION ================================*/
class_derived_cfg(peek_queue_t, queue_t)

implement_constructor(peek_queue_t)

    constructor_body(
        
        read_param(uint8_t*, pchBuffer);
        read_param(uint16_t, hwSize);
 
        if ((NULL == pchBuffer) || (0 == hwSize)) {
            return;
        }
 
        // 1、调用父类构造方法
        base_constructor(peek_queue_t, base_obj(byte_queue_t), pchBuffer, hwSize);
                     
        // 2、构造当前类属性、接口
         this.hwPeekHead = 0;
         this.hwPeekLen = 0;
         this.hwPeekTail = 0;
    
         this_interface(i_peek_queue_t).GetAllPeek  = get_all_peek_byte;
         this_interface(i_peek_queue_t).Peek        = peek_byte_queue;
         this_interface(i_peek_queue_t).ResetPeek   = reset_peek_byte;

                     ____p_queue_t *ptSuperProtecd = (____p_queue_t *)(&(this.base__byte_queue_t.base__queue_t.base____p_queue_t));
                     ptSuperProtecd->hwItemSize = 1;
                     
                     s_tOverWriteMethod.Dequeue = this.base__byte_queue_t.base__queue_t.base__i_queue_t.Dequeue;
                     this.base__byte_queue_t.base__queue_t.base__i_queue_t.Dequeue = (void *)peek_dequeue;
                     
                     s_tOverWriteMethod.Enqueue = this.base__byte_queue_t.base__queue_t.base__i_queue_t.Enqueue;
                     this.base__byte_queue_t.base__queue_t.base__i_queue_t.Enqueue = (void*)peek_enqueue;

    )

implement_destructors(peek_queue_t)

    destructors_body(
        // 1、析构当前类
        this.hwPeekHead = 0;
        this.hwPeekLen = 0;
        this.hwPeekTail = 0;
        this_interface(i_peek_queue_t).GetAllPeek  = NULL;
        this_interface(i_peek_queue_t).Peek        = NULL;
        this_interface(i_peek_queue_t).ResetPeek   = NULL;
                     
        // 2、调用父类析构，析构父类
        base_destructors(peek_queue_t, byte_queue_t);
    )


peek_queue_t* new_peek_queue(uint8_t *pchBuffer, uint16_t hwSize)
{
    if ((NULL == pchBuffer) || (0 == hwSize)) {
        return NULL;
    }

    // 1、申请内存
    peek_queue_t *ptThis = alloc_memory();
    if (NULL == ptThis) {
        return NULL;
    }
    
    // 2、构造
    this_constructor(ptThis, pchBuffer, hwSize);
 
    return ptThis;
}

void delete_peek_queue(peek_queue_t *ptQueue)
{
    class(peek_queue_t) *ptThis = (class(peek_queue_t) *)ptQueue;
    
    if (NULL == ptThis) {
        return;
    }
    
    // 1、析构
    this_destructors(ptQueue);
    
    // 2、释放内存
    free_memory(ptQueue);
}

// overwrite i_queue_t method: dequeue:
static bool peek_dequeue(peek_queue_t *ptQueue, void *ptStream)
{
    class(peek_queue_t) *ptThis = (class(peek_queue_t) *)ptQueue;
    if (NULL == ptQueue || NULL == ptStream) {
        return false;
    }
    
    if (!s_tOverWriteMethod.Dequeue(&(this.base__byte_queue_t.base__queue_t), ptStream)) {
        return false;
    }

    ____p_queue_t *ptSuperProtecd = (____p_queue_t *)(&(this.base__byte_queue_t.base__queue_t.base____p_queue_t));
    this.hwPeekLen = ptSuperProtecd->hwLength;
 
    return true;
}

// overwrite i_queue_t method: enqueue:
static bool peek_enqueue(peek_queue_t *ptQueue, void *ptStream)
{
    class(peek_queue_t) *ptThis = (class(peek_queue_t) *)ptQueue;
    if (NULL == ptQueue || NULL == ptStream) {
        return false;
    }

    if(!s_tOverWriteMethod.Enqueue(&(this.base__byte_queue_t.base__queue_t), ptStream)) {
        return false;
    }

    this.hwPeekLen ++;

    return true;
}

static bool peek_byte_queue(peek_queue_t *ptQueue, uint8_t *pchObj)
{
    class(peek_queue_t) *ptThis = (class(peek_queue_t) *)ptQueue;
    if (NULL == ptQueue || NULL == pchObj) {
        return false;
    }
    
    ____p_queue_t *ptSuperProtecd = (____p_queue_t *)(&(this.base__byte_queue_t.base__queue_t.base____p_queue_t));
 
    if((this.hwPeekHead == ptSuperProtecd->hwTail) && (!this.hwPeekLen )){
        return false;
    }
    
    *pchObj = ptSuperProtecd->pchBuffer[this.hwPeekHead];
    this.hwPeekHead ++;
    if (this.hwPeekHead >= ptSuperProtecd->hwSize) {
        this.hwPeekHead = 0;
    }
    this.hwPeekLen--;
    
    return true;
}

static bool get_all_peek_byte(peek_queue_t *ptQueue)
{
    class(peek_queue_t) *ptThis = (class(peek_queue_t) *)ptQueue;
    if (NULL == ptQueue) {
        return false;
    }
    
    ____p_queue_t *ptSuperProtecd = (____p_queue_t *)(&(this.base__byte_queue_t.base__queue_t.base____p_queue_t));
    
    ptSuperProtecd->hwHead = this.hwPeekHead;
    ptSuperProtecd->hwLength = this.hwPeekLen;
    
    return true;
}

static bool reset_peek_byte(peek_queue_t *ptQueue)
{
    class(peek_queue_t) *ptThis = (class(peek_queue_t) *)ptQueue;
    if (NULL == ptQueue) {
        return false;
    }
    
    ____p_queue_t *ptSuperProtecd = (____p_queue_t *)(&(this.base__byte_queue_t.base__queue_t.base____p_queue_t));
 
    this.hwPeekHead = ptSuperProtecd->hwHead;
    this.hwPeekLen  = ptSuperProtecd->hwLength;
    
    return true;
}

/////////////////////////////// 对象内存池操作 /////////////////////////////////
DEF_POOL(PEEK_QUEUE, peek_queue_t, uint8_t, uint8_t);

static POOL(PEEK_QUEUE) s_tPeekQueueObjPool;

void init_peek_pool_cfg(void)
{
    static POOL_ITEM(PEEK_QUEUE) s_tPoolItem[4];
    
    POOL_INIT(PEEK_QUEUE, &s_tPeekQueueObjPool);
 
    POOL_ADD_HEAP(PEEK_QUEUE, &s_tPeekQueueObjPool, s_tPoolItem, 4);
}

static peek_queue_t* alloc_memory(void)
{
    return POOL_NEW(PEEK_QUEUE, &s_tPeekQueueObjPool);
}

static void free_memory(peek_queue_t* ptItem)
{
    POOL_FREE(PEEK_QUEUE, &s_tPeekQueueObjPool, ptItem);
}

/* EOF */
