//
//  CriticalSector.h
//  State
//
//  Created by zhaoli on 2017/8/22.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef __CRITICAL_SECTOR__
#define __CRITICAL_SECTOR__

#include <stdbool.h>
#include <stdlib.h>

#define ENTER_CRITICAL_SECTOR(__CRITICAL)   \
enter_critical_sector(__CRITICAL)

#define LEAVE_CRITICAL_SECTOR(__CRITICAL)   \
leave_critical_sector(__CRITICAL)

#define INIT_CRITICAL_SECTOR(__CRITICAL)    \
init_critical_sector(__CRITICAL)


typedef struct {
    bool bLocked;
}critical_sector_t;

bool enter_critical_sector(critical_sector_t *ptSignal);
void leave_critical_sector(critical_sector_t *ptSignal);
void init_critical_sector(critical_sector_t *ptSignal);

#endif

