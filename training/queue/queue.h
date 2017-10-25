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
declare_class(queue_t)
def_interface(i_queue_t)

    bool (*Dequeue)(queue_t *ptQueue, void *ptStream);
    bool (*Enqueue)(queue_t *ptQueue, void *ptStream);

end_def_interface(i_queue_t)

// protected 的属性、方法
declare_protected(queue_t)
extern_protected(queue_t)

    uint16_t hwItemSize;

end_extern_protected(queue_t)

// 抽象类 queue_t
extern_class(queue_t,
    which(  Object *ptType;
            inherit( protected(queue_t))
            implement(i_queue_t)))

    uint8_t *pchBuffer;
    uint16_t hwSize;
    uint16_t hwHead;
    uint16_t hwTail;
    uint16_t hwLength;
    
end_extern_class(queue_t, which(  Object *ptType;  inherit(protected(queue_t)) implement(i_queue_t)))

#endif
/* EOF */

