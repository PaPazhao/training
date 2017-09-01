//
//  test4A.c
//  training
//
//  Created by zhaoli on 2017/8/25.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

/*============================ INCLUDES ======================================*/
#include "./app_cfg.h"

/*============================ MACROS ========================================*/
#ifndef SERIAL_IN
#define SERIAL_IN(__BYTE)  serial_in(__BYTE)
#endif

#ifndef WAIT_EVENT
#define WAIT_EVENT(__EVENT)  wait_event(__EVENT)
#endif

#ifndef SET_EVENT
#define SET_EVENT(__EVENT)   set_event(__EVENT)
#endif

#ifndef INIT_EVENT
#define INIT_EVENT(__EVENT, __EVENT_VALUE, __MANUAL)    \
init_event(__EVENT,__EVENT_VALUE,__MANUAL)
#endif


/*============================ MACROFIED FUNCTIONS ===========================*/

/**
 define fsm `check_world`

 @return
 */
simple_fsm(check_world)


/**
 define fsm test4A,

 @param test4A fsm
 @param print_hello
 @return
 */
simple_fsm(test4A_check,
    def_params(
        uint8_t chChar;
        fsm(check_world) fsmCheck_world;
    ))

/**
 define fsm `test4A_print` when s_tCheckOver event is set print `hello`
 
 @return
 */
simple_fsm(test4A_print,
    def_params(
        fsm(print_hello) fsmPrintHello;
    ))

/*============================ TYPES =========================================*/

extern bool serial_in(uint8_t *pchByte);
extern void init_event(event_t *ptEvent,bool bInitValue,even_model_t tModel);
extern void set_event(event_t *ptEvent);
extern bool wait_event(event_t *ptEvent);

extern_fsm_implementation(check_world, args(uint8_t chByte));
extern_fsm_implementation(test4A_print);
extern_fsm_implementation(test4A_check);

/*============================ GLOBAL VARIABLES ==============================*/

/*============================ LOCAL VARIABLES ===============================*/
static event_t s_tCheckOver;
static fsm(test4A_check) s_fsmTest4ACheck;
static fsm(test4A_print) s_fsmTest4APrint;

/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

/**
 define fsm initialiser

 @param test4A
 @return
 */
fsm_initialiser(test4A_check)
    init_body()


/**
 define fsm check_world,check 'world'

 @param check name
 @return
 */
fsm_initialiser(check_world)
    init_body()

/**
 define fsm check_world,check 'world'
 
 @param check name
 @return
 */
fsm_initialiser(test4A_print)
    init_body()

/**
 fsm implement test4a,when input 'world',then out 'hello'

 @param test4A
 @return
 */
fsm_implementation(test4A_check)
    
    def_states( GET_CHAR, CHECK )

    body(

        on_start(
            init_fsm(check_world, &(this.fsmCheck_world));
        )

        state(GET_CHAR,
            if ( !SERIAL_IN(&(this.chChar)) ) {
                fsm_on_going();
            }
 
            transfer_to(CHECK);
        )
         
        state(CHECK,
            if (fsm_rt_cpl == call_fsm(check_world, &(this.fsmCheck_world), args(this.chChar))) {
                SET_EVENT(&s_tCheckOver);
                fsm_cpl();
            } else {
                transfer_to(GET_CHAR);
            }
        )  
    )

/**
 implementation fsm check,check input 'world'
 
 @param test4A
 @return
 */
fsm_implementation(check_world, args(uint8_t chByte))

    def_states(CHECK_W, CHECK_O, CHECK_R, CHECK_L, CHECK_D)

    body(
 
        state(CHECK_W,
            if ('W' != chByte) {
                transfer_to(CHECK_W);
            }
            
            transfer_to(CHECK_O);
        )

        state(CHECK_O,

            if ('O' != chByte) {
                transfer_to(CHECK_W);
            }

            transfer_to(CHECK_R);
        )

        state(CHECK_R,

            if ('R' != chByte) {
                transfer_to(CHECK_W);
            }

            transfer_to(CHECK_L);
        )

        state(CHECK_L,

            if ('L' != chByte) {
                transfer_to(CHECK_W);
            }

            transfer_to(CHECK_D);
        )

        state(CHECK_D,

            if ('D' != chByte) {
                transfer_to(CHECK_W);
            }

            fsm_cpl();
        )
    )


/**
 fsm implement test4a,when input 'world',then out 'hello'
 
 @param test4A
 @return
 */
fsm_implementation(test4A_print)

    def_states( WAIT_EVENT, PRINT_HELLO )

    body(
        state(WAIT_EVENT,
            if (!WAIT_EVENT(&s_tCheckOver)) {
                fsm_on_going();
            }
              
            init_fsm(print_hello, &(this.fsmPrintHello));
            transfer_to(PRINT_HELLO);
        )
         
        state(PRINT_HELLO,
            if (fsm_rt_cpl == call_fsm(print_hello, &(this.fsmPrintHello))) {
                fsm_cpl();
            }

            fsm_on_going();
        )
    )

/**
 init task test4A
 */
void init_test4A(void) {
    init_fsm(test4A_check, &s_fsmTest4ACheck);
    init_fsm(test4A_print, &s_fsmTest4APrint);
    INIT_EVENT(&s_tCheckOver, false, AUTOSET);
}

/**
 task test4A
 */
void test4A(void) {
    call_fsm(test4A_check, &(s_fsmTest4ACheck));
    call_fsm(test4A_print, &(s_fsmTest4APrint));
}

/* EOF */
