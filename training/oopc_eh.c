//
//  oopc_eh.c
//  training
//
//  Created by zhaoli on 2017/10/18.
//  Copyright © 2017年 zhaoli. All rights reserved.
//


/*============================ INCLUDES ======================================*/
#include "oopc_eh.h"
#include <stdbool.h>
#include <stdint.h>


void wrapper(constructor_fn *fnFunction, ...)
{
    va_list args;
    
    va_start(args, fnFunction );
    void *pstr = va_arg(args, void *);
    fnFunction(pstr, &args);
    va_end(args);
}

Object* is_type_of(void *ptObj)
{
    if (NULL == ptObj) {
        return NULL;
    }
    
    Object *ptSuper = (Object *)ptObj;
    
    do {
        if (NULL == ptSuper->ptBase) {
            return ptSuper;
        }
        
        ptSuper = ptSuper->ptBase;
    } while(1);
    
    return NULL;
}

bool is_type_equal(void *ptObjL, void *ptObjR)
{
    if ((NULL == ptObjL) || (NULL == ptObjR)){
        return false;
    }
    
    if (ptObjL == ptObjR) {
        return true;
    }
    
    Object* ptTypeL = is_type_of(ptObjL);
    Object* ptTypeR = is_type_of(ptObjR);
    
    return ptTypeR == ptTypeL;
}


/* EOF */
