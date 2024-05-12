/*
 * drv8323.h
 *
 *  Created on: May 7, 2024
 *      Author: ADMIN
 */

#ifndef DRV8323_RS_DRV8323_H_
#define DRV8323_RS_DRV8323_H_

#include "stdint.h"

#define DIR_FORWARD 0
#define DIR_BACKWARD 1

void drv8323_init(void);

void drv832_set_dir(uint8_t dir);

void drv832_set_speed(uint8_t percent);

void drv832_start();
void drv832_stop();

void drv832_reset_fault();

#endif /* DRV8323_RS_DRV8323_H_ */
