//
//  test1A.h
//  State
//
//  Created by zhaoli on 2017/8/23.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef __TEST_1A_H__
#define __TEST_1A_H__

/*============================ INCLUDES ======================================*/
#include "./app_cfg.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/**
 define fsm print_hello

 @param print_hello fsm name
 @return fsm state
 */
extern_simple_fsm(print_hello)

/**
 fsm print_hello initialiser

 @param print_hello
 @return 
 */
extern_fsm_initialiser(print_hello)

/**
 print hello delay 1s

 @param print_hello fsm name
 @return fsm state
 */
extern_fsm_implementation(print_hello)

#endif /* test1A_h */
/* EOF */
