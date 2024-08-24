#ifndef JOY_STICK_H
#define	JOY_STICK_H

#include "../../MCAL_Layer/ADC/hal_adc.h"
#include "../button/ecu_button.h"

typedef struct
{
    ADC_config_t X_AXIS;
    ADC_config_t Y_AXIS;
    button_t switch_pin;
}joy_stick_t;

std_ReturneType JOT_STICK_initialize(const joy_stick_t *joy_stick_obj);
std_ReturneType JOT_STICK_READ_X_Y_switch(const joy_stick_t *joy_stick_obj , uint16 *x_data , uint16 *y_data , button_status_t *btn_status);

#endif	/* JOY_STICK_H */