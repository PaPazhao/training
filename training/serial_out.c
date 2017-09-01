//
//  serial_out.c
//  State
//
//  Created by zhaoli on 2017/8/23.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#include "app_cfg.h"

static uint8_t s_chframeBuf[] = "WORLD           Abd               WORLD               Abd3        wWORLD        WORLLD";
static uint8_t s_chIndex = 0;

bool serial_out(uint8_t chByte)
{
    static bool s_bIsStart = false;
    static uint32_t s_wCount = 40;
        // printf("\r\n                                seriout: %c -- %d, count: %d\r\n",chByte, s_bIsStart, s_wCount);
    if (s_bIsStart) {
        s_wCount = 40;
        s_bIsStart = false;
    } else {
        if (s_wCount) {
            if (s_wCount == 1) {
                printf("%c",chByte);
            }
            s_wCount -= 1;
        } else {
            s_bIsStart = true;
        }
    }
    // if (s_bIsStart) {
    //     printf("\r\n                                seriout: %c over\r\n",chByte );
    // }
    return s_bIsStart;
}

bool serial_in(uint8_t *pchByte)
{
    static bool s_bIsStart = true;
    static uint32_t s_wCount = 0;
    
    if (NULL == pchByte) {
        return false;
    }
    
    if (s_bIsStart) {
        s_wCount = 0;
        s_bIsStart = false;
        
        if (s_chIndex < sizeof(s_chframeBuf)) {
            *pchByte = s_chframeBuf[s_chIndex];
            s_chIndex += 1;
//            printf("\r\n-===-=-==============================%c \r\n", *pchByte);
            return true;
        } else {
            return false;
        }
    } else {
        s_wCount += 1;
        if (s_wCount > 2000) {
            s_bIsStart = true;
        }
    }
    
    return false;
}
