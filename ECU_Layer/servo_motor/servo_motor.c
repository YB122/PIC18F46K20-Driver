#include "servo_motor.h"
/*
static void TIMER0_ISR_(void);
static uint16 delay_time_us = 0 , timer0_value = 0;
static uint8 logic_flag = 0;

std_ReturneType servo_motor_initialize(const servo_motor_t *servo_motor_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(servo_motor_obj == NULL)
        ret = E_NOT_OK;
    else
    {
        ret = gpio_pin_direction_intialize(&(servo_motor_obj->servo_pin));
        ret = servo_motor_obj->timer_pin.TIMER0_INTERRUPT_HANDLER = TIMER0_ISR_;
        ret = Timer0_initialize(&(servo_motor_obj->timer_pin));      
        ret = E_OK;
    }
    return ret ;
}

/**************************************/

std_ReturneType servo_motor_write_degree(const servo_motor_t *servo_motor_obj , uint16 degree)
{
    std_ReturneType ret = E_NOT_OK ;
    if(servo_motor_obj == NULL)
        ret = E_NOT_OK;
    else
    {
        if(degree > 360)
            ret = E_NOT_OK;
        else
        {
            ret = gpio_pin_write_logic(&(servo_motor_obj->servo_pin) , LOW);           
            delay_time_us = (uint16)((((sint32)(degree)) * 1000) / 90);  
            ret = Timer0_Write_Value(&(servo_motor_obj->timer_pin) , 65535);           
            while(timer0_value <= delay_time_us)
                ret = Timer0_Read_Value(&(servo_motor_obj->timer_pin) , &timer0_value);
            ret = gpio_pin_write_logic(&(servo_motor_obj->servo_pin) , LOW);
            while(timer0_value != 40000);
            ret = E_OK; 
        }        
    }
    return ret ;
}

/**************************************/

static void TIMER0_ISR_(void)
{
    if(logic_flag)
    {
        
        logic_flag = 0;
    }
    else
    {
        ret = gpio_pin_write_logic(&(servo_motor_obj->servo_pin) , HIGH);
        logic_flag = 1;
    }
}
