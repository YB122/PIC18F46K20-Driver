#include "Ultrasonic_Sensor.h"

/******************************/

std_ReturneType Ultrasonic_Sensor_initialize(const Ultrasonic_Sensor_pin *US_obj)
{
    std_ReturneType ret = E_NOT_OK;
    if(US_obj == NULL)
        ret = E_NOT_OK;
    else
    {
        ret = gpio_pin_direction_intialize(&(US_obj->TRIG));
        ret = gpio_pin_direction_intialize(&(US_obj->ECHO));
        ret = Timer0_initialize(&(US_obj->timer_pin));
        ret = E_OK;
    }
    return ret ; 
}

/******************************/

std_ReturneType Ultrasonic_Sensor_Get_Distance(const Ultrasonic_Sensor_pin *US_obj , uint16 *distance)
{
    std_ReturneType ret = E_NOT_OK;
    if((US_obj == NULL) || (distance == NULL))
        ret = E_NOT_OK;
    else
    {
        uint8 logic_pin = LOW ;
        uint16 timer0_value = 0;
        ret = gpio_pin_write_logic(&(US_obj->TRIG) , HIGH);
        DU(10);
        ret = gpio_pin_write_logic(&(US_obj->TRIG) , LOW);
        while(logic_pin == LOW)
            ret = gpio_pin_read_logic(&(US_obj->ECHO) , &logic_pin);
        ret = Timer0_Write_Value(&(US_obj->timer_pin) , timer0_value);
        while(logic_pin == HIGH)
            ret = gpio_pin_read_logic(&(US_obj->ECHO) , &logic_pin);
        ret = Timer0_Read_Value(&(US_obj->timer_pin)  , &timer0_value);
        *distance = (uint16)(timer0_value / 58.0);
        DM(60);
        ret = E_OK;
    }
    return ret ;
}

/******************************/