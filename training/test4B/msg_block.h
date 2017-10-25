//
//  msg_block_t.h
//  training
//
//  Created by zhaoli on 2017/9/21.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef __msg_block_h__
#define __msg_block_h__

#include "app_cfg.h"

DECLARE_CLASS(msg_block_t)                                   
EXTERN_CLASS(msg_block_t)
    mail_t tEchoMail;
    event_t tEchoAck;                        
END_EXTERN_CLASS(msg_block_t)

extern void msg_init(msg_block_t* ptObj);
extern bool msg_open(msg_block_t* ptObj, uint8_t* pchChar);
extern bool msg_post(msg_block_t* ptObj, uint8_t* pchChar);


#endif /* msg_block_t_h */
