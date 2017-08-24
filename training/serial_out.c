//
//  serial_out.c
//  State
//
//  Created by zhaoli on 2017/8/23.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#include "app_cfg.h"

bool serial_out(uint8_t chByte) {
    static bool s_bIsStart = true;
    static uint32_t s_wCount = 0;
    
    if (s_bIsStart) {
        s_wCount = 0;
        s_bIsStart = false;
        printf("%c",chByte);
    } else {
        s_wCount += 1;
        if (s_wCount > 1000000) {
            s_bIsStart = true;
        }
    }
    
    return s_bIsStart;
}
