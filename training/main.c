//
//  main.c
//  training
//
//  Created by zhaoli on 2017/8/23.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#include "app_cfg.h"
#include "test4A/test4A.h"

int main(int argc, const char * argv[])
{
    init_test4A();
    
    while (1) {
        test4A();
    }
 
    return 0;
}
