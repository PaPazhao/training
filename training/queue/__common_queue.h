//
//  __common_queue.h
//  training
//
//  Created by zhaoli on 2017/10/20.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef __common_queue_h
#define __common_queue_h

#include "../app_cfg.h"

// protected 的属性、方法
DECLARE_PROTECTED(queue_t)
DEF_PROTECTED(queue_t)

    uint16_t hwItemSize;

END_DEF_PROTECTED(queue_t)


// interface
declare_class(queue_t)
def_interface(i_queue_t)

    bool (*Dequeue)(queue_t *ptQueue, void *ptStream);
    bool (*Enqueue)(queue_t *ptQueue, void *ptStream);

end_def_interface(i_queue_t)
 
#endif /* __common_queue_h */
