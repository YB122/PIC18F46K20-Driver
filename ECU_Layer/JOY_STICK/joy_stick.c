#include "joy_stick.h"

/*****************************/

std_ReturneType JOT_STICK_initialize(const joy_stick_t *joy_stick_obj)
{
    std_ReturneType ret = E_NOT_OK;
    if(joy_stick_obj == NULL)
        ret = E_NOT_OK;
    else
    {
        ret = ADC_initialize(&(joy_stick_obj->X_AXIS));
        ret = ADC_initialize(&(joy_stick_obj->Y_AXIS));
        ret = button_intialize(&(joy_stick_obj->switch_pin));
        ret = E_OK;
    }
    return ret;
}

/*****************************/

std_ReturneType JOT_STICK_READ_X_Y_switch(const joy_stick_t *joy_stick_obj , uint16 *x_data , uint16 *y_data , button_status_t *btn_status)
{
    std_ReturneType ret = E_NOT_OK;
    if((joy_stick_obj == NULL) || (x_data == NULL) || (y_data == NULL) || (btn_status == NULL))
        ret = E_NOT_OK;
    else
    {
        ret = ADC_get_conversion(&(joy_stick_obj->X_AXIS) , (joy_stick_obj->X_AXIS.ANx) , x_data);
        ret = ADC_get_conversion(&(joy_stick_obj->Y_AXIS) , (joy_stick_obj->Y_AXIS.ANx) , y_data);
        ret = button_read_status(&(joy_stick_obj->switch_pin) , btn_status);
        ret = E_OK;
    }
    return ret;
}

/*****************************/