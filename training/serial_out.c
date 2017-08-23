//
//  serial_out.c
//  State
//
//  Created by zhaoli on 2017/8/23.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#include "app_cfg.h"

bool serial_out(uint8_t chByte) {
    static bool isStart = true;
    
    if (isStart) {
        printf("%c",chByte);
    }
    
    isStart = !isStart;
    
    return isStart;
}
