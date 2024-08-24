#ifndef LINE_TRACKER_H
#define	LINE_TRACKER_H

#include "../../MCAL_Layer/GPIO/hal_gpio.h"

typedef enum
{
    BLACK,
    WHITE     
}line_tracker_status_t;

typedef struct
{
    pin_config_t right;
    pin_config_t center;
    pin_config_t left;
}line_tracker_3_pin;

std_ReturneType Line_Tracker_intialize(const line_tracker_3_pin *line_tracker_obj);
std_ReturneType Line_Tracker_Right_Status(const line_tracker_3_pin *line_tracker_obj , line_tracker_status_t *line_tracker_status);
std_ReturneType Line_Tracker_Center_Status(const line_tracker_3_pin *line_tracker_obj , line_tracker_status_t *line_tracker_status);
std_ReturneType Line_Tracker_Left_Status(const line_tracker_3_pin *line_tracker_obj , line_tracker_status_t *line_tracker_status);

#endif	/* LINE_TRACKER_H */

