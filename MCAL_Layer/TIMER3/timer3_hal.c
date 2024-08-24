#include "timer3_hal.h"

/******************************/

#if TImer3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TIMER3_INTERRUPT_HANDLER)(void) = NULL ;        
#endif
static void timer3_select_mode(const timer3_confg_t *timer_obj);
static uint16 timer3_preload = 0 ;

/******************************/

std_ReturneType Timer3_initialize(const timer3_confg_t *timer_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(NULL == timer_obj)
        ret = E_NOT_OK ;
    else
    { 
        Stops_Timer3();
        timer3_preload = timer_obj->timer3_preload_value ;
        
        #if TImer3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_ENABLE();
        TIMER3_INTERRUPT_CLEAR_FLAG();
        TIMER3_INTERRUPT_HANDLER = timer_obj->T3MER3_INTERRUPT_HANDLER;        
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_LEVEL_ENABLE();
        if(timer_obj->priority == HIGH_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            TIMER3_HIGH_PRIORITY_SET();
        }   
        else if(timer_obj->priority == LOW_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
            TIMER3_LOW_PRIORITY_SET();
        }            
        else{/* Nothing */}
        #else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();  
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        #endif
        #endif

        timer3_select_mode(timer_obj);
        (T3CONbits.T3CKPS) = timer_obj->Timer3_Prescaler;
        TMR3H = ((timer_obj->timer3_preload_value) >> 8) ;
        TMR3L = (uint8)(timer_obj->timer3_preload_value) ;
        
        Enables_Timer3();
        ret = E_OK ; 
    }
    return ret ;
}

/******************************/

std_ReturneType Timer3_deinitialize(const timer3_confg_t *timer_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(timer_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        Stops_Timer3();
        #if TImer3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_DIASBLE();
        #endif
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType Timer3_Read_Value(const timer3_confg_t *timer_obj , uint16 *value)
{
    std_ReturneType ret = E_NOT_OK ;
    if((timer_obj == NULL) || (value == NULL))
        ret = E_NOT_OK ;
    else
    {
        uint8 tmr3l = 0 , tmr3h = 0 ;
        tmr3l  = TMR3L ;
        tmr3h  = TMR3H ;
        *value = (uint16)((tmr3h << 8) + tmr3l) ;
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType Timer3_Write_Value(const timer3_confg_t *timer_obj , uint16 value)
{
    std_ReturneType ret = E_NOT_OK ;
    if(timer_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        TMR3H = (value >> 8) ;
        TMR3L = (uint8)(value) ;
        ret = E_OK ; 
    }
    return ret ;
}

/******************************/

void TIMER3_ISR(void)
{
    TIMER3_INTERRUPT_CLEAR_FLAG();
    TMR3H = ((timer3_preload) >> 8) ;
    TMR3L = (uint8)(timer3_preload) ;
    if(TIMER3_INTERRUPT_HANDLER)
        TIMER3_INTERRUPT_HANDLER();
}

/******************************/

static void timer3_select_mode(const timer3_confg_t *timer_obj)
{
    if(timer_obj->mode == timer_timer3)
        Timer3_Timer_mode();
    else if(timer_obj->mode == counter_timer3)
    {
        Timer3_Counter_mode();
        if(timer_obj->mode_of_counter == timer3_Synchronize)
            timer3_Synchronize_counter();
        else if(timer_obj->mode_of_counter == timer3_Asynchronize)
            timer3_Asynchronize_counter();
        else{/* Nothing */}        
    }          
    else{/* Nothing */}
}

/******************************/