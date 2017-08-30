//
//  event.h
//  training
//
//  Created by zhaoli on 2017/8/26.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef __EVENT_H__
#define __EVENT_H__

#include <stdio.h>
#include <stdbool.h>

#define SET_EVENT(__EVENT)         set_event(__EVENT)
#define WAIT_EVENT(__EVENT)        wait_event(__EVENT)
#define RESET_EVENT(__EVENT)       reset_event(__EVENT)
#define INIT_EVENT(__EVENT, __EVENT_VALUE, __MANUAL)   \
init_event(__EVENT,__EVENT_VALUE,__MANUAL)


typedef enum {
    MANUAL  = 0,
    AUTOSET
}even_model_t;


typedef struct{
    bool bAutoReset;
    bool bIsSet;
}event_t;

void init_event(event_t *ptEvent,bool bInitValue,even_model_t tModel);
void set_event(event_t *ptEvent);
void reset_event(event_t *ptEvent);
bool wait_event(event_t *ptEvent);

#endif /* event_h */
