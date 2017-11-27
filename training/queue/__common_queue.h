//
//  __common_queue.h
//  training
//
//  Created by zhaoli on 2017/10/20.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef __COMMON_QUEUE_H__
#define __COMMON_QUEUE_H__

#include "../app_cfg.h"

// protected 的属性、方法
declare_protected(queue_t)
def_protected(queue_t)
    uint16_t hwSize;
    uint16_t hwHead;
    uint16_t hwTail;
    uint16_t hwLength;
    uint16_t hwItemSize;
    uint8_t *pchBuffer;
end_def_protected(queue_t)

// interface
declare_class(queue_t)
def_interface(i_queue_t)

    bool (*Dequeue)(queue_t *ptQueue, void *ptStream);
    bool (*Enqueue)(queue_t *ptQueue, void *ptStream);

end_def_interface(i_queue_t)
 
#endif /* __common_queue_h */
