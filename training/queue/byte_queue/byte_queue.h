//
//  byte_queue.h
//  training
//
//  Created by zhaoli on 2017/9/27.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef __byte_queue_h__
#define __byte_queue_h__

/*============================ INCLUDES ======================================*/
#include "./app_cfg.h"
#include "../queue.h"
 
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
 

// 字节队列类
declare_class(byte_queue_t)
extern_class(byte_queue_t, inherit(queue_t))

end_extern_class(byte_queue_t, inherit(queue_t))

// 创建对象
extern byte_queue_t* new_byte_queue(uint8_t *pchBuffer, uint16_t hwSize);
// 销毁对象
extern void delete_byte_queue(byte_queue_t *ptQueue);


////////////////////////////////////////////////////////////////////////////////
extern void init_pool_cfg(void);

#endif /* byte_queue_h */
/* EOF */
