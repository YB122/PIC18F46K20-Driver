#ifndef SERVO_MOTOR_H
#define	SERVO_MOTOR_H

#include "../../MCAL_Layer/TIMER0/timer0_hal.h"

typedef struct
{
    pin_config_t servo_pin;
    timer0_confg_t timer_pin;
}servo_motor_t;


std_ReturneType servo_motor_initialize(const servo_motor_t *servo_motor_obj);
std_ReturneType servo_motor_write_degree(const servo_motor_t *servo_motor_obj , uint16 degree);

#endif	/* SERVO_MOTOR_H */

