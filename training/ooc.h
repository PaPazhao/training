/***************************************************************************
 *   Copyright(C)2009-2012 by Gorgon Meducer<Embedded_zhuoran@hotmail.com> *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef __OBJECT_ORIENTED_C_H__
#define __OBJECT_ORIENTED_C_H__

/*============================ INCLUDES ======================================*/
#include <stdint.h>

/*! \NOTE the uint_fast8_t used in this header file is defined in stdint.h 
          if you don't have stdint.h supported in your toolchain, you should
          define uint_fast8_t all by yourself with following rule:
          a. if the target processor is 8 bits, define it as uint8_t
          b. if the target processor is 16 bits, define it as uint16_t 
          c. if the target processor is 32 bits, define it as uint32_t
          d. if the target processor is 64 bits, define it as either uint32_t or uint64_t
 */

/*============================ MACROS ========================================*/



/* -----------------  Start of section using anonymous unions  -------------- */
#if defined(__CC_ARM)
  //#pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
/* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler type
#endif


#ifndef this
#   define this        (*ptThis)
#endif

/*============================ MACROFIED FUNCTIONS ===========================*/

#define __CLASS(__NAME)             __##__NAME
#define CLASS(__NAME)               __CLASS(__NAME)

//! \brief macro for initializing an event
#define INIT_DELEGATE(__NAME/*,__ASYN*/)           delegate_init(&(__NAME)/*, (__ASYN)*/)


 

#define DECLARE_CLASS(__NAME)                   \
     typedef union __NAME __NAME;                

#define __DEF_CLASS(__NAME,...)                 \
    /*typedef union __NAME __NAME;  */          \
    typedef struct __##__NAME __##__NAME;       \
    struct __##__NAME {                         \
        __VA_ARGS__
#define DEF_CLASS(__NAME, ...)      __DEF_CLASS(__NAME, __VA_ARGS__)

          
#define __END_DEF_CLASS(__NAME, ...)            \
    };                                          \
    union __NAME {                              \
        __VA_ARGS__                             \
        uint_fast8_t __NAME##__chMask[(sizeof(__##__NAME) + sizeof(uint_fast8_t) - 1) / sizeof(uint_fast8_t)];\
    };
#define END_DEF_CLASS(__NAME, ...)  __END_DEF_CLASS(__NAME, __VA_ARGS__)

/*! \brief macro for initializing class in compiler-time
 *! \param __TYPE class name
 *! \param __OBJ target object
 *! \param ... initialization list
 */
#define __INIT_CLASS_OBJ(__TYPE, __OBJ, ...)        \
            union {                                 \
                CLASS(__TYPE) __##__OBJ;            \
                __TYPE   __OBJ;                     \
            } = {                                   \
                .__##__OBJ = __VA_ARGS__,           \
            }
#define INIT_CLASS_OBJ(__TYEP, __OBJ, ...)          \
            __INIT_CLASS_OBJ(__TYPE, __OBJ, __VA_ARGS__)

#define __EXTERN_CLASS_OBJ( __TYPE, __OBJ )         \
            extern union {                          \
                CLASS(__TYPE) __##__OBJ;            \
                __TYPE   __OBJ;                     \
            };
#define EXTERN_CLASS_OBJ(__TYPE, __OBJ)             \
            __EXTERN_CLASS_OBJ( __TYPE, __OBJ )


#define __EXTERN_CLASS(__NAME,...)                  \
    /*typedef union __NAME __NAME; */               \
    union __NAME {                                  \
        __VA_ARGS__                                 \
        uint_fast8_t __NAME##__chMask[(sizeof(struct{\
        __VA_ARGS__
#define EXTERN_CLASS(__NAME, ...)   __EXTERN_CLASS(__NAME, __VA_ARGS__)

#define END_EXTERN_CLASS(__NAME, ...)               \
        }) + sizeof(uint_fast8_t) - 1) / sizeof(uint_fast8_t)];\
    };


//! \name interface definition
//! @{
#define DEF_INTERFACE(__NAME,...)                   \
            typedef struct __NAME __NAME;           \
            __VA_ARGS__                             \
            struct __NAME {

#define END_DEF_INTERFACE(__NAME)                   \
            };
//! @}

//! \name structure definition
//! @{
#define DEF_STRUCTURE(__NAME,...)                   \
            typedef struct __NAME __NAME;           \
            __VA_ARGS__                             \
            struct __NAME {

#define END_DEF_STRUCTURE(__NAME)                   \
            };
//! @}


//! \brief macro for inheritance

#define INHERIT_EX(__TYPE, __NAME)  \
            union {                 \
                __TYPE  __NAME;     \
                __TYPE;             \
            };

/*! \note When deriving a new class from a base class, you should use INHERIT 
 *        other than IMPLEMENT, although they looks the same now.
 */
#define __INHERIT(__TYPE)           INHERIT_EX(__TYPE, base__##__TYPE)
#define INHERIT(__TYPE)             __INHERIT(__TYPE)

/*! \note You can only use IMPLEMENT when defining INTERFACE. For Implement 
 *        interface when defining CLASS, you should use DEF_CLASS_IMPLEMENT 
 *        instead.
 */
#define __IMPLEMENT(__INTERFACE)    INHERIT_EX(__INTERFACE, base__##__INTERFACE)
#define IMPLEMENT(__INTERFACE)      __IMPLEMENT(__INTERFACE)  

/*! \note if you have used INHERIT or IMPLEMENT to define a CLASS / INTERFACE, 
          you can use OBJ_CONVERT_AS to extract the reference to the inherited 
          object. 
  \*/
#define __OBJ_CONVERT_AS(__OBJ, __INTERFACE)    (__OBJ.base__##__INTERFACE)
#define OBJ_CONVERT_AS(__OBJ, __INTERFACE)      __OBJ_CONVERT_AS(__OBJ, __INTERFACE)          

#define __REF_OBJ_AS(__OBJ, __TYPE)             (&(__OBJ.base__##__TYPE))
#define REF_OBJ_AS(__OBJ, __TYPE)               __REF_OBJ_AS(__OBJ, __TYPE)

#define REF_INTERFACE(__INTERFACE)      const __INTERFACE *ptMethod;
           

/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/


#endif
/* EOF */
