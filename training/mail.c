//
//  mail.c
//  training
//
//  Created by zhaoli on 2017/9/1.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#include "./mail.h"

void mail_init(mail_t *ptMail)
{
    if (ptMail) {
        INIT_EVENT(&ptMail->tCreatEvent, false, AUTOSET);
        ptMail->pTarget = NULL;
    }
}

void* mail_open(mail_t *ptMail)
{
    if (NULL == ptMail) {
        return NULL;
    }
    
    if ( WAIT_EVENT(&ptMail->tCreatEvent)) {
        return ptMail->pTarget;
    }
    
    return NULL;
}

void mail_post(mail_t *ptMail, void *tObj)
{
    if (ptMail && tObj) {
        SET_EVENT(&ptMail->tCreatEvent);
        ptMail->pTarget = tObj;
    }
}


/* EOF */
