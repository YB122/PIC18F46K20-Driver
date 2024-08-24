#ifndef LM35_H
#define	LM35_H

#include "../../MCAL_Layer/ADC/hal_adc.h"


typedef struct
{
    ADC_config_t lm35_pin;
}lm35_t;

std_ReturneType LM35_initialize(const lm35_t *lm35_obj);
std_ReturneType LM35_Read_Temperature(const lm35_t *lm35_obj , uint16 *Temperature);

#endif	/* LM35_H */