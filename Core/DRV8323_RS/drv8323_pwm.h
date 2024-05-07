/*
 * drv8323_pwm.h
 *
 *  Created on: May 7, 2024
 *      Author: ADMIN
 */

#ifndef DRV8323_RS_DRV8323_PWM_H_
#define DRV8323_RS_DRV8323_PWM_H_

void drv_pwm_start(void);
void drv_pwm_stop(void);

void drv_pwm_set_duty_cycle(uint8_t percent);

void drv_pwm_set_frequency(uint16_t hz);

#endif /* DRV8323_RS_DRV8323_PWM_H_ */
