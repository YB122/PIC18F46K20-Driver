#ifndef TIMER0_HAL_H
#define	TIMER0_HAL_H

#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupts/mcal_internal_interrupt.h"

#define Enables_Timer0()                   (T0CONbits.TMR0ON = 1)
#define Stops_Timer0()                     (T0CONbits.TMR0ON = 0)

#define Timer0_is_8_bit()                  (T0CONbits.T08BIT = 1)
#define Timer0_is_16_bit()                 (T0CONbits.T08BIT = 0)

#define Transition_on_T0CKI_pin()          (T0CONbits.T0CS = 1) // counter 
#define Internal_instruction_cycle_clock() (T0CONbits.T0CS = 0) // timer

#define Timer0_Falling_Edge()              (T0CONbits.T0SE = 1)
#define Timer0_Rising_Edge()               (T0CONbits.T0SE = 0)

#define TImer0_prescaler_not_assigned()    (T0CONbits.PSA = 1)
#define TImer0_prescaler_assigned()        (T0CONbits.PSA = 0)

#define TImer0_prescaler_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE

#if TImer0_prescaler_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

typedef enum
{
    Timer0_Prescaler_DIV_2,
    Timer0_Prescaler_DIV_4,
    Timer0_Prescaler_DIV_8,
    Timer0_Prescaler_DIV_16,
    Timer0_Prescaler_DIV_32,
    Timer0_Prescaler_DIV_64,
    Timer0_Prescaler_DIV_128,
    Timer0_Prescaler_DIV_256
}Timer0_Prescaler_Select;

#endif 

typedef enum
{
    Timer0_8_bit,
    Timer0_16_bit
}Timer0_x_bit;

typedef enum
{
    timer0_falling,
    timer0_rising
}timer0_edge;

typedef enum
{
    timer_timer0,
    counter_timer0
}timer0_mode;

typedef struct
{
    uint16 timer0_preload_value ;
    
    #if TImer0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* TIMER0_INTERRUPT_HANDLER)(void);
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PRIORITY_CFG priority;
    #endif
    #endif  
    
    #if TImer0_prescaler_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    Timer0_Prescaler_Select Timer0_Prescaler;
    #endif

    Timer0_x_bit select_bit;
    timer0_edge edge;
    timer0_mode mode;  
}timer0_confg_t;

std_ReturneType Timer0_initialize(const timer0_confg_t *timer_obj);
std_ReturneType Timer0_deinitialize(const timer0_confg_t *timer_obj);
std_ReturneType Timer0_Read_Value(const timer0_confg_t *timer_obj , uint16 *value);
std_ReturneType Timer0_Write_Value(const timer0_confg_t *timer_obj , uint16 value);

#endif	/* TIMER0_HAL_H */