#include "ecu_dc_motor.h"

/****************************/

std_ReturneType dc_motor_intialize(const dc_motor_t *_dc_motor)
{
    std_ReturneType ret = E_OK ;
    if(NULL == _dc_motor)
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_direction_intialize(&(_dc_motor->dc_motor[0]));
        ret = gpio_pin_direction_intialize(&(_dc_motor->dc_motor[1]));
        ret = E_OK ; 
    }
    return ret ;
}

/****************************/

std_ReturneType dc_motor_move_right(const dc_motor_t *_dc_motor)
{
    std_ReturneType ret = E_OK ;
    if(NULL == _dc_motor)
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[0]) , HIGH);
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[1]) , LOW);
        ret = E_OK ; 
    }
    return ret ;
}

/****************************/

std_ReturneType dc_motor_move_left(const dc_motor_t *_dc_motor)
{
    std_ReturneType ret = E_OK ;
    if(NULL == _dc_motor)
        ret = E_NOT_OK ;
    else
    {
       ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[0]) , LOW);
       ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[1]) , HIGH);
       ret = E_OK ; 
    }
    return ret ;
}

/****************************/

std_ReturneType dc_motor_move_toggle(const dc_motor_t *_dc_motor)
{
    std_ReturneType ret = E_OK ;
    if(NULL == _dc_motor)
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_toogle_logic(&(_dc_motor->dc_motor[0]));
        ret = gpio_pin_toogle_logic(&(_dc_motor->dc_motor[1]));
        ret = E_OK ; 
    }
    return ret ;
}

/****************************/

std_ReturneType dc_motor_stop(const dc_motor_t *_dc_motor)
{
    std_ReturneType ret = E_OK ;
    if(NULL == _dc_motor)
        ret = E_NOT_OK ;
    else
    {
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[0]) , LOW);
        ret = gpio_pin_write_logic(&(_dc_motor->dc_motor[1]) , LOW);
        ret = E_OK ; 
    }
    return ret ;
}

/****************************/

std_ReturneType dc_motor_intialize_pwm(const dc_motor_t *_dc_motor)
{
    std_ReturneType ret = E_OK ;
    if(NULL == _dc_motor)
        ret = E_NOT_OK ;
    else
    {
        ret = dc_motor_intialize(_dc_motor);
        ret = CCP_initialize(&(_dc_motor->dc_motor_pwm));
        ret = E_OK ; 
    }
    return ret ;
}

/****************************/

std_ReturneType dc_motor_move_right_pwm(const dc_motor_t *_dc_motor , float speed)
{
    std_ReturneType ret = E_OK ;
    if(NULL == _dc_motor)
        ret = E_NOT_OK ;
    else
    {
        ret = dc_motor_move_right(_dc_motor);
        ret = ccp_pwm_duty_cycle(&(_dc_motor->dc_motor_pwm) , speed);
        ret = ccp_start_pwm(&(_dc_motor->dc_motor_pwm));
        ret = E_OK ; 
    }
    return ret ;
}

/****************************/

std_ReturneType dc_motor_move_left_pwm(const dc_motor_t *_dc_motor , float speed)
{
    std_ReturneType ret = E_OK ;
    if(NULL == _dc_motor)
        ret = E_NOT_OK ;
    else
    {
        ret = dc_motor_move_left(_dc_motor);
        ret = ccp_pwm_duty_cycle(&(_dc_motor->dc_motor_pwm) , speed);
        ret = ccp_start_pwm(&(_dc_motor->dc_motor_pwm));
        ret = E_OK ; 
    }
    return ret ;
}

/****************************/