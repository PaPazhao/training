//
//  bind.h
//  training
//
//  Created by zhaoli on 2017/9/19.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef bind_h
#define bind_h

#include <stdbool.h>
#include <stdint.h>

#define SERIVECE_COUNT      4

/**
 handler_fn

 @param ptObj 被绑定的数据
 @param ptParams 调用事件处理函数需要的参数
 @return 是否完成
 */
typedef bool handler_fn(void* ptObj, void* ptParams);

typedef struct {
    void* ptTag;                //绑定事件处理函数的数据源对象。
    handler_fn *fnHandler;
} service_task_t;


extern service_task_t* delegate_register(handler_fn *fnHandle, void* pObj);

extern bool delegate_unregister(handler_fn *fnHandle, void* pObj);

extern bool invoke(service_task_t *ptService, void* ptParams);


#endif /* bind_h */
