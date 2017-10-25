//
//  delegate.h
//  training
//
//  Created by zhaoli on 2017/9/20.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#ifndef delegate_h
#define delegate_h


#include <stdbool.h>
#include <stdint.h>
#include "simple_fsm.h"

//typedef fsm_rt_t delegate_handle_fn(void *pArg, void *pParam);
//typedef struct {
//    delegate_handle_fn *fnHandler;
//    void *pArg;
//} delegate_handle_t;
//
//typedef struct {
//    delegate_handle_t *ptEvent;
//} delegate_t;
//
//
///*! \brief initialize event
// *! \param ptEvent target event
// *! \return the address of event item
// */
//extern delegate_t *delegate_init(delegate_t *ptEvent);
//
///*! \brief initialize event handler item
// *! \param ptHandler the target event handler item
// *! \param fnRoutine event handler routine
// *! \param pArg handler extra arguments
// *! \return the address of event handler item
// */
//extern delegate_handle_t *delegate_handler_init( delegate_t *ptHandler, delegate_handle_fn *fnRoutine, void *pArg);
//
///*! \brief register event handler to specified event
// *! \param ptEvent target event
// *! \param ptHandler target event handler
// *! \return access result
// */
//extern bool register_delegate_handler(delegate_t *ptEvent, delegate_handle_t *ptHandler);
//
///*! \brief unregister a specified event handler
// *! \param ptEvent target event
// *! \param ptHandler target event handler
// *! \return access result
// */
//extern bool unregister_delegate_handler( delegate_t *ptEvent, delegate_handle_t *ptHandler);
//
///*! \brief raise target event
// *! \param ptEvent the target event
// *! \param pArg event argument
// *! \return access result
// */
//extern fsm_rt_t invoke_delegate( delegate_t *ptEvent, void *pArg);
//
//

#endif /* delegate_h */
