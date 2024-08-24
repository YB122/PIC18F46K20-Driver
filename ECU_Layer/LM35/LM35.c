#include "LM35.h"

/******************************/

std_ReturneType LM35_initialize(const lm35_t *lm35_obj)
{
    std_ReturneType ret = E_NOT_OK;
    if(lm35_obj == NULL)
        ret = E_NOT_OK;
    else
    {
        ret = ADC_initialize(&(lm35_obj->lm35_pin));
        ret = E_OK;
    }
    return ret;
}

/******************************/

std_ReturneType LM35_Read_Temperature(const lm35_t *lm35_obj , uint16 *Temperature)
{
    std_ReturneType ret = E_NOT_OK;
    if((lm35_obj == NULL) || (Temperature == NULL))
        ret = E_NOT_OK;
    else
    {
        ret = ADC_get_conversion(&(lm35_obj->lm35_pin) , (lm35_obj->lm35_pin.ANx) , Temperature);
        *Temperature = (uint16)(((float) *Temperature) * 4.88f);
        *Temperature /= 10 ;
        ret = E_OK;
    }
    return ret;
}

/******************************/
