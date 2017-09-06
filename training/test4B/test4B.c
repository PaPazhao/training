//
//  test4B.c
//  training
//
//  Created by zhaoli on 2017/8/25.
//  Copyright © 2017年 zhaoli. All rights reserved.
//
#include "test4B.h"
/*============================ INCLUDES ======================================*/
#include "./app_cfg.h"

/*============================ MACROS ========================================*/
#ifndef SERIAL_IN
#define SERIAL_IN(__BYTE)               serial_in(__BYTE)
#endif

#ifndef SERIAL_OUT
#define SERIAL_OUT(__BYTE)              serial_out(__BYTE)
#endif

#ifndef WAIT_EVENT
#define WAIT_EVENT(__EVENT)             wait_event(__EVENT)
#endif

#ifndef SET_EVENT
#define SET_EVENT(__EVENT)              set_event(__EVENT)
#endif

#ifndef INIT_EVENT
#define INIT_EVENT(__EVENT, __EVENT_VALUE, __MANUAL)    \
init_event(__EVENT,__EVENT_VALUE,__MANUAL)
#endif

#ifndef WAIT_EVENT
#define WAIT_EVENT(__EVENT)             wait_event(__EVENT)
#endif

#ifndef SET_EVENT
#define SET_EVENT(__EVENT)              set_event(__EVENT)
#endif

#ifndef INIT_EVENT
#define (__EVENT, __EVENT_VALUE, __MANUAL)    \
init_event(__EVENT,__EVENT_VALUE,__MANUAL)
#endif

/*============================ MACROFIED FUNCTIONS ===========================*/

/**
 define fsm `check_world`

 @return
 */
simple_fsm(check_world)

/**
 define fsm `test4B_echo`

 @return
 */
simple_fsm(test4B_echo,
    def_params(
        uint8_t chEcho;
    ))

/**
 define fsm test4B,

 @param test4B fsm
 @param print_hello
 @return
 */
simple_fsm(test4B_check,
    def_params(
        uint8_t chChar;
        fsm(check_world) fsmCheck_world;
    ))

/**
 define fsm `test4B_print` when s_tCheckOver event is set print `hello`
 
 @return
 */
simple_fsm(test4B_print,
    def_params(
        fsm(print_hello) fsmPrintHello;
    ))

/*============================ TYPES =========================================*/
extern bool serial_out(uint8_t chByte);
extern bool serial_in(uint8_t *pchByte);
extern void init_event(event_t *ptEvent,bool bInitValue,even_model_t tModel);
extern void set_event(event_t *ptEvent);
extern bool wait_event(event_t *ptEvent);

extern_fsm_implementation(check_world, args(uint8_t chByte));
extern_fsm_implementation(test4B_print);
extern_fsm_implementation(test4B_check);
extern_fsm_implementation(test4B_echo);

/*============================ GLOBAL VARIABLES ==============================*/

/*============================ LOCAL VARIABLES ===============================*/
static fsm(test4B_check) s_fsmTest4BCheck;
static fsm(test4B_print) s_fsmTest4BPrint;
static fsm(test4B_echo) s_fsmTest4BEcho;
static uint8_t *s_pchChar = NULL;

// event: check word successed
static event_t s_tEventCheckSuccessed;

/*============================ PROTOTYPES ====================================*/
/**
 init task test4B
 */
void init_test4B(void);

/**
 task test4B
 */
void tedst4B(void);
#define  PRN(...) printf(__VA_ARGS__)
/*============================ FSM_initialiser ================================*/
/**
 define fsm check_world,check 'world'

 @param check name
 @return
 */
fsm_initialiser(check_world)
    init_body()

/**
 define fsm initialiser

 @param test4B
 @return
 */
fsm_initialiser(test4B_check)
    init_body()

/**
 define fsm test4B_echo,echo serial in char

 @param test4B_echo
 @return
 */
fsm_initialiser(test4B_echo)
    init_body()

/**
 define fsm check_world,check 'world'
 
 @param check name
 @return
 */
fsm_initialiser(test4B_print)
    init_body()


/*============================ IMPLEMENTATION ================================*/
/**
 implementation fsm check,check input 'world'
 
 @param test4B
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
 fsm implement test4B,when input 'world',then out 'hello'

 @param test4B
 @return
 */
fsm_implementation(test4B_check)
    
    def_states( GET_CHAR, CHECK,WAIT_AND_SETEVENT )

    body(

        on_start(
            init_fsm(check_world, &(this.fsmCheck_world));
                 PRN("\r\n test4B_check    test4B_check: 1 - SERIAL_IN wait");
        )

        state(GET_CHAR,
            if ( !SERIAL_IN(&(this.chChar)) ) {
                fsm_on_going();
            }
            s_pchChar = &this.chChar;
 
              PRN("\r\n test4B_check    test4B_check: 2 - SERIAL_IN %c start to check", *s_pchChar);
            update_state_to(CHECK);
        )
         
        state(CHECK,
            if (fsm_rt_cpl == call_fsm(check_world, &(this.fsmCheck_world), args(this.chChar))) {
                PRN("\r\n test4B_check    test4B_check: 3 - CHECK over, wait evet reset");
                update_state_to(WAIT_AND_SETEVENT);
            } else {
                transfer_to(GET_CHAR);
            }
        )

        state(WAIT_AND_SETEVENT,
            if (!WAIT_EVENT(&s_tEventCheckSuccessed)) {
                
                SET_EVENT(&s_tEventCheckSuccessed);
                PRN("\r\n test4B_check    test4B_check: 4 - SET_EVENT over");
                fsm_cpl();
            }

            fsm_on_going();
        )
    )

/**
 fsm implement test4B,when input 'world',then out 'hello'
 
 @param test4B
 @return
 */
fsm_implementation(test4B_print)

    def_states( WAIT_EVENT, PRINT_HELLO )

    body(
         on_start(
         PRN("\r\n test4B_print        test4B_print: 1 - wait event");
         )
        state(WAIT_EVENT,
            if (!WAIT_EVENT(&s_tEventCheckSuccessed)) {
                fsm_on_going();
            }
            PRN("\r\n test4B_print        test4B_print: 2 - PRINT_HELLO start\r\n");
            init_fsm(print_hello, &(this.fsmPrintHello));
            update_state_to(PRINT_HELLO);
        )
         
        state(PRINT_HELLO,
            if (fsm_rt_cpl == call_fsm(print_hello, &(this.fsmPrintHello))) {
                RESET_EVENT(&s_tEventCheckSuccessed);
                PRN("\r\n test4B_print        test4B_print: 2 - PRINT_HELLO over");
                fsm_cpl();
            }

            fsm_on_going();
        )
    )   

fsm_implementation(test4B_echo)

    def_states( WAIT_MAIL, ECHO )
    
    body(
         on_start(
         PRN("\r\n test4B_echo            test4B_echo: 1 - wait mail");
         )
        state(WAIT_MAIL,
 
            if (NULL == s_pchChar) {
                fsm_on_going();
            }

              PRN("\r\n test4B_echo            test4B_echo: 2 - event is set, waitng....");
            this.chEcho = *s_pchChar;
            update_state_to(ECHO);
              printf("       event - is - set -- ..................\r\n");
        )

        state(ECHO,
            if (!WAIT_EVENT(&s_tEventCheckSuccessed)) {
                
                if (SERIAL_OUT(this.chEcho)) {
                    printf(" --- SERIAL_OUT `%c`\r\n",this.chEcho);
                    s_pchChar = NULL;
                    fsm_cpl();
                }
            }
            
            fsm_on_going();
        )
    )

/**
 init task test4B
 */
void init_test4B(void)
{
    init_fsm(test4B_check, &s_fsmTest4BCheck);
    init_fsm(test4B_print, &s_fsmTest4BPrint);
    init_fsm(test4B_echo, &s_fsmTest4BEcho);
    
    INIT_EVENT(&s_tEventCheckSuccessed, false, MANUAL);
}

/**
 task test4B
 */
void test4B(void)
{
    call_fsm(test4B_check, &(s_fsmTest4BCheck));
    call_fsm(test4B_print, &(s_fsmTest4BPrint));
    call_fsm(test4B_echo, &(s_fsmTest4BEcho));
}

/* EOF */
