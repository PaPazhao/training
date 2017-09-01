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

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/

#define MAIL_INIT(__MAIL)           mail_init(__MAIL)

#define MAIL_OPEN(__MAIL)           mail_open(__MAIL)

#define MAIL_POST(__MAIL, __OBJ)    mail_post(__MAIL, __OBJ)

#define MAIL_IS_OPEN(__MAIL)        mail_isOpen(__MAIL)


/*============================ TYPES =========================================*/
typedef struct {
    bool bIsOpen;
    void *pTarget;
}mail_t;

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/**
 init a post char mail
 
 @param pTarget obj
 */
extern void mail_init(mail_t *pTarget);

/**
 open a mail
 
 @param pTarget obj
 @return target
 */
extern void* mail_open(mail_t *pTarget);

/**
 send a mail
 
 @param pTarget mail obj pointer
 @param tObj content obj pointer
 */
extern void mail_post(mail_t *pTarget, void *tObj);

/**
 mail is open
 
 @param pTarget mail obj pointer
 @return bool
 */
extern bool mail_isOpen(mail_t *pTarget);

#endif /* mail_h */
/* EOF */
