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

#ifndef MAIL_INIT
#define MAIL_INIT(__MAIL)               mail_init(__MAIL)
#endif

#ifndef MAIL_OPEN
#define MAIL_OPEN(__MAIL)               mail_open(__MAIL)
#endif

#ifndef MAIL_POST
#define MAIL_POST(__MAIL, __OBJ)        mail_post(__MAIL, __OBJ)
#endif

#ifndef MAIL_IS_OPEN
#define MAIL_IS_OPEN(__MAIL)            mail_isOpen(__MAIL)
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
extern void mail_init(mail_t *pTarget);
extern void* mail_open(mail_t *pTarget);
extern void mail_post(mail_t *pTarget, void *tObj);
extern bool mail_isOpen(mail_t *pTarget);

extern_fsm_implementation(check_world, args(uint8_t chByte));
extern_fsm_implementation(test4B_print);
extern_fsm_implementation(test4B_check);
extern_fsm_implementation(test4B_echo);

/*============================ GLOBAL VARIABLES ==============================*/
#define PRT(...)   // printf(__VA_ARGS__)

/*============================ LOCAL VARIABLES ===============================*/

static fsm(test4B_check) s_fsmTest4BCheck;
static fsm(test4B_print) s_fsmTest4BPrint;
static fsm(test4B_echo) s_fsmTest4BEcho;

// critical check event
static critical_sector_t s_tCriticalEvent;

// mail: send to echo
static mail_t s_tMailEcho;

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
    
    def_states( GET_CHAR, CHECK, SEND_EVENT )

    body(

        on_start(
            init_fsm(check_world, &(this.fsmCheck_world));
        )

        state(GET_CHAR,
            if ( !SERIAL_IN(&(this.chChar)) ) {
                fsm_on_going();
            }
              
            MAIL_POST(&s_tMailEcho, &(this.chChar));
            PRT("\r\n1: MAIL_POST: isOpen:%d - obj: %c\r\n", s_tMailEcho.bIsOpen, *(uint8_t *)s_tMailEcho.pTarget);
            transfer_to(CHECK);
        )
         
        state(CHECK,
            if (fsm_rt_cpl == call_fsm(check_world, &(this.fsmCheck_world), args(this.chChar))) {
                transfer_to(SEND_EVENT);
            } else {
                transfer_to(GET_CHAR);
            }
        )

        state(SEND_EVENT,
            if (ENTER_CRITICAL_SECTOR(&s_tCriticalEvent)) {
                SET_EVENT(&s_tEventCheckSuccessed);
                PRT("\r\n1: SEND_EVENT: bAutoReset:%d - bIsSet: %d\r\n", s_tEventCheckSuccessed.bAutoReset, s_tEventCheckSuccessed.bIsSet);
                LEAVE_CRITICAL_SECTOR(&s_tCriticalEvent);
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

    def_states( WAIT_EVENT, PRINT_HELLO, RESET )

    body(

        state(WAIT_EVENT,
            if (!ENTER_CRITICAL_SECTOR(&s_tCriticalEvent)) {
                fsm_on_going();
            }

            if (!WAIT_EVENT(&s_tEventCheckSuccessed)) {
                LEAVE_CRITICAL_SECTOR(&s_tCriticalEvent);
                fsm_on_going();
            }
                
            LEAVE_CRITICAL_SECTOR(&s_tCriticalEvent);
            PRT("\r\n2: get event, ready to print Hello\r\n");
            init_fsm(print_hello, &(this.fsmPrintHello));
            transfer_to(PRINT_HELLO);
        )
         
        state(PRINT_HELLO,
            if (fsm_rt_cpl == call_fsm(print_hello, &(this.fsmPrintHello))) {
                update_state_to(RESET);
            }

            fsm_on_going();
        )

        state(RESET,
            if (ENTER_CRITICAL_SECTOR(&s_tCriticalEvent)) {
                RESET_EVENT(&s_tEventCheckSuccessed);
                PRT("\r\n2: print over reset event");
                LEAVE_CRITICAL_SECTOR(&s_tCriticalEvent);
                fsm_cpl();
            }
        )
    )   

fsm_implementation(test4B_echo)

    def_states( WAIT_MAIL, ECHO )
    
    body(

        state(WAIT_MAIL,
            if (MAIL_IS_OPEN(&s_tMailEcho)) {
                fsm_on_going();
            }
              PRT("\r\n3: GET MAIL: ready for echo");
            this.chEcho = *((uint8_t *)MAIL_OPEN(&s_tMailEcho));
            transfer_to(ECHO);
        )

        state(ECHO,
            if (!ENTER_CRITICAL_SECTOR(&s_tCriticalEvent)) {
                fsm_on_going();
            }

            if (!WAIT_EVENT(&s_tEventCheckSuccessed)) {
                if (SERIAL_OUT(this.chEcho)) {
                    PRT("\r\n3: -------ECHO-%c\r\n",this.chEcho);
                    LEAVE_CRITICAL_SECTOR(&s_tCriticalEvent); 
                    fsm_cpl();  
                }
            }

            LEAVE_CRITICAL_SECTOR(&s_tCriticalEvent); 
            fsm_on_going();
        )
    )
/**
 init task test4B
 */
void init_test4B(void) {
    init_fsm(test4B_check, &s_fsmTest4BCheck);
    init_fsm(test4B_print, &s_fsmTest4BPrint);
    init_fsm(test4B_echo, &s_fsmTest4BEcho);
    
    INIT_CRITICAL_SECTOR(&s_tCriticalEvent);
    INIT_EVENT(&s_tEventCheckSuccessed, false, MANUAL);
    MAIL_INIT(&s_tMailEcho);
}

/**
 task test4B
 */
void test4B(void) {
    call_fsm(test4B_check, &(s_fsmTest4BCheck));
    call_fsm(test4B_print, &(s_fsmTest4BPrint));
    call_fsm(test4B_echo, &(s_fsmTest4BEcho));
}

/* EOF */
