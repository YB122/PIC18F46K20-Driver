#ifndef DHT11_H
#define	DHT11_H

#include "../../MCAL_Layer/TIMER3/timer3_hal.h"

#define delay_18_ms             29536
#define delay_40_us             65456
#define delay_80_us             65376
#define delay_50_us             65436
#define delay_28_us             65480
#define delay_28_us             65480
#define delay_70_us             65396
#define delay_0_us              0

typedef struct 
{
    pin_config_t pin_dht11;
    timer3_confg_t timer3_dht11;
}dht11_config_t;

std_ReturneType DHT11_Read_Data(dht11_config_t *dht11_obj , uint8 *humidity , uint8 *temperature);

#endif	/* DHT11_H */

