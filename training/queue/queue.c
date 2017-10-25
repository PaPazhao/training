//
//  test1A.c
//  State
//
//  Created by zhaoli on 2017/8/23.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

/*============================ INCLUDES ======================================*/
#include "./app_cfg.h"
#include "__common_queue.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
DECLARE_CLASS(queue_t)
DEF_CLASS(queue_t, 
    WHICH(  Object *ptType; 
            INHERIT(INTERNAL_PROTECTED(queue_t ))
            IMPLEMENT(i_queue_t)))

    uint8_t *pchBuffer;
    uint16_t hwSize;
    uint16_t hwHead;
    uint16_t hwTail;
    uint16_t hwLength;

END_DEF_CLASS(queue_t, WHICH(Object *ptType; INHERIT(INTERNAL_PROTECTED(queue_t)) IMPLEMENT(i_queue_t) ))

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
bool enqueue(queue_t *ptQueue, void *ptStream)
{
    CLASS(queue_t) *ptThis = (CLASS(queue_t) *)ptQueue;
    
    if ((NULL == ptQueue) || (NULL == ptStream)) {
        return false;
    }
    
    if ((this.hwHead == this.hwTail) && (0 != this.hwLength)) {
        return false;
    }
    
    uint16_t hwItemSize = this_protected(queue_t).hwItemSize;
    if (NULL == memcpy(&this.pchBuffer[this.hwTail * hwItemSize], ptStream, hwItemSize)) {
        return false;
    }
 
    this.hwTail++;
    if (this.hwTail >= this.hwSize) {
        this.hwTail = 0;
    }
    this.hwLength++;
    
    return true;
}

bool dequeue(queue_t *ptQueue, void *ptStream)
{
    CLASS(queue_t) *ptThis = (CLASS(queue_t) *)ptQueue;
    
    if ((NULL == ptQueue)||(NULL == ptStream)) {
        return false;
    }
    
    if ((this.hwHead == this.hwTail) && (!this.hwLength)) {
        return false;
    }
    
    uint16_t hwItemSize = this_protected(queue_t).hwItemSize;
    if (NULL == memcpy(ptStream, &(this.pchBuffer[this.hwHead * hwItemSize]), hwItemSize)) {
        return false;
    }
    
    this.hwHead++;
    if (this.hwHead >= this.hwSize) {
        this.hwHead = 0;
    }
    this.hwLength--;

    return true;
}

class_abstract_cfg(queue_t)

implement_destructors(queue_t)

    destructors_body(
        this_interface(i_queue_t).Dequeue = NULL;
        this_interface(i_queue_t).Enqueue = NULL;
        this_protected(queue_t).hwItemSize = 0;
        this.pchBuffer = NULL;
        this.hwSize = 0;
        this.hwHead = 0;
        this.hwTail = 0;
        this.hwLength = 0;
        this.ptType = NULL;
    )

implement_constructor(queue_t)

    constructor_body(
 
        read_param(uint8_t *, pchBuffer);
        read_param(uint16_t, hwSize);
        if ((NULL == pchBuffer) || (0 == hwSize)) {
            return;
        }
        
        this_interface(i_queue_t).Dequeue = dequeue;
        this_interface(i_queue_t).Enqueue = enqueue;
        this.pchBuffer = pchBuffer;
        this.hwSize = hwSize;
        this.hwTail = 0;
        this.hwHead = 0;
        this.hwLength = 0;
        this_protected(queue_t).hwItemSize = 0 ;
        this.ptType = typeof(queue_t);
    )

/* EOF */
