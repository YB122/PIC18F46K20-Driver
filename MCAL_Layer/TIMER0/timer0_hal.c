#include "timer0_hal.h"

/******************************/

#if TImer0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TIMER0_INTERRUPT_HANDLER)(void) = NULL ;        
#endif
static std_ReturneType timer0_select_mode(const timer0_confg_t *timer_obj);
static std_ReturneType timer0_select_size(const timer0_confg_t *timer_obj);
static uint16 timer0_preload = 0 ;

/******************************/

std_ReturneType Timer0_initialize(const timer0_confg_t *timer_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(NULL == timer_obj)
        ret = E_NOT_OK ;
    else
    { 
        Stops_Timer0();
        
        #if TImer0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_ENABLE();
        TIMER0_INTERRUPT_CLEAR_FLAG();
        TIMER0_INTERRUPT_HANDLER = timer_obj->TIMER0_INTERRUPT_HANDLER;        
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_LEVEL_ENABLE();
        if(timer_obj->priority == HIGH_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            TIMER0_HIGH_PRIORITY_SET();
        }   
        else if(timer_obj->priority == LOW_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
            TIMER0_LOW_PRIORITY_SET();
        }            
        else{/* Nothing */}
        #else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();  
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        #endif
        #endif

        #if TImer0_prescaler_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TImer0_prescaler_assigned();
        (T0CONbits.T0PS) = timer_obj->Timer0_Prescaler;
        #elif
        TImer0_prescaler_not_assigned();
        #else /* Nothing */
        #endif

        ret = timer0_select_mode(timer_obj);
        ret = timer0_select_size(timer_obj);
        
        TMR0H = ((timer_obj->timer0_preload_value) >> 8) ;
        TMR0L = (uint8)(timer_obj->timer0_preload_value) ;
        timer0_preload = timer_obj->timer0_preload_value ;
        Enables_Timer0();
         ret = E_OK ; 
    }
    return ret ;
}

/******************************/

std_ReturneType Timer0_deinitialize(const timer0_confg_t *timer_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(NULL == timer_obj)
        ret = E_NOT_OK ;
    else
    {
        Stops_Timer0();
        #if TImer0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_DIASBLE();
        #endif
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType Timer0_Read_Value(const timer0_confg_t *timer_obj , uint16 *value)
{
    std_ReturneType ret = E_NOT_OK ;
    if((NULL == timer_obj) || (NULL == value))
        ret = E_NOT_OK ;
    else
    {
        uint8 tmr0l = 0 , tmr0h = 0 ;
        tmr0l  = TMR0L ;
        tmr0h  = TMR0H ;
        *value = (uint16)((tmr0h << 8) + tmr0l) ;
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType Timer0_Write_Value(const timer0_confg_t *timer_obj , uint16 value)
{
    std_ReturneType ret = E_NOT_OK ;
    if(NULL == timer_obj)
        ret = E_NOT_OK ;
    else
    {
        TMR0H = (value >> 8) ;
        TMR0L = (uint8)(value) ;
        ret = E_OK ; 
    }
    return ret ;
}

/******************************/
#if TImer0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void TIMER0_ISR(void)
{
    TIMER0_INTERRUPT_CLEAR_FLAG();
    TMR0H = ((timer0_preload) >> 8) ;
    TMR0L = (uint8)(timer0_preload) ;
    if(TIMER0_INTERRUPT_HANDLER)
        TIMER0_INTERRUPT_HANDLER();
}
#endif
/******************************/

static std_ReturneType timer0_select_mode(const timer0_confg_t *timer_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(NULL == timer_obj)
        ret = E_NOT_OK ;
    else
    {
        if(timer_obj->mode == timer_timer0)
            Internal_instruction_cycle_clock();
        else if(timer_obj->mode == counter_timer0)
        {
            Transition_on_T0CKI_pin();
            if(timer_obj->edge == timer0_falling)
                Timer0_Falling_Edge();
            else if(timer_obj->edge == timer0_rising)
                Timer0_Rising_Edge();
            else{/* Nothing */}        
        }
            
        else{/* Nothing */}
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

static std_ReturneType timer0_select_size(const timer0_confg_t *timer_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(NULL == timer_obj)
        ret = E_NOT_OK ;
    else
    {
        if(timer_obj->select_bit == Timer0_8_bit)
            Timer0_is_8_bit();
        else if(timer_obj->select_bit == Timer0_16_bit)
            Timer0_is_16_bit();
        else{/* Nothing */}
        ret = E_OK ;
    }
    return ret ;
}

/******************************/