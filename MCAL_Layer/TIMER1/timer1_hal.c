#include "timer1_hal.h"

/******************************/

#if TImer1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TIMER1_INTERRUPT_HANDLER)(void) = NULL ;        
#endif
static void timer1_select_mode(const timer1_confg_t *timer_obj);
static uint16 timer1_preload = 0 ;

/******************************/

std_ReturneType Timer1_initialize(const timer1_confg_t *timer_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(NULL == timer_obj)
        ret = E_NOT_OK ;
    else
    { 
        Stops_Timer1();
        timer1_preload = timer_obj->timer1_preload_value ;
        
        #if TImer1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_ENABLE();
        TIMER1_INTERRUPT_CLEAR_FLAG();
        TIMER1_INTERRUPT_HANDLER = timer_obj->TIMER1_INTERRUPT_HANDLER;        
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_LEVEL_ENABLE();
        if(timer_obj->priority == HIGH_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            TIMER1_HIGH_PRIORITY_SET();
        }   
        else if(timer_obj->priority == LOW_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
            TIMER1_LOW_PRIORITY_SET();
        }            
        else{/* Nothing */}
        #else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();  
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        #endif
        #endif

        timer1_select_mode(timer_obj);
        (T1CONbits.T1CKPS) = timer_obj->Timer1_Prescaler;
        TMR1H = ((timer_obj->timer1_preload_value) >> 8) ;
        TMR1L = (uint8)(timer_obj->timer1_preload_value) ;
        
        Enables_Timer1();
        ret = E_OK ; 
    }
    return ret ;
}

/******************************/

std_ReturneType Timer1_deinitialize(const timer1_confg_t *timer_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(timer_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        Stops_Timer1();
        #if TImer1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_DIASBLE();
        #endif
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType Timer1_Read_Value(const timer1_confg_t *timer_obj , uint16 *value)
{
    std_ReturneType ret = E_NOT_OK ;
    if((timer_obj == NULL) || (value == NULL))
        ret = E_NOT_OK ;
    else
    {
        uint8 tmr1l = 0 , tmr1h = 0 ;
        tmr1l  = TMR1L ;
        tmr1h  = TMR1H ;
        *value = (uint16)((tmr1h << 8) + tmr1l) ;
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType Timer1_Write_Value(const timer1_confg_t *timer_obj , uint16 value)
{
    std_ReturneType ret = E_NOT_OK ;
    if(timer_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        TMR1H = (value >> 8) ;
        TMR1L = (uint8)(value) ;
        ret = E_OK ; 
    }
    return ret ;
}

/******************************/

void TIMER1_ISR(void)
{
    TIMER1_INTERRUPT_CLEAR_FLAG();
    TMR1H = ((timer1_preload) >> 8) ;
    TMR1L = (uint8)(timer1_preload) ;
    if(TIMER1_INTERRUPT_HANDLER)
        TIMER1_INTERRUPT_HANDLER();
}

/******************************/

static void timer1_select_mode(const timer1_confg_t *timer_obj)
{
    if(timer_obj->mode == timer_timer1)
        Timer1_Timer_mode();
    else if(timer_obj->mode == counter_timer1)
    {
        Timer1_Counter_mode();
        if(timer_obj->mode_of_counter == timer1_Synchronize)
            timer1_Synchronize_counter();
        else if(timer_obj->mode_of_counter == timer1_Asynchronize)
            timer1_Asynchronize_counter();
        else{/* Nothing */}        
    }          
    else{/* Nothing */}
}

/******************************/