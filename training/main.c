//
//  main.c
//  training
//
//  Created by zhaoli on 2017/8/23.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#include "app_cfg.h"
#include "test1A/test1A.h"


int main(int argc, const char * argv[]) {
    
    fsm(print_hello) fsmPrintString;
    
    init_fsm(print_hello, &fsmPrintString);
    
    while (1) {
        call_fsm(print_hello, &fsmPrintString);
    }
    
    return 0;
}
