//
//  bind.c
//  training
//
//  Created by zhaoli on 2017/9/19.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#include "bind.h"
 
#ifndef SERIVECE_COUNT
#define SERIVECE_COUNT      4
#warning macro SERIVECE_COUNT is not defiend, now use default value 4
#endif

static service_task_t s_tService[SERIVECE_COUNT];
static uint8_t s_chIndex = 0;


service_task_t* delegate_register(handler_fn *fnHandle, void* pObj)
{
    
    if ((NULL == fnHandle) || (NULL == pObj)) {
        return NULL;
    }
    
    if (s_chIndex < sizeof(s_tService) / sizeof(s_tService[0])) {
        service_task_t* ptService = &s_tService[s_chIndex];
        
        s_tService[s_chIndex].fnHandler = fnHandle;
        s_tService[s_chIndex].ptTag = pObj;
        s_chIndex += 1;
        return ptService;
    }
    
    return NULL;
}


bool delegate_unregister(handler_fn *fnHandle, void* pObj)
{
    return true;
}

bool invoke(service_task_t *ptService, void* ptParams){
    if (NULL == ptService) {
        return false;
    }
    
    return ptService->fnHandler(ptService->ptTag, ptParams);
}













