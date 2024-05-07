/*
 * drv_io.h
 *
 *  Created on: May 7, 2024
 *      Author: ADMIN
 */

#ifndef DRV8323_RS_DRV8232_IO_H_
#define DRV8323_RS_DRV8232_IO_H_


//#define DRV_BRAKE_Pin GPIO_PIN_8
//#define DRV_BRAKE_GPIO_Port GPIOD
//#define DRV_ENABLE_Pin GPIO_PIN_0
//#define DRV_ENABLE_GPIO_Port GPIOD
//#define DRV_DIR_Pin GPIO_PIN_7
//#define DRV_DIR_GPIO_Port GPIOD

void drv8323_set_dir(uint8_t level);
void drv8323_set_brake(uint8_t level);
void drv8323_set_enable(uint8_t level);

#endif /* DRV8323_RS_DRV8232_IO_H_ */
