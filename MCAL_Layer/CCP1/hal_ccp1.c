#include "hal_ccp1.h"

/******************************/

#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*CCP1_INTERRUPT_HANDLER)(void) = NULL ;        
#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*CCP2_INTERRUPT_HANDLER)(void) = NULL ;        
#endif

/******************************/

std_ReturneType CCP_initialize(const ccp_config_t *ccp_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(ccp_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        if(ccp_obj->selecte_CCP == CCP1_selected)
        {
            ccp1_set_mode(Capture_Compare_PWM_disabled);   
            if(ccp_obj->ccp_mode == ccp_Capture_mode_selected)
            {
                switch(ccp_obj->ccp_bits_mode)
                {
                    case Capture_mode_1_every_falling_edge : ccp1_set_mode(Capture_mode_1_every_falling_edge) ; ret = E_OK ; break ;
                    case Capture_mode_1_every_rising_dge : ccp1_set_mode(Capture_mode_1_every_rising_dge) ; ret = E_OK ; break ;
                    case Capture_mode_1_every_4th_rising_edge : ccp1_set_mode(Capture_mode_1_every_4th_rising_edge) ; ret = E_OK ; break ;
                    case Capture_mode_1_every_16th_rising_edge : ccp1_set_mode(Capture_mode_1_every_16th_rising_edge) ; ret = E_OK ; break ;
                    default : ret = E_NOT_OK ;
                }
                if(ccp_obj->ccp_selecte_timer == CCP1_CCP2_TIMER1)
                {
                    T3CONbits.T3CCP2 = 0;
                    T3CONbits.T3CCP1 = 0;
                }
                else if(ccp_obj->ccp_selecte_timer == CCP1_TIMER1_CCP2_TIMER3)
                {
                    T3CONbits.T3CCP2 = 0;
                    T3CONbits.T3CCP1 = 1;
                }
                else if(ccp_obj->ccp_selecte_timer == CCP1_CCP2_TIMER3)
                {
                    T3CONbits.T3CCP2 = 1;
                    T3CONbits.T3CCP1 = 0;
                }
                else
                {
                    /* NOTHING */
                }
            }
            else if(ccp_obj->ccp_mode == ccp_Compare_mode_selected)
            {
                switch(ccp_obj->ccp_bits_mode)
                {
                    case Compare_mode_set_pin_low : ccp1_set_mode(Compare_mode_set_pin_low) ; ret = E_OK ; break ;
                    case Compare_mode_set_pin_high : ccp1_set_mode(Compare_mode_set_pin_high) ; ret = E_OK ; break ;
                    case Compare_mode_generate_software_interrupt : ccp1_set_mode(Compare_mode_generate_software_interrupt) ; ret = E_OK ; break ;
                    case Compare_mode_trigger_special_event : ccp1_set_mode(Compare_mode_trigger_special_event) ; ret = E_OK ; break ;
                    default : ret = E_NOT_OK ;
                }
            }
            else if(ccp_obj->ccp_mode == ccp_pwm_mode_selected)
            {
                #if(ccp1_selected_mode == ccp_pwm_mode_selected)  
                if(ccp_obj->ccp_bits_mode == PWM_mode)
                {
                    ccp1_set_mode(PWM_mode);
                    ret = E_OK ;
                }
                else
                {
                    ret = E_NOT_OK ;
                }
                PR2 = (uint8)((((uint32)_XTAL_FREQ) / (((uint32)ccp_obj->pwm_frequency) * 4 * ((uint32)ccp_obj->CCP_Prescaler) ) - 1));
                #endif
                ret = Timer2_initialize(&(ccp_obj->ccp_timer2));
                Stops_Timer2();
            }
        }
        else if(ccp_obj->selecte_CCP == CCP2_selected)
        {
            ccp2_set_mode(Capture_Compare_PWM_disabled);
            if(ccp_obj->ccp_mode == ccp_Capture_mode_selected)
            {
                switch(ccp_obj->ccp_bits_mode)
                {
                    case Capture_mode_1_every_falling_edge : ccp2_set_mode(Capture_mode_1_every_falling_edge) ; ret = E_OK ; break ;
                    case Capture_mode_1_every_rising_dge : ccp2_set_mode(Capture_mode_1_every_rising_dge) ; ret = E_OK ; break ;
                    case Capture_mode_1_every_4th_rising_edge : ccp2_set_mode(Capture_mode_1_every_4th_rising_edge) ; ret = E_OK ; break ;
                    case Capture_mode_1_every_16th_rising_edge : ccp2_set_mode(Capture_mode_1_every_16th_rising_edge) ; ret = E_OK ; break ;
                    default : ret = E_NOT_OK ;
                }
                if(ccp_obj->ccp_selecte_timer == CCP1_CCP2_TIMER1)
                {
                    T3CONbits.T3CCP2 = 0;
                    T3CONbits.T3CCP1 = 0;
                }
                else if(ccp_obj->ccp_selecte_timer == CCP1_TIMER1_CCP2_TIMER3)
                {
                    T3CONbits.T3CCP2 = 0;
                    T3CONbits.T3CCP1 = 1;
                }
                else if(ccp_obj->ccp_selecte_timer == CCP1_CCP2_TIMER3)
                {
                    T3CONbits.T3CCP2 = 1;
                    T3CONbits.T3CCP1 = 0;
                }
                else
                {
                    /* NOTHING */
                }
            }
            else if(ccp_obj->ccp_mode == ccp_Compare_mode_selected)
            {
                switch(ccp_obj->ccp_bits_mode)
                {
                    case Compare_mode_set_pin_low : ccp2_set_mode(Compare_mode_set_pin_low) ; ret = E_OK ; break ;
                    case Compare_mode_set_pin_high : ccp2_set_mode(Compare_mode_set_pin_high) ; ret = E_OK ; break ;
                    case Compare_mode_generate_software_interrupt : ccp2_set_mode(Compare_mode_generate_software_interrupt) ; ret = E_OK ; break ;
                    case Compare_mode_trigger_special_event : ccp2_set_mode(Compare_mode_trigger_special_event) ; ret = E_OK ; break ;
                    default : ret = E_NOT_OK ;
                }
            }
            else if(ccp_obj->ccp_mode == ccp_pwm_mode_selected)
            {
                #if(ccp2_selected_mode == ccp_pwm_mode_selected)
                if(ccp_obj->ccp_bits_mode == PWM_mode)
                {
                    ccp2_set_mode(PWM_mode);
                    ret = E_OK ;
                }
                else
                {
                    ret = E_NOT_OK ;
                }
                PR2 = (uint8)((((uint32)_XTAL_FREQ) / (((uint32)ccp_obj->pwm_frequency) * 4 * ((uint32)ccp_obj->CCP_Prescaler) * ((uint32)ccp_obj->CCP_Postscale)) - 1));
                #endif
                ret = Timer2_initialize(&(ccp_obj->ccp_timer2));
                Stops_Timer2();
            }
        }
        else
        {
            /* NOTHING */
        }
        ret = gpio_pin_intialize(&(ccp_obj->ccp_pin));
        
        #if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        CCP1_INTERRUPT_ENABLE();
        CCP1_INTERRUPT_CLEAR_FLAG();
        CCP1_INTERRUPT_HANDLER = ccp_obj->CCP1_INTERRUPT_HANDLER;
        
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_LEVEL_ENABLE();
        if(ccp_obj->priority_1 == HIGH_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            CCP1_HIGH_PRIORITY_SET();
        }   
        else if(ccp_obj->priority_1 == LOW_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
            CCP1_LOW_PRIORITY_SET();
        }            
        else{/* Nothing */}
        #else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();  
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        
        #endif
        #endif  

        #if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        CCP2_INTERRUPT_ENABLE();
        CCP2_INTERRUPT_CLEAR_FLAG();
        CCP2_INTERRUPT_HANDLER = ccp_obj->CCP2_INTERRUPT_HANDLER;
        
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_LEVEL_ENABLE();
        if(ccp_obj->priority_2 == HIGH_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            CCP2_HIGH_PRIORITY_SET();
        }   
        else if(ccp_obj->priority_2 == LOW_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
            CCP2_LOW_PRIORITY_SET();
        }            
        else{/* Nothing */}
        #else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();  
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        
        #endif
        #endif       
    }
    return ret ;
}

/******************************/

std_ReturneType CCP_deinitialize(const ccp_config_t *ccp_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(ccp_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        if(ccp_obj->selecte_CCP == CCP1_selected)
        {
        ccp1_set_mode(Capture_Compare_PWM_disabled);
        #if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        CCP1_INTERRUPT_DIASBLE();
        #endif            
        }
        else if(ccp_obj->selecte_CCP == CCP1_selected)
        {
            ccp2_set_mode(Capture_Compare_PWM_disabled);
            #if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            CCP2_INTERRUPT_DIASBLE();
            #endif 
        }
        else
        {
            /* NOTHING */
        }
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

#if((ccp1_selected_mode == ccp_Capture_mode_selected) || (ccp2_selected_mode == ccp_Capture_mode_selected)) 

std_ReturneType ccp1_capture_data_ready(uint8 *capture_status)
{
    std_ReturneType ret = E_NOT_OK ;
    if(capture_status == NULL)
        ret = E_NOT_OK ;
    else
    {
        if(PIR1bits.CCP1IF == ccp_Capture_ready)
        {
            *capture_status = (uint8)ccp_Capture_ready;
            CCP1_INTERRUPT_CLEAR_FLAG();
        }
        else
        {
            *capture_status = (uint8)ccp_Capture_not_ready;
        }
        ret = E_OK ;       
    }
    return ret ;
}

/******************************/

std_ReturneType ccp1_capture_read_value(uint16 *capture_value)
{
    std_ReturneType ret = E_NOT_OK ;
    if(capture_value == NULL)
        ret = E_NOT_OK ;
    else
    {
        CCP_PERIOD_REG_t capture_value_temp = {.ccp_16_bit = 0};
        capture_value_temp.ccp_low  = CCPR1L;
        capture_value_temp.ccp_high = CCPR1H;
        *capture_value = capture_value_temp.ccp_16_bit;
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType ccp2_capture_data_ready(uint8 *capture_status)
{
    std_ReturneType ret = E_NOT_OK ;
    if(capture_status == NULL)
        ret = E_NOT_OK ;
    else
    {
        if(PIR2bits.CCP2IF == ccp_Capture_ready)
        {
            *capture_status = (uint8)ccp_Capture_ready;
            CCP2_INTERRUPT_CLEAR_FLAG();
        }
        else
        {
            *capture_status = (uint8)ccp_Capture_not_ready;
        }
        ret = E_OK ;      
    }
    return ret ;
}

/******************************/

std_ReturneType ccp2_capture_read_value(uint16 *capture_value)
{
    std_ReturneType ret = E_NOT_OK ;
    if(capture_value == NULL)
        ret = E_NOT_OK ;
    else
    {
        CCP_PERIOD_REG_t capture_value_temp = {.ccp_16_bit = 0};
        capture_value_temp.ccp_low  = CCPR2L;
        capture_value_temp.ccp_high = CCPR2H;
        *capture_value = capture_value_temp.ccp_16_bit;
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

#endif

#if((ccp1_selected_mode == ccp_Compare_mode_selected) || (ccp2_selected_mode == ccp_Compare_mode_selected)) 

std_ReturneType ccp1_compare_data_ready(uint8 *compare_status)
{
    std_ReturneType ret = E_NOT_OK ;
    if(compare_status == NULL)
        ret = E_NOT_OK ;
    else
    {
        if(PIR1bits.CCP1IF == ccp_Capture_ready)
        {
            *compare_status = (uint8)ccp_Compare_ready;
            CCP1_INTERRUPT_CLEAR_FLAG();
        }
        else
        {
            *compare_status = (uint8)ccp_Compare_not_ready;
        }
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType ccp1_compare_write_value(uint16 compare_value)
{
    std_ReturneType ret = E_NOT_OK ;
    CCP_PERIOD_REG_t capture_value_temp = {.ccp_16_bit = 0};
    capture_value_temp.ccp_16_bit = compare_value ;
    CCPR1L = capture_value_temp.ccp_low;
    CCPR1H = capture_value_temp.ccp_high;
    ret = E_OK ;
    return ret ;
}

/******************************/

std_ReturneType ccp2_compare_data_ready(uint8 *compare_status)
{
    std_ReturneType ret = E_NOT_OK ;
    if(compare_status == NULL)
        ret = E_NOT_OK ;
    else
    {
        if(PIR2bits.CCP2IF == ccp_Capture_ready)
        {
            *compare_status = (uint8)ccp_Compare_ready;
            CCP2_INTERRUPT_CLEAR_FLAG();
        }
        else
        {
            *compare_status = (uint8)ccp_Compare_not_ready;
        }
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType ccp2_compare_write_value(uint16 compare_value)
{
    std_ReturneType ret = E_NOT_OK ;
    CCP_PERIOD_REG_t capture_value_temp = {.ccp_16_bit = 0};
    capture_value_temp.ccp_16_bit = compare_value ;
    CCPR2L = capture_value_temp.ccp_low;
    CCPR2H = capture_value_temp.ccp_high;
    ret = E_OK ;
    return ret ;
}

/******************************/

#endif

#if((ccp1_selected_mode == ccp_pwm_mode_selected) || (ccp2_selected_mode == ccp_pwm_mode_selected)) 

std_ReturneType ccp_pwm_duty_cycle(const ccp_config_t *ccp_obj , float duty)
{   
    std_ReturneType ret = E_NOT_OK ;
    if(ccp_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        uint16 local_duty = 0;
        local_duty = (uint16)(4 * ((float)PR2 + 1) * (((float)duty / 100.0)));
        if(ccp_obj->selecte_CCP == CCP1_selected)
        {
            CCP1CONbits.DC1B = (uint8)(local_duty & 0x0003);
            CCPR1L = (uint8)(local_duty >> 2);  
        }
        else if(ccp_obj->selecte_CCP == CCP2_selected)
        {
            CCP2CONbits.DC2B = (uint8)(local_duty & 0x0003);
            CCPR2L = (uint8)(local_duty >> 2);
        }
        else
        {
            /* NOTHING */
        }
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType ccp_start_pwm(const ccp_config_t *ccp_obj)
{   
    std_ReturneType ret = E_NOT_OK ;
    if(ccp_obj == NULL)
        ret = E_NOT_OK ;
    else
    {     
        if(ccp_obj->selecte_CCP == CCP1_selected)
        {
            ccp1_set_mode(PWM_mode);  
            Enables_Timer2();
        }
        else if(ccp_obj->selecte_CCP == CCP2_selected)
        {
            ccp2_set_mode(PWM_mode);
            Enables_Timer2();
        }
        else
        {
            /* NOTHING */
        }
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType ccp_stop_pwm(const ccp_config_t *ccp_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(ccp_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        if(ccp_obj->selecte_CCP == CCP1_selected)
        {
            ccp1_set_mode(Capture_Compare_PWM_disabled); 
            Stops_Timer2();
        }
        else if(ccp_obj->selecte_CCP == CCP2_selected)
        {
            ccp2_set_mode(Capture_Compare_PWM_disabled);
            Stops_Timer2();
        }
        else
        {
            /* NOTHING */
        }
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

#endif

void CCP1_ISR(void)
{
    CCP1_INTERRUPT_CLEAR_FLAG();   
    if(CCP1_INTERRUPT_HANDLER)
        CCP1_INTERRUPT_HANDLER();
}

/******************************/
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void CCP2_ISR(void)
{
    CCP2_INTERRUPT_CLEAR_FLAG();
    if(CCP2_INTERRUPT_HANDLER)
        CCP2_INTERRUPT_HANDLER();
}
#endif
/******************************/
