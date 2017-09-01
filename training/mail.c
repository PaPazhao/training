//
//  mail.c
//  training
//
//  Created by zhaoli on 2017/9/1.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

/*============================ INCLUDES ======================================*/
#include "./mail.h"

/*============================ MACROS ========================================*/

/*============================ MACROFIED FUNCTIONS ===========================*/

/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/

/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/

/*============================ IMPLEMENTATION ================================*/


/**
 init a post char mail
 
 @param pTarget obj
 */
void mail_init(mail_t *pTarget) {
    if (pTarget) {
        pTarget->bIsOpen = true;
        pTarget->pTarget = NULL;
    }
}

/**
 open a mail
 
 @param pTarget obj
 @return target
 */
void* mail_open(mail_t *pTarget) {
    
    if (NULL == pTarget) {
        return NULL;
    }
    
    if (!pTarget->bIsOpen) {
        pTarget->bIsOpen = true;
        return pTarget->pTarget;
    }
    
    return NULL;
}

/**
 send a mail
 
 @param pTarget mail obj pointer
 @param tObj content obj pointer
 */
void mail_post(mail_t *pTarget, void *tObj) {
    
    if (pTarget && tObj) {
        pTarget->bIsOpen = false;
        pTarget->pTarget = tObj;
    }
}

/**
 mail is open
 
 @param pTarget mail obj pointer
 @return bool
 */
bool mail_isOpen(mail_t *pTarget) {
    
    if (pTarget) {
        return pTarget->bIsOpen;
    }
    
    return true;
}

/* EOF */
