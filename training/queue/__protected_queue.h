//
//  __protected_queue.h
//  training
//
//  Created by zhaoli on 2017/9/27.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef __PROTECTED_QUEUE_H__
#define __PROTECTED_QUEUE_H__

#include "__common_queue.h"

// 抽象类 queue_t
extern_class(queue_t,
    which(  Object *ptType;
            inherit(protected(queue_t))
            implement(i_queue_t)))

end_extern_class(queue_t, which( Object *ptType; inherit(protected(queue_t)) implement(i_queue_t)))
 
#endif /* Header_h */
