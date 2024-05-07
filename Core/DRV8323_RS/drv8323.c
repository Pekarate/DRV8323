/*
 * drv8323.c
 *
 *  Created on: May 7, 2024
 *      Author: ADMIN
 */
#include "drv8323.h"
#include "drv8232_io.h"
#include "drv8323_pwm.h"
#include "drv8323_spi.h"

extern SPI_HandleTypeDef hspi1;

void drv8323_init(void){
	drv8323_set_enable(1);
	DRV832x_initSPIInterface(&hspi1);
	drv_pwm_set_duty_cycle(50);
}

void drv832_set_dir(uint8_t dir){
	drv8323io_set_dir(dir);
}

void drv832_set_speed(uint8_t speed){
	speed = speed;
	drv_pwm_set_frequency(10000);
	drv_pwm_set_duty_cycle(50);
}

void drv832_start(){
	drv8323_set_brake(1);
	drv_pwm_start();
}
void drv832_stop(){
	drv8323_set_brake(0);
	drv_pwm_stop();
}
