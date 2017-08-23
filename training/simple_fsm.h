/***************************************************************************
 *   Copyright(C)2016-2017 by Gorgon Meducer<Embedded_zhuoran@hotmail.com> *
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

#ifndef __SIMPLE_FSM_H__
#define __SIMPLE_FSM_H__

/*============================ INCLUDES ======================================*/
/*============================ MACROS ========================================*/


#ifndef this
#   define this    (*ptThis)
#endif

/*============================ MACROFIED FUNCTIONS ===========================*/
#define def_states(...)                                             \
enum {                                                      \
START = 0,                                              \
__VA_ARGS__                                             \
};

#define def_params(...)         __VA_ARGS__

#define args(...)               ,__VA_ARGS__

#define __fsm(__NAME)           fsm_##__NAME##_t
#define fsm(__NAME)             __fsm(__NAME)

#define __simple_fsm(__FSM_TYPE, ...)                               \
DECLARE_CLASS(__FSM_TYPE)                                   \
DEF_CLASS(__FSM_TYPE)                                       \
uint_fast8_t chState;                                   \
__VA_ARGS__                                             \
END_DEF_CLASS(__FSM_TYPE)

#define simple_fsm(__NAME, ...)                                     \
__simple_fsm(fsm(__NAME), __VA_ARGS__)

#define __extern_simple_fsm(__FSM_TYPE, ...)                        \
DECLARE_CLASS(__FSM_TYPE)                                   \
EXTERN_CLASS(__FSM_TYPE)                                    \
uint_fast8_t chState;                                   \
__VA_ARGS__                                             \
END_EXTERN_CLASS(__FSM_TYPE)



#define extern_simple_fsm(__NAME, ...)                                          \
__extern_simple_fsm(fsm(__NAME), __VA_ARGS__)

/*! \brief extern fsm initialisation function and provide function prototye
 as <__NAME>_fn, E.g
 extern_fsm_initialiser( demo_fsm );
 we extern a function called:
 extern fsm_demo_fsm_t *demo_fsm_init( fsm_demo_fsm_t *ptFSM );
 and a prototype definition:
 typedef fsm_demo_fsm_t *demo_fsm_init_fn( fsm_demo_fsm_t *ptFSM );
 We can then use demo_fsm_init_fn to define function pointer
 */
#define __extern_fsm_initialiser(__NAME, ...)                                   \
typedef fsm(__NAME) *__NAME##_init_fn(fsm(__NAME) *ptFSM __VA_ARGS__);  \
extern  fsm(__NAME) *__NAME##_init(fsm(__NAME) *ptFSM __VA_ARGS__);
#define extern_fsm_initialiser(__NAME, ...)                                     \
__extern_fsm_initialiser(__NAME, __VA_ARGS__)

/*! \brief extern fsm task function and provide function prototye as <__NAME>_fn, E.g
 extern_fsm_implementation( demo_fsm );
 we extern a function called:
 fsm_rt_t demo_fsm( fsm_demo_fsm_t *ptFSM )
 and a prototype definition:
 typedef fsm_rt_t demo_fsm_fn (fsm_demo_fsm_t *ptFSM);
 We can then use demo_fsm_fn to define function pointer
 */
//!@{
#define __extern_fsm_implementation(__NAME, ...)                                \
typedef fsm_rt_t __NAME##_fn( fsm(__NAME) *ptFSM __VA_ARGS__ );         \
extern fsm_rt_t __NAME( fsm(__NAME) *ptFSM __VA_ARGS__ );
#define extern_fsm_implementation(__NAME, ...)                                  \
__extern_fsm_implementation(__NAME, __VA_ARGS__)
//!@}

#define call_fsm(__NAME, __FSM, ...)                                            \
__NAME((__FSM) __VA_ARGS__)

#define state(__STATE, ...)                                                     \
case __STATE:                                                           \
{__VA_ARGS__;}

#define on_start(...)                       __VA_ARGS__


#define reset_fsm()         do { ptThis->chState = 0; } while(0);
#define fsm_cpl()           do {reset_fsm(); return fsm_rt_cpl;} while(0);
#define fsm_report(__CODE)  return (__ERROR);
#define fsm_on_going()      return fsm_rt_on_going;


#define update_state_to(__STATE)                                                \
{ ptThis->chState = (__STATE); }

#define transfer_to(__STATE)                                                    \
{ update_state_to(__STATE); fsm_on_going() }


#define fsm_initialiser(__NAME, ...)        __fsm_initialiser(__NAME, __VA_ARGS__)
#define __fsm_initialiser(__NAME, ...)                                          \
typedef fsm(__NAME) *__NAME##_init_fn(fsm(__NAME) *ptFSM __VA_ARGS__);  \
fsm(__NAME) *__NAME##_init(fsm(__NAME) *ptFSM __VA_ARGS__)              \
{                                                                       \
CLASS(fsm_##__NAME##_t) *ptThis = ( CLASS(fsm_##__NAME##_t) *)ptFSM;\
if (NULL == ptThis) {                                               \
return NULL;                                                    \
}                                                                   \
ptThis->chState = 0;

#define abort_init()     return NULL;

#define init_body(...)                                                          \
__VA_ARGS__                                                         \
return ptFSM;                                                       \
}


#define __init_fsm(__NAME, __FSM, ...)                                            \
__NAME##_init((__FSM) __VA_ARGS__)
#define init_fsm(__NAME, __FSM, ...)    __init_fsm(__NAME, __FSM, __VA_ARGS__)

#define fsm_implementation(__NAME, ...)                                         \
__implement_fsm(__NAME, __VA_ARGS__)

#define implement_fsm(__NAME, ...)      __implement_fsm(__NAME, __VA_ARGS__)
#define __implement_fsm(__NAME, ...)                                            \
typedef fsm_rt_t __NAME##_fn( fsm(__NAME) *ptFSM __VA_ARGS__ );             \
fsm_rt_t __NAME( fsm(__NAME) *ptFSM __VA_ARGS__ )                           \
{                                                                           \
CLASS(fsm_##__NAME##_t) *ptThis = (CLASS(fsm_##__NAME##_t) *)ptFSM;     \
if (NULL == ptThis) {                                                   \
return fsm_rt_err;                                                  \
}

#define body(...)                                                               \
switch (ptThis->chState) {                                              \
case 0:                                                             \
ptThis->chState++;                                              \
__VA_ARGS__                                                         \
}                                                                       \
\
return fsm_rt_on_going;                                                 \
}


/*============================ TYPES =========================================*/

#ifndef __FSM_RT_TYPE__
#define __FSM_RT_TYPE__
//! \name finit state machine state
//! @{
typedef enum {
    fsm_rt_err          = -1,    //!< fsm error, error code can be get from other interface
    fsm_rt_cpl          = 0,     //!< fsm complete
    fsm_rt_on_going     = 1,     //!< fsm on-going
    fsm_rt_wait_for_obj = 2,     //!< fsm wait for object
    fsm_rt_asyn         = 3,     //!< fsm asynchronose complete, you can check it later.
} fsm_rt_t;
//! @}

#endif

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/




#endif

/* EOF */

