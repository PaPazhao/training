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
declare_class(queue_t)
def_class(queue_t, 
    which(  Object *ptType;
            inherit(protected(queue_t))
            implement(i_queue_t)))

end_def_class(queue_t, which(Object *ptType; inherit(protected(queue_t)) implement(i_queue_t) ))

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
bool enqueue(queue_t *ptQueue, void *ptStream)
{
    class(queue_t) *ptThis = (class(queue_t) *)ptQueue;
    
    if ((NULL == ptQueue) || (NULL == ptStream)) {
        return false;
    }
    
    if ((this_protected(queue_t).hwHead == this_protected(queue_t).hwTail) && (0 != this_protected(queue_t).hwLength)) {
        return false;
    }

    uint16_t hwItemSize =  this_protected(queue_t).hwItemSize;
    
    if (NULL == memcpy(&this_protected(queue_t).pchBuffer[this_protected(queue_t).hwTail * hwItemSize], ptStream, hwItemSize)) {
        return false;
    }
 
    this_protected(queue_t).hwTail++;
    if (this_protected(queue_t).hwTail >= this_protected(queue_t).hwSize) {
        this_protected(queue_t).hwTail = 0;
    }
    this_protected(queue_t).hwLength++;
    
    return true;
}

bool dequeue(queue_t *ptQueue, void *ptStream)
{
    class(queue_t) *ptThis = (class(queue_t) *)ptQueue;
    
    if ((NULL == ptQueue)||(NULL == ptStream)) {
        return false;
    }
    
    if ((this_protected(queue_t).hwHead == this_protected(queue_t).hwTail) && (!this_protected(queue_t).hwLength)) {
        return false;
    }

    uint16_t hwItemSize = this_protected(queue_t).hwItemSize;
    if (NULL == memcpy(ptStream, &(this_protected(queue_t).pchBuffer[this_protected(queue_t).hwHead * hwItemSize]), hwItemSize)) {
        return false;
    }
    
    this_protected(queue_t).hwHead++;
    if (this_protected(queue_t).hwHead >= this_protected(queue_t).hwSize) {
        this_protected(queue_t).hwHead = 0;
    }
    this_protected(queue_t).hwLength--;

    return true;
}

class_abstract_cfg(queue_t)

implement_destructors(queue_t)

    destructors_body(
        this_interface(i_queue_t).Dequeue = NULL;
        this_interface(i_queue_t).Enqueue = NULL;
        this_protected(queue_t).hwItemSize = 0;
        this_protected(queue_t).pchBuffer = NULL;
        this_protected(queue_t).hwSize = 0;
        this_protected(queue_t).hwHead = 0;
        this_protected(queue_t).hwTail = 0;
        this_protected(queue_t).hwLength = 0;
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
        this_protected(queue_t).pchBuffer = pchBuffer;
        this_protected(queue_t).hwSize = hwSize;
        this_protected(queue_t).hwTail = 0;
        this_protected(queue_t).hwHead = 0;
        this_protected(queue_t).hwLength = 0;
        this_protected(queue_t).hwItemSize = 0;
        this.ptType = typeof(queue_t);
    )
 
/* EOF */
