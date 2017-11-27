//
//  oopc_eh.h
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//  github: https://github.com/PaPazhao
//
//  Created by zhaoli on 2017/10/18.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef __OOPC_EH_H__
#define __OOPC_EH_H__

/*============================ INCLUDES ======================================*/
#include <stdarg.h>
#include <stdbool.h>

/*============================ MACROS ========================================*/

/*============================ MACROFIED FUNCTIONS ===========================*/
//! @{  example：
/*      byte_queue_t
//============================ TYPES =========================================
declare_class(byte_queue_t)

def_class(byte_queue_t, which(inherit(queue_t)) )

end_def_class(byte_queue_t, which(inherit(queue_t)))

//============================ IMPLEMENTATION ================================
class_derived_cfg(byte_queue_t, queue_t)

implement_constructor(byte_queue_t)

    constructor_body(
        
        // 读取参数列表，类型和顺序跟调用方法要一一要对应。
        read_param(uint8_t*, pchBuffer);
        read_param(uint16_t, hwSize);

        // 1、调用父类构造方法
        base_constructor(byte_queue_t, base_obj(queue_t), pchBuffer, hwSize);
                     
        // 2、构造当     
        this_protected(queue_t)->hwItemSize = 1;
        ........
    )

implement_destructors(byte_queue_t)

    destructors_body(
        // 1、析构当前类
        .......
        
        // 2、调用父类析构，析构父类
        base_destructors(byte_queue_t, queue_t);
    )
*/
//! @}

//! @{  destructors
#define declare_destructors(__type)     static void destructors(__type *ptObj);
#define __implement_destructors(__type)                     \
        static void destructors(__type *ptObj)              \
        {                                                   \
            class(__type) *ptThis = (class(__type) *)ptObj;
#define implement_destructors(__type)   __implement_destructors(__type)

#define __destructors_body(...)                             \
            __VA_ARGS__                                     \
        }
#define destructors_body(...)           __destructors_body(__VA_ARGS__)\
//! @}

//! @{  constructor
#define declare_constructor(__type)     static void constructor(__type *ptObj, va_list *ptArg);
#define __implement_constructor(__type)                     \
        static void constructor(__type *ptObj, va_list *ptArg)\
        {                                                   \
            class(__type) *ptThis = (class(__type) *)ptObj; \
            if (NULL == ptThis) {                           \
                return;                                     \
            }                                               \
            *((Object **)ptObj) = (Object *)(&(c_##__type##TypeObj));
#define implement_constructor(__type)   __implement_constructor(__type)

#define __constructor_body(...)                             \
            __VA_ARGS__                                     \
        }
#define constructor_body(...)           __constructor_body(__VA_ARGS__)\
//! @}
 
//! @{  初始化 class
#define define_derived_type(__type, __super)                \
        extern type_t c_##__super##TypeObj;                 \
        type_t c_##__type##TypeObj = {                      \
            .ptBase = &c_##__super##TypeObj,                \
            .constructor = (constructor_fn*)constructor,    \
            .destructors = (destructors_fn*)destructors     \
        };

#define define_abstract_type(__type)                        \
        type_t c_##__type##TypeObj = {                      \
            .ptBase = NULL,                                 \
            .constructor = (constructor_fn*)constructor,    \
            .destructors = (destructors_fn*)destructors     \
        };

#define class_derived_cfg(__type, __base_type)              \
        declare_constructor(__type)                         \
        declare_destructors(__type)                         \
        define_derived_type(__type, __base_type)

#define class_abstract_cfg(__type)                          \
        declare_constructor(__type)                         \
        declare_destructors(__type)                         \
        define_abstract_type(__type)
//! @}

//! @{ 构造析构方法调用
#define __super_type_obj(__type)          ((c_##__type##TypeObj.ptBase))

#define __base_constructor(__type, ...)                     \
        do {                                                \
            constructor_fn *ptConstructor = __super_type_obj(__type)->constructor;\
            wrapper(ptConstructor, __VA_ARGS__);            \
        }while(0);
#define base_constructor(__type, ...)   __base_constructor(__type, __VA_ARGS__)

#define __base_destructors(__type, __obj)                  \
        do {                                               \
            destructors_fn *ptDestructors = __super_type_obj(__type)->destructors;\
            ptDestructors(__obj);                          \
        }while(0);
#define base_destructors(__type, __base_type)   __base_destructors(__type, base_obj(__base_type))

#define this_constructor(...)           wrapper(constructor, __VA_ARGS__)
#define this_destructors(__obj)         destructors(__obj)

#define this_interface(__interface)     convert_obj_as(this, __interface)
#define this_protected(__type)          type_convert(ref_obj_as(this, protected(__type)), protected_content(__type))
#define base_obj(__type)                ref_obj_as(this, __type)

#define read_param(__type, __param)     __type __param = va_arg(*ptArg, __type) // 堆栈中读取一个参数
//! @}


#define typeof(__TYPE)                  &(c_##__TYPE##TypeObj)


// 弃用
#define base_protected(__base_type)     ((protected_content(__base_type) *)(ref_obj_as( obj_convert_as(this, __base_type), protected(__base_type))))
/*============================ TYPES =========================================*/
//! @{ 类型定义
typedef void constructor_fn(void *ptObject, va_list *ptArg);
typedef void destructors_fn(void *ptObject);
typedef const struct _type_t type_t;
struct _type_t {
    type_t *ptBase;
    constructor_fn *constructor;
    destructors_fn *destructors;
};
typedef type_t Object ;
//! @}

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/ 
extern void wrapper(constructor_fn *fnFunction, ...);
extern Object* is_type_of(void *ptObj);                 // root base
extern bool is_type_equal(void *ptObjL, void *ptObjR);

#endif /* oopc_eh_h */
