//
//  test1A.h
//  State
//
//  Created by zhaoli on 2017/8/23.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef __CLASS_QUEUE_H__
#define __CLASS_QUEUE_H__

/*============================ INCLUDES ======================================*/
#include "../app_cfg.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
// interface 
DECLARE_CLASS(queue_t)
DEF_INTERFACE(i_queue_t)

    bool (*Dequeue)(queue_t *ptQueue, void *ptStream);
    bool (*Enqueue)(queue_t *ptQueue, void *ptStream);

END_DEF_INTERFACE(i_queue_t)

// protected 的属性、方法
DECLARE_PROTECTED(queue_t)
EXTERN_PROTECTED(queue_t)

    uint16_t hwItemSize;

END_EXTERN_PROTECTED(queue_t)

// 抽象类 queue_t
EXTERN_CLASS(queue_t,  
    WHICH(  Object *ptType; 
            INHERIT( PROTECTED(queue_t))
            IMPLEMENT(i_queue_t)))

    uint8_t *pchBuffer;
    uint16_t hwSize;
    uint16_t hwHead;
    uint16_t hwTail;
    uint16_t hwLength;
    
END_EXTERN_CLASS(queue_t, WHICH(  Object *ptType;  INHERIT(PROTECTED(queue_t)) IMPLEMENT(i_queue_t)))

#endif
/* EOF */

