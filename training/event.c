//
//  event.c
//  training
//
//  Created by zhaoli on 2017/8/26.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#include "event.h"

void set_event(event_t *ptEvent)
{
    if(NULL != ptEvent){
        ptEvent->bIsSet = true;
    }
}

void reset_event(event_t *ptEvent)
{
    if(NULL != ptEvent){
        ptEvent->bIsSet = false;
    }
}

bool wait_event(event_t *ptEvent)
{
    if(NULL == ptEvent ){
        return false;
    }
    
    if( AUTOSET == ptEvent->bAutoReset ){
        if(ptEvent->bIsSet){
            ptEvent->bIsSet = false;
            return true;
        }
    }
    
    return ptEvent->bIsSet;
}

void init_event(event_t *ptEvent,bool bInitValue,even_model_t tModel)
{
    if( NULL != ptEvent ){
        ptEvent->bIsSet = bInitValue;
        ptEvent->bAutoReset = tModel;
    }
}
