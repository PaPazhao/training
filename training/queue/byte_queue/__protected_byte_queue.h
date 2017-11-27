//
//  Header.h
//  training
//
//  Created by zhaoli on 2017/9/27.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef __PROTECTED_BYTE_QUEUE_H__
#define __PROTECTED_BYTE_QUEUE_H__

#include "./app_cfg.h"
#include "__common_byte_queue.h"
#include "../__protected_queue.h"

declare_class(byte_queue_t)
extern_class(byte_queue_t,
    which( inherit(queue_t) ))

end_extern_class(byte_queue_t, which( inherit(queue_t) ))


#endif /* Header_h */
