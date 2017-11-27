//
//  test1A.c
//  State
//
//  Created by zhaoli on 2017/8/23.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

/*============================ INCLUDES ======================================*/
#include "./app_cfg.h"
#include "./__common_queue.h"

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
    protected_content(queue_t) *ptProtected = &this_protected(queue_t);
    
    if ((NULL == ptQueue) || (NULL == ptStream)) {
        return false;
    }
    
    if ((ptProtected->hwHead == ptProtected->hwTail) && (0 != ptProtected->hwLength)) {
        return false;
    }

    uint16_t hwItemSize = ptProtected->hwItemSize;
 
    if (NULL == memcpy(&ptProtected->pchBuffer[ptProtected->hwTail * hwItemSize], ptStream, hwItemSize)) {
        return false;
    }
 
    ptProtected->hwTail++;
    if (ptProtected->hwTail >= ptProtected->hwSize) {
        ptProtected->hwTail = 0;
    }
    ptProtected->hwLength++;
    
    return true;
}

bool dequeue(queue_t *ptQueue, void *ptStream)
{
    class(queue_t) *ptThis = (class(queue_t) *)ptQueue;
    protected_content(queue_t) *ptProtected = &this_protected(queue_t);
    
    if ((NULL == ptQueue)||(NULL == ptStream)) {
        return false;
    }
    
    if ((ptProtected->hwHead == ptProtected->hwTail) && (!ptProtected->hwLength)) {
        return false;
    }

    uint16_t hwItemSize = ptProtected->hwItemSize;
    if (NULL == memcpy(ptStream, &(ptProtected->pchBuffer[ptProtected->hwHead * hwItemSize]), hwItemSize)) {
        return false;
    }
    
    ptProtected->hwHead++;
    if (ptProtected->hwHead >= ptProtected->hwSize) {
        ptProtected->hwHead = 0;
    }
    ptProtected->hwLength--;

    return true;
}

class_abstract_cfg(queue_t)

implement_destructors(queue_t)
    
    protected_content(queue_t) *ptProtected = &this_protected(queue_t);

    destructors_body(
        this_interface(i_queue_t).Dequeue = NULL;
        this_interface(i_queue_t).Enqueue = NULL;
        ptProtected->hwItemSize = 0;
        ptProtected->pchBuffer = NULL;
        ptProtected->hwSize = 0;
        ptProtected->hwHead = 0;
        ptProtected->hwTail = 0;
        ptProtected->hwLength = 0;
        this.ptType = NULL;
    )

implement_constructor(queue_t)
    
    protected_content(queue_t) *ptProtected = &this_protected(queue_t);
    
    constructor_body(
 
        read_param(uint8_t *, pchBuffer);
        read_param(uint16_t, hwSize);

        if ((NULL == pchBuffer) || (0 == hwSize)) {
            return;
        }
        
        this_interface(i_queue_t).Dequeue = dequeue;
        this_interface(i_queue_t).Enqueue = enqueue;
        ptProtected->pchBuffer = pchBuffer;
        ptProtected->hwSize = hwSize;
        ptProtected->hwTail = 0;
        ptProtected->hwHead = 0;
        ptProtected->hwLength = 0;
        ptProtected->hwItemSize = 0;
        this.ptType = typeof(queue_t);
    )
 
/* EOF */
