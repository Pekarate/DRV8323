/*
 * drv8323_io.c
 *
 *  Created on: May 7, 2024
 *      Author: ADMIN
 */

#include "stm32f0xx_hal.h"
#include "drv8232_io.h"
#include "main.h"
//#define DRV_BRAKE_Pin GPIO_PIN_8
//#define DRV_BRAKE_GPIO_Port GPIOD
//#define DRV_ENABLE_Pin GPIO_PIN_0
//#define DRV_ENABLE_GPIO_Port GPIOD
//#define DRV_DIR_Pin GPIO_PIN_7
//#define DRV_DIR_GPIO_Port GPIOD

void drv8323_set_dir(uint8_t level) {
	HAL_GPIO_WritePin(DRV_DIR_GPIO_Port, DRV_DIR_Pin, level? GPIO_PIN_SET : GPIO_PIN_RESET );
}

void drv8323_set_brake(uint8_t level){
	HAL_GPIO_WritePin(DRV_BRAKE_GPIO_Port, DRV_BRAKE_Pin, level? GPIO_PIN_SET : GPIO_PIN_RESET );
}

void drv8323_set_enable(uint8_t level){
	HAL_GPIO_WritePin(DRV_ENABLE_GPIO_Port, DRV_ENABLE_Pin, level? GPIO_PIN_SET : GPIO_PIN_RESET );
}
