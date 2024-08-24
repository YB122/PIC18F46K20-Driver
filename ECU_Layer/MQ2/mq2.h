#ifndef MQ2_H
#define	MQ2_H

#include "../../MCAL_Layer/ADC/hal_adc.h"

#define MQ2_DETECT       1
#define MQ2_NOT_DETECT   0

typedef struct
{
    ADC_config_t MQ2_pin_analog;
    pin_config_t MQ2_pin_digital;
}mq2_t;

std_ReturneType MQ2_initialize(const mq2_t *mq2_obj);
std_ReturneType MQ2_Read_Data(const mq2_t *mq2_obj , uint16 *Data_Analog , uint8 *Data_Digital);

#endif	/* MQ2_H */