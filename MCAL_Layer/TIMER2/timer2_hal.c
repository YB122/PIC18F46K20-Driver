#include "timer2_hal.h"

/******************************/

#if TImer2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*TIMER2_INTERRUPT_HANDLER)(void) = NULL ;        
#endif
static uint8 timer2_preload = 0 ;

/******************************/

std_ReturneType Timer2_initialize(const timer2_confg_t *timer_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(NULL == timer_obj)
        ret = E_NOT_OK ;
    else
    { 
        Stops_Timer2();
        timer2_preload = timer_obj->timer2_preload_value ;
        #if TImer1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_ENABLE();
        TIMER1_INTERRUPT_CLEAR_FLAG();
        TIMER2_INTERRUPT_HANDLER = timer_obj->TIMER2_INTERRUPT_HANDLER;        
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_LEVEL_ENABLE();
        if(timer_obj->priority == HIGH_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            TIMER2_HIGH_PRIORITY_SET();
        }   
        else if(timer_obj->priority == LOW_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
            TIMER2_LOW_PRIORITY_SET();
        }            
        else{/* Nothing */}
        #else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();  
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        #endif
        #endif

        (T2CONbits.T2CKPS) = timer_obj->Timer2_Prescaler;
        (T2CONbits.T2OUTPS) = timer_obj->Timer2_Postscale;
        
        Enables_Timer2();
        ret = E_OK ; 
    }
    return ret ;
}

/******************************/

std_ReturneType Timer2_deinitialize(const timer2_confg_t *timer_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(timer_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        Stops_Timer2();
        #if TImer2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_DIASBLE();
        #endif
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType Timer2_Read_Value(const timer2_confg_t *timer_obj , uint8 *value)
{
    std_ReturneType ret = E_NOT_OK ;
    if((timer_obj == NULL) || (value == NULL))
        ret = E_NOT_OK ;
    else
    {
        *value = TMR2 ;
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType Timer2_Write_Value(const timer2_confg_t *timer_obj , uint8 value)
{
    std_ReturneType ret = E_NOT_OK ;
    if(timer_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        TMR2 = value ;
        ret = E_OK ; 
    }
    return ret ;
}

/******************************/

void TIMER2_ISR(void)
{
    TIMER1_INTERRUPT_CLEAR_FLAG();
    TMR2 = timer2_preload ;
    if(TIMER2_INTERRUPT_HANDLER)
        TIMER2_INTERRUPT_HANDLER();
}

/******************************/