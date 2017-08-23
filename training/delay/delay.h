//
//  delay.h
//  State
//
//  Created by zhaoli on 2017/8/23.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef delay_h
#define delay_h

#include "./app_cfg.h"

#define DELAY_MS    100000
#define DELAY_S     1000 * DELAY_MS

extern_simple_fsm(delay_1s)

extern_fsm_initialiser(delay_1s, args(uint32_t wCounter))

extern_fsm_implementation(delay_1s)

#endif /* delay_h */
