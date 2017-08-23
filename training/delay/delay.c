//
//  delay.c
//  State
//
//  Created by zhaoli on 2017/8/23.
//  Copyright © 2017年 zhaoli. All rights reserved.
//

#include "./app_cfg.h"

simple_fsm(delay_1s, def_params(uint32_t wCounter;))


fsm_initialiser(delay_1s, args(uint32_t wCounter))
	init_body(
		this.wCounter = wCounter;
	)

fsm_implementation(delay_1s)
	def_states(DELAY_1S)

    body(
        state(DELAY_1S,
			if (!this.wCounter) {
				fsm_cpl();
			}

			this.wCounter -= 1;
			fsm_on_going();
		)
	)