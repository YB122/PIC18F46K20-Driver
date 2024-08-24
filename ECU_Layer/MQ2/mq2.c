#include "mq2.h"

/******************************/

std_ReturneType MQ2_initialize(const mq2_t *mq2_obj)
{
    std_ReturneType ret = E_NOT_OK;
    if(mq2_obj == NULL)
        ret = E_NOT_OK;
    else
    {
        ret = ADC_initialize(&(mq2_obj->MQ2_pin_analog));
        ret = gpio_pin_direction_intialize(&(mq2_obj->MQ2_pin_digital));
        ret = E_OK;
    }
    return ret;
}

/******************************/

std_ReturneType MQ2_Read_Data(const mq2_t *mq2_obj , uint16 *Data_Analog , uint8 *Data_Digital)
{
    std_ReturneType ret = E_NOT_OK;
    if(mq2_obj == NULL)
        ret = E_NOT_OK;
    else
    {
        ret = ADC_get_conversion(&(mq2_obj->MQ2_pin_analog) , (mq2_obj->MQ2_pin_analog.ANx) , Data_Analog);
        ret = gpio_pin_read_logic(&(mq2_obj->MQ2_pin_digital) , Data_Digital);
        ret = E_OK;
    }
    return ret;
}

/******************************/