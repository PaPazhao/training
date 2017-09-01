//
//  CriticalSector.c
//  State
//
//  Created by zhaoli on 2017/8/23.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#include "./critical section.h"

bool enter_critical_sector(critical_sector_t *ptSignal)
{
    if((NULL != ptSignal) && (!(ptSignal ->bLocked))){
        ptSignal -> bLocked = true;
        return true;
    }
    return false;
}

void leave_critical_sector(critical_sector_t *ptSignal)
{
    if(NULL != ptSignal) {
        ptSignal -> bLocked = false;
    }
}
void init_critical_sector(critical_sector_t *ptSignal)
{
    if(NULL != ptSignal) {
        ptSignal -> bLocked = false;
    }
}
