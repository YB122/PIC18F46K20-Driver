#ifndef TIMER2_HAL_H
#define	TIMER2_HAL_H

#include "../Interrupts/mcal_internal_interrupt.h"

#define Enables_Timer2()                          (T2CONbits.TMR2ON = 1)
#define Stops_Timer2()                            (T2CONbits.TMR2ON = 0)

typedef enum
{
    Timer2_Prescaler_DIV_1,
    Timer2_Prescaler_DIV_4,
    Timer2_Prescaler_DIV_16
}Timer2_Prescaler_Select;

typedef enum
{
    Timer2_Postscale_DIV_1,
    Timer2_Postscale_DIV_2,
    Timer2_Postscale_DIV_3,
    Timer2_Postscale_DIV_4,
    Timer2_Postscale_DIV_5,
    Timer2_Postscale_DIV_6,
    Timer2_Postscale_DIV_7,
    Timer2_Postscale_DIV_8,
    Timer2_Postscale_DIV_9,
    Timer2_Postscale_DIV_10,
    Timer2_Postscale_DIV_11,
    Timer2_Postscale_DIV_12,
    Timer2_Postscale_DIV_13,
    Timer2_Postscale_DIV_14,
    Timer2_Postscale_DIV_15,
    Timer2_Postscale_DIV_16       
}Timer2_Postscale_Select;

typedef struct
{
    uint8 timer2_preload_value ;
    
    #if TImer2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* TIMER2_INTERRUPT_HANDLER)(void);
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PRIORITY_CFG priority;
    #endif
    #endif

    Timer2_Prescaler_Select Timer2_Prescaler;
    Timer2_Postscale_Select Timer2_Postscale;
}timer2_confg_t;

std_ReturneType Timer2_initialize(const timer2_confg_t *timer_obj);
std_ReturneType Timer2_deinitialize(const timer2_confg_t *timer_obj);
std_ReturneType Timer2_Read_Value(const timer2_confg_t *timer_obj  , uint8 *value);
std_ReturneType Timer2_Write_Value(const timer2_confg_t *timer_obj , uint8 value) ;

#endif	/* TIMER2_HAL_H */