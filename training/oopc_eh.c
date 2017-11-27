//
//  oopc_eh.c
//
// Licensed under the Apache License, Version 2.0 (the "License");          
// you may not use this file except in compliance with the License.         
// You may obtain a copy of the License at                                  
//                                                                          
//    http://www.apache.org/licenses/LICENSE-2.0                            
//                                                                          
// Unless required by applicable law or agreed to in writing, software      
// distributed under the License is distributed on an "AS IS" BASIS,        
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and      
// limitations under the License.                                           
//
//  github: https://github.com/PaPazhao
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
    
    Object *ptSuper = (Object *)ptObjL;
    
    do {
        if (ptSuper == ptObjR) {
            return true;
        }
        if (NULL == ptSuper->ptBase) {
            break;
        }
        ptSuper = ptSuper->ptBase;
    } while (1);
    
    ptSuper = (Object *)ptObjR;

    do {
        if (ptSuper == ptObjL) {
            return true;
        }
        if (NULL == ptSuper->ptBase) {
            break;
        }
        ptSuper = ptSuper->ptBase;
    } while (1);

    return false;
}


/* EOF */
