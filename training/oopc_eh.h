//
//  oopc_eh.h
//  training
//
//  Created by zhaoli on 2017/10/16.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef __OOPC_EH_H__
#define __OOPC_EH_H__


#include <stdarg.h>
#include <stdbool.h>

 
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

//! @{  destructors
#define declare_destructors(__type)     static void destructors(__type *ptObj);
#define __implement_destructors(__type)                     \
        static void destructors(__type *ptObj)              \
        {                                                   \
            CLASS(__type) *ptThis = (CLASS(__type) *)ptObj;
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
            CLASS(__type) *ptThis = (CLASS(__type) *)ptObj; \
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
        do {                                                \
            destructors_fn *ptDestructors = __super_type_obj(__type)->destructors;\
            ptDestructors(__obj);                           \
        }while(0);
#define base_destructors(__type, __obj)   __base_destructors(__type, __obj)


#define this_constructor(...)           wrapper(constructor, __VA_ARGS__)
#define this_destructors(__obj)         destructors(__obj)
#define this_protected(__type)          OBJ_CONVERT_AS(this, INTERNAL_PROTECTED(__type))
#define this_interface(__interface)     OBJ_CONVERT_AS(this, __interface)
#define base_protected(__base_type)     REF_OBJ_AS(OBJ_CONVERT_AS(this, __base_type), INTERNAL_PROTECTED(__base_type))


// 堆栈中读取一个参数
#define read_param(__type, __param)     __type __param = va_arg(*ptArg, __type)
//! @}


#define typeof(__TYPE)       &(c_##__TYPE##TypeObj)
extern void wrapper(constructor_fn *fnFunction, ...);
extern Object* is_type_of(void *ptObj);                 // root base
extern bool is_type_equal(void *ptObjL, void *ptObjR);


#endif /* oopc_eh_h */
