#include "line_tracker.h"

/*****************************/

std_ReturneType Line_Tracker_intialize(const line_tracker_3_pin *line_tracker_obj)
{
    std_ReturneType ret = E_NOT_OK;
    if(line_tracker_obj == NULL)
        ret = E_NOT_OK;
    else
    {
        ret = gpio_pin_direction_intialize(&(line_tracker_obj->right));
        ret = gpio_pin_direction_intialize(&(line_tracker_obj->left));
        ret = gpio_pin_direction_intialize(&(line_tracker_obj->center));
        ret = E_OK;
    }
    return ret;
}

/*****************************/

std_ReturneType Line_Tracker_Right_Status(const line_tracker_3_pin *line_tracker_obj , line_tracker_status_t *line_tracker_status)
{
    std_ReturneType ret = E_NOT_OK;
    if((line_tracker_obj == NULL) || (line_tracker_status == NULL))
        ret = E_NOT_OK;
    else
    {
        uint8 Right_logic = BLACK ;
        ret = gpio_pin_read_logic(&(line_tracker_obj->right) , &Right_logic);
        if(Right_logic == BLACK)
            *line_tracker_status = BLACK;
        else
            *line_tracker_status = WHITE;
        ret = E_OK;
    }
    return ret;
}

/*****************************/

std_ReturneType Line_Tracker_Center_Status(const line_tracker_3_pin *line_tracker_obj , line_tracker_status_t *line_tracker_status)
{
    std_ReturneType ret = E_NOT_OK;
    if((line_tracker_obj == NULL) || (line_tracker_status == NULL))
        ret = E_NOT_OK;
    else
    {
        uint8 Center_Right_logic = BLACK ;
        ret = gpio_pin_read_logic(&(line_tracker_obj->center) , &Center_Right_logic);
        if(Center_Right_logic == BLACK)
            *line_tracker_status = BLACK;
        else
            *line_tracker_status = WHITE;
        ret = E_OK;
    }
    return ret;
}

/*****************************/

std_ReturneType Line_Tracker_Left_Status(const line_tracker_3_pin *line_tracker_obj , line_tracker_status_t *line_tracker_status)
{
    std_ReturneType ret = E_NOT_OK;
    if((line_tracker_obj == NULL) || (line_tracker_status == NULL))
        ret = E_NOT_OK;
    else
    {
        uint8 Left_logic = BLACK ;
        ret = gpio_pin_read_logic(&(line_tracker_obj->left) , &Left_logic);
        if(Left_logic == BLACK)
            *line_tracker_status = BLACK;
        else
            *line_tracker_status = WHITE;
        ret = E_OK;
    }
    return ret;
}

/*****************************/