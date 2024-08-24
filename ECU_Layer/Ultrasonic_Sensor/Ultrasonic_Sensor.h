#ifndef ULTRASONIC_SENSOR_H
#define	ULTRASONIC_SENSOR_H

#include "../../MCAL_Layer/TIMER0/timer0_hal.h"

typedef struct
{
    pin_config_t TRIG;
    pin_config_t ECHO;
    timer0_confg_t timer_pin;
}Ultrasonic_Sensor_pin;

std_ReturneType Ultrasonic_Sensor_initialize(const Ultrasonic_Sensor_pin *US_obj);
std_ReturneType Ultrasonic_Sensor_Get_Distance(const Ultrasonic_Sensor_pin *US_obj , uint16 *distance);

#endif	/* ULTRASONIC_SENSOR_H */
