//
//  __common_peek_queue.h
//  training
//
//  Created by zhaoli on 2017/11/7.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef __COMMON_PEEK_QUEUE_H__
#define __COMMON_PEEK_QUEUE_H__

#include "../app_cfg.h"

// 定义接口，定义私有

// interface
declare_class(peek_queue_t)
def_interface(i_peek_queue_t)
    bool (*Peek)        (peek_queue_t *ptQueue, uint8_t *pchObj);
    bool (*GetAllPeek)  (peek_queue_t *ptQueue);
    bool (*ResetPeek)   (peek_queue_t *ptQueue);
end_def_interface(i_peek_queue_t)

// protected 的属性、方法
declare_protected(peek_queue_t)
def_protected(peek_queue_t)

end_def_protected(peek_queue_t)

#endif /* __common_peek_queue_h */
