//
//  test4B.c
//  training
//
//  Created by zhaoli on 2017/8/25.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

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
typedef bool post_handler_fn(msg_block_t* ptObj, void* pchChar);
typedef bool open_handler_fn(msg_block_t* ptObj, void* pchChar);

/**
 define fsm `check_world`

 @return
 */
simple_fsm(check_world)

/**
 define fsm test4B,

 @param test4B fsm
 @param print_hello
 @return
 */
simple_fsm(test4B_check,
    def_params(
        uint8_t chChar;
        uint8_t chEchoCache;
        void* pTag;                //绑定事件处理函数的数据源对象。
        post_handler_fn *fnPost;
        fsm(check_world) fsmCheck_world;
    ))

/**
 define fsm `test4B_echo` 
 
 @return
 */
simple_fsm(test4B_echo,
    def_params(
        uint8_t chEcho;
        void* pTag;                //绑定事件处理函数的数据源对象。
        open_handler_fn *fnOpen;
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

/*============================ GLOBAL VARIABLES ==============================*/
static fsm(test4B_check) s_fsmTest4BCheck;
static fsm(test4B_print) s_fsmTest4BPrint;
static fsm(test4B_echo) s_fsmTest4BEcho;


/*============================ LOCAL VARIABLES ===============================*/
// event: check word successed
event_t s_tEventCheckSuccessed;
event_t s_tEventCheckSuccessedACK;

/*============================ PROTOTYPES ====================================*/
/*============================ FSM_initialiser ================================*/
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
fsm_initialiser(test4B_print)
    init_body()

/**
 define fsm initialiser

 @param test4B
 @return
 */
fsm_initialiser(test4B_check, args(
        msg_block_t* ptMSG,
        post_handler_fn* fnHandler
    ))

    init_body(

        if ((NULL == ptMSG) || (NULL == fnHandler) ) {
            abort_init();
        }

        this.pTag = ptMSG;
        this.fnPost = fnHandler;
    )

fsm_initialiser(test4B_echo, args(
        msg_block_t* ptMSG,
        open_handler_fn *fnHandler
    ))

    init_body(
          
        if ((NULL == ptMSG) || (NULL == fnHandler) ) {
            abort_init();
        }
        this.pTag = ptMSG;
        this.fnOpen = fnHandler;
    )

/*============================ IMPLEMENTATION ================================*/
fsm_implementation(test4B_echo)

    def_states( WAIT_MAIL, ECHO )

    body(

        state(WAIT_MAIL,
            
            if (!this.fnOpen(this.pTag, &this.chEcho)) { // 调用 open
                fsm_on_going();
            }
              
            update_state_to(ECHO);
        )
         
        state(ECHO,
          if (!WAIT_EVENT(&s_tEventCheckSuccessed)) {
              if (serial_out(this.chEcho)) {
                  fsm_cpl();
              }
          }
               
          fsm_on_going();
        )
    )

/**
 fsm implement test4B,when input 'world',then out 'hello'
 
 @param test4B
 @return
 */
fsm_implementation(test4B_check)

    def_states( GET_CHAR, CHECK, WAIT_AND_SETEVENT )

    body(

        on_start(
            init_fsm(check_world, &(this.fsmCheck_world));
        )

        state(GET_CHAR,
            if ( !SERIAL_IN(&(this.chChar)) ) {
                fsm_on_going();
            }

            this.chEchoCache = this.chChar;
            
            if (NULL != this.fnPost) {
                this.fnPost(this.pTag, &(this.chEchoCache));
            }
            
            update_state_to(CHECK);
        )

        state(CHECK,
            if (fsm_rt_cpl == call_fsm(check_world, &(this.fsmCheck_world), args(this.chChar))) {
                update_state_to(WAIT_AND_SETEVENT);
            } else {
                transfer_to(GET_CHAR);
            }
        )

        state(WAIT_AND_SETEVENT,
            if (WAIT_EVENT(&s_tEventCheckSuccessedACK)) {
                SET_EVENT(&s_tEventCheckSuccessed);
                fsm_cpl();
            }

            fsm_on_going();
        )
  )

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
fsm_implementation(test4B_print)

    def_states( WAIT_EVENT, PRINT_HELLO )

    body(

        state(WAIT_EVENT,
            if (!WAIT_EVENT(&s_tEventCheckSuccessed)) {
                fsm_on_going();
            }

            init_fsm(print_hello, &(this.fsmPrintHello));
            update_state_to(PRINT_HELLO);
        )
         
        state(PRINT_HELLO,
              if (fsm_rt_cpl == call_fsm(print_hello, &(this.fsmPrintHello))) {
                  RESET_EVENT(&s_tEventCheckSuccessed);
                  SET_EVENT(&s_tEventCheckSuccessedACK);
                fsm_cpl();
            }

            fsm_on_going();
        )
    )   

/**
 init task test4B
 */
void init_test4B(void)
{
    INIT_EVENT(&s_tEventCheckSuccessed, false, MANUAL);
    INIT_EVENT(&s_tEventCheckSuccessedACK, true, AUTOSET);

    
    init_fsm(test4B_print, &s_fsmTest4BPrint);
    
    static msg_block_t s_tMsg;
    msg_init(&s_tMsg);

    init_fsm(test4B_check, &s_fsmTest4BCheck,
        args(
            &s_tMsg, msg_post
        ));

    init_fsm(test4B_echo, &s_fsmTest4BEcho, 
        args(
             &s_tMsg, msg_open
        ));
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
