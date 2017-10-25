//
//  msg_block_t.c
//  training
//
//  Created by zhaoli on 2017/9/21.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#include "../app_cfg.h"


DECLARE_CLASS(msg_block_t)
DEF_CLASS(msg_block_t)
    mail_t tEchoMail;
    event_t tEchoAck;
END_DEF_CLASS(msg_block_t)

bool msg_open(msg_block_t* ptObj, uint8_t* pchChar)
{
    CLASS(msg_block_t) *ptThis = (CLASS(msg_block_t) *)ptObj;
    
    if ((NULL == ptThis) || (NULL == pchChar)) {
        return false;
    }
    
    uint8_t *pchMailObj = MAIL_OPEN(&(this.tEchoMail));
    
    if (pchMailObj) {
        *((uint8_t*)pchChar) = *pchMailObj;
        SET_EVENT(&(this.tEchoAck));
    } else {
        return false;
    }
    
    return true;
}

bool msg_post(msg_block_t* ptObj, uint8_t* pchChar)
{
    CLASS(msg_block_t) *ptThis = (CLASS(msg_block_t) *)ptObj;
    
    if ((NULL == ptThis) || (NULL == pchChar)) {
        return false;
    }
    
    if (WAIT_EVENT(&(this.tEchoAck))) {
        MAIL_POST(&(this.tEchoMail), pchChar);
        return true;
    } else {
        return false;
    }
}

void msg_init(msg_block_t* ptObj)
{
    CLASS(msg_block_t) *ptThis = (CLASS(msg_block_t) *)ptObj;
    
    if ((NULL == ptThis)) {
        return ;
    }
    
    INIT_EVENT(&(this.tEchoAck), true, AUTOSET);
    MAIL_INIT(&(this.tEchoMail));
}

