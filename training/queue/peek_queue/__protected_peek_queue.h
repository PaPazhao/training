//
//  Header.h
//  training
//
//  Created by zhaoli on 2017/9/27.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef __PROTECTED_PEEK_QUEUE_H__
#define __PROTECTED_PEEK_QUEUE_H__

#include "./__common_peek_queue.h"
#include "../byte_queue/__protected_byte_queue.h"

// 抽象类 queue_t
//declare_class(peek_queue_t)
extern_class(peek_queue_t,
	which(   inherit(byte_queue_t)
             implement(i_peek_queue_t)))

    uint16_t hwPeekHead;
    uint16_t hwPeekTail;
    uint16_t hwPeekLen;

end_extern_class(peek_queue_t, which(inherit(byte_queue_t) implement(i_peek_queue_t)))

#endif /* Header_h */
