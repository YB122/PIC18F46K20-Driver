#include "dht11.h"

/******************************/

std_ReturneType DHT11_Read_Data (dht11_config_t *dht11_obj , uint8 *humidity , uint8 *temperature)
{
    std_ReturneType ret = E_NOT_OK;
    if((dht11_obj == NULL) || (humidity == NULL) || (temperature == NULL))
        ret = E_NOT_OK;
    else
    {
        uint16 timer3_value = 0;
        uint8 logic_pin = LOW ;
        uint8 l_counter = 0 ;
        uint8 Low_temperature = 0 , Low_humidity = 0 , Total = 0 , Check_Total = 0 ; 
        *humidity = 0 ;
        *temperature = 0 ;
        ret = Timer3_initialize(&(dht11_obj->timer3_dht11));
        ret = dht11_obj->pin_dht11.direction = OUTPUT;
        ret = gpio_pin_direction_intialize(&(dht11_obj->pin_dht11));
        ret = gpio_pin_write_logic(&(dht11_obj->pin_dht11) , LOW);
        ret = Timer3_Write_Value(&(dht11_obj->timer3_dht11) , delay_0_us);
        while(timer3_value <= delay_18_ms)
            ret = Timer3_Read_Value(&(dht11_obj->timer3_dht11)  , &timer3_value);
        ret = gpio_pin_write_logic(&(dht11_obj->pin_dht11) , HIGH);
        ret = Timer3_Write_Value(&(dht11_obj->timer3_dht11) , delay_0_us);
        while(timer3_value <= delay_40_us)
            ret = Timer3_Read_Value(&(dht11_obj->timer3_dht11)  , &timer3_value);
        ret = gpio_pin_write_logic(&(dht11_obj->pin_dht11) , LOW);
        ret = dht11_obj->pin_dht11.direction = INPUT;
        ret = gpio_pin_direction_intialize(&(dht11_obj->pin_dht11));
        while(logic_pin == HIGH)
            ret = gpio_pin_read_logic(&(dht11_obj->pin_dht11) , &logic_pin);
        while(logic_pin == LOW)
            ret = gpio_pin_read_logic(&(dht11_obj->pin_dht11) , &logic_pin);      
        for(l_counter = 0 ; l_counter < 8 ; l_counter++)
        {
            ret = Timer3_Write_Value(&(dht11_obj->timer3_dht11) , delay_0_us);
            while(timer3_value <= delay_50_us)
                ret = Timer3_Read_Value(&(dht11_obj->timer3_dht11)  , &timer3_value);
            ret = Timer3_Write_Value(&(dht11_obj->timer3_dht11) , delay_0_us);
            while((timer3_value < delay_70_us) && (logic_pin == HIGH))
            {
                ret = Timer3_Read_Value(&(dht11_obj->timer3_dht11)  , &timer3_value);
                ret = gpio_pin_read_logic(&(dht11_obj->pin_dht11) , &logic_pin); 
            }
            *humidity *= 10;
            if(timer3_value < delay_70_us)         
                *humidity += 0;
            else
                *humidity += 1;
        }
        for(l_counter = 0 ; l_counter < 8 ; l_counter++)
        {
            ret = Timer3_Write_Value(&(dht11_obj->timer3_dht11) , delay_0_us);
            while(timer3_value <= delay_50_us)
                ret = Timer3_Read_Value(&(dht11_obj->timer3_dht11)  , &timer3_value);
            ret = Timer3_Write_Value(&(dht11_obj->timer3_dht11) , delay_0_us);
            while((timer3_value < delay_70_us) && (logic_pin == HIGH))
            {
                ret = Timer3_Read_Value(&(dht11_obj->timer3_dht11)  , &timer3_value);
                ret = gpio_pin_read_logic(&(dht11_obj->pin_dht11) , &logic_pin); 
            }
            Low_humidity *= 10;
            if(timer3_value < delay_70_us)         
                Low_humidity += 0;
            else
                Low_humidity += 1;
        }
        for(l_counter = 0 ; l_counter < 8 ; l_counter++)
        {
            ret = Timer3_Write_Value(&(dht11_obj->timer3_dht11) , delay_0_us);
            while(timer3_value <= delay_50_us)
                ret = Timer3_Read_Value(&(dht11_obj->timer3_dht11)  , &timer3_value);
            ret = Timer3_Write_Value(&(dht11_obj->timer3_dht11) , delay_0_us);
            while((timer3_value < delay_70_us) && (logic_pin == HIGH))
            {
                ret = Timer3_Read_Value(&(dht11_obj->timer3_dht11)  , &timer3_value);
                ret = gpio_pin_read_logic(&(dht11_obj->pin_dht11) , &logic_pin); 
            }
            *temperature *= 10;
            if(timer3_value < delay_70_us)         
                *temperature += 0;
            else
                *temperature += 1;
        }
        for(l_counter = 0 ; l_counter < 8 ; l_counter++)
        {
            ret = Timer3_Write_Value(&(dht11_obj->timer3_dht11) , delay_0_us);
            while(timer3_value <= delay_50_us)
                ret = Timer3_Read_Value(&(dht11_obj->timer3_dht11)  , &timer3_value);
            ret = Timer3_Write_Value(&(dht11_obj->timer3_dht11) , delay_0_us);
            while((timer3_value < delay_70_us) && (logic_pin == HIGH))
            {
                ret = Timer3_Read_Value(&(dht11_obj->timer3_dht11)  , &timer3_value);
                ret = gpio_pin_read_logic(&(dht11_obj->pin_dht11) , &logic_pin); 
            }
            Low_temperature *= 10;
            if(timer3_value < delay_70_us)         
                Low_temperature += 0;
            else
                Low_temperature += 1;
        }
        for(l_counter = 0 ; l_counter < 8 ; l_counter++)
        {
            ret = Timer3_Write_Value(&(dht11_obj->timer3_dht11) , delay_0_us);
            while(timer3_value <= delay_50_us)
                ret = Timer3_Read_Value(&(dht11_obj->timer3_dht11)  , &timer3_value);
            ret = Timer3_Write_Value(&(dht11_obj->timer3_dht11) , delay_0_us);
            while((timer3_value < delay_70_us) && (logic_pin == HIGH))
            {
                ret = Timer3_Read_Value(&(dht11_obj->timer3_dht11)  , &timer3_value);
                ret = gpio_pin_read_logic(&(dht11_obj->pin_dht11) , &logic_pin); 
            }
            Total *= 10;
            if(timer3_value < delay_70_us)         
                Total += 0;
            else
                Total += 1;
        }
        Check_Total = Low_humidity + Low_temperature + *temperature + *humidity ;
        if(Check_Total == Total)
            ret = E_OK;
        else
            ret = E_NOT_OK;
    }
    return ret ;
}

/******************************/