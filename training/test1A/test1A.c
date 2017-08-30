//
//  test1A.c
//  State
//
//  Created by zhaoli on 2017/8/23.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

/*============================ INCLUDES ======================================*/
#include "./app_cfg.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
#ifndef SERIAL_OUT
#define SERIAL_OUT(__BYTE)  serial_out(__BYTE)
#endif

/*============================ TYPES =========================================*/

/**
 Description

 @param chByte chByte description
 @return return value description
 */
extern bool serial_out(uint8_t chByte);

/*============================ GLOBAL VARIABLES ==============================*/

/*============================ LOCAL VARIABLES ===============================*/

/*============================ PROTOTYPES ====================================*/
simple_fsm(print_hello,
    def_params(
        fsm(delay_1s) fsmDelay;
    ))

/*============================ IMPLEMENTATION ================================*/


/**
 define the fsm initialiser for FSML delay_1s

 @param print_hello
 @return return value description
 */
fsm_initialiser(print_hello)
    init_body()

 /**
 Implement the fsm: print_hello

 @param print_hello print_hello description
 @return return value description
 */
fsm_implementation(print_hello)
    def_states(
        PRINT_H,
        PRINT_E,
        PRINT_L,
        PRINT_L_2,
		PRINT_O,
		PRINT_R,
		PRINT_N,
		DELAY)

    body(
        state(PRINT_H,
            if (!SERIAL_OUT('H')) {
                fsm_on_going();
            }

            update_state_to(PRINT_E)
        )

        state(PRINT_E,
            if (!SERIAL_OUT('E')) {
                fsm_on_going();
            }
            update_state_to(PRINT_L)
        )

        state(PRINT_L,
            if (!SERIAL_OUT('L')) {
                fsm_on_going();
            }
            update_state_to(PRINT_L_2)
        )

        state(PRINT_L_2,
            if (!SERIAL_OUT('L')) {
                fsm_on_going();
            }

            update_state_to(PRINT_O)
        )

        state(PRINT_O,
            if (!SERIAL_OUT('O')) {
                fsm_on_going();
            }

            update_state_to(PRINT_R)
        )

        state(PRINT_R,
            if (!SERIAL_OUT('\r')) {
                fsm_on_going();
            }

            update_state_to(PRINT_N)
        )

        state(PRINT_N,
            if (!SERIAL_OUT('\n')) {
                fsm_on_going();
            }

            init_fsm(delay_1s, &(this.fsmDelay));
            update_state_to(DELAY)
        )

        state(DELAY,
            if (fsm_rt_cpl == call_fsm(delay_1s, &(this.fsmDelay) )) {
                fsm_cpl();
            }

            fsm_on_going();
        )
    )
/* EOF */
