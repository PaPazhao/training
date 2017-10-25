//
//  mail.h
//  training
//
//  Created by zhaoli on 2017/9/1.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef __MAIL_H__
#define __MAIL_H__

/*============================ INCLUDES ======================================*/
#include "./app_cfg.h"
#include "./event.h"
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/

#define MAIL_INIT(__MAIL)           mail_init(__MAIL)

#define MAIL_OPEN(__MAIL)           mail_open(__MAIL)

#define MAIL_POST(__MAIL, __OBJ)    mail_post(__MAIL, __OBJ)


/*============================ TYPES =========================================*/

typedef struct {
    event_t tCreatEvent;    // 添加一个消息到邮件时被set，邮件打开reset
    void *pTarget;
}mail_t;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/**
 init a post char mail
 
 @param ptMail obj
 */
extern void mail_init(mail_t *ptMail);

/**
 open a mail
 
 @param ptMail obj
 @return target
 */
extern void* mail_open(mail_t *ptMail);

/**
 send a mail
 
 @param ptMail mail obj pointer
 @param tObj content obj pointer
 */
extern void mail_post(mail_t *ptMail, void *tObj);

extern void mail_reset(mail_t *ptMail);

#endif /* mail_h */
/* EOF */
