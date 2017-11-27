//
//  byte_queue.h
//  training
//
//  Created by zhaoli on 2017/9/27.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef __peek_byte_queue_h__
#define __peek_byte_queue_h__

/*============================ INCLUDES ======================================*/
#include "./app_cfg.h"
#include "byte_queue.h"
//#include "__protected_queue.h"
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
// interface
declare_class(peek_queue_t)
def_interface(i_peek_queue_t)
    bool (*Peek)        (peek_queue_t *ptQueue, uint8_t *pchObj);
    bool (*GetAllPeek)  (peek_queue_t *ptQueue);
    bool (*ResetPeek)   (peek_queue_t *ptQueue);
end_def_interface(i_peek_queue_t)
// 字节队列类
declare_class(peek_queue_t)
extern_class(peek_queue_t,
    which(   inherit(byte_queue_t)
             implement(i_peek_queue_t)))

    uint16_t hwPeekHead;
    uint16_t hwPeekTail;
    uint16_t hwPeekLen;

end_extern_class(peek_queue_t, which(inherit(byte_queue_t) implement(i_peek_queue_t)))

// 创建对象
extern peek_queue_t* new_peek_queue(uint8_t *pchBuffer, uint16_t hwSize);
// 销毁对象
extern void delete_peek_queue(peek_queue_t *ptQueue);


////////////////////////////////////////////////////////////////////////////////
extern void init_peek_pool_cfg(void);

#endif /* byte_queue_h */
/* EOF */
