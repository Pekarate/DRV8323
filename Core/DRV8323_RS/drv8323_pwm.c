/*
 * drv8323_pwm.c
 *
 *  Created on: May 7, 2024
 *      Author: ADMIN
 */

#include "stm32f0xx_hal.h"
#include "stdint.h"
#include "drv8323_pwm.h"
extern TIM_HandleTypeDef htim15;



void drv_pwm_start(void)
{
	HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);
}
void drv_pwm_stop(void){
	HAL_TIM_PWM_Stop(&htim15, TIM_CHANNEL_1);
}

void drv_pwm_set_duty_cycle(uint8_t percent){
 uint16_t reload = __HAL_TIM_GET_AUTORELOAD(&htim15);
 __HAL_TIM_SET_COMPARE(&htim15,TIM_CHANNEL_1,(reload/100)*percent);
}


/*input 1000000hz*/
#define TIMER_FRE 48000000
void drv_pwm_set_frequency(uint16_t hz){
	uint32_t prescale = htim15.Instance->PSC;
	if((TIMER_FRE/(prescale+1)) > 65535) {
		//todo
		while(1);
	}
	__HAL_TIM_SET_AUTORELOAD(&htim15,(TIMER_FRE/(prescale+1) / hz));
// __HAL_T / IM_SET_AUTORELOAD(&htim15,)
}
