#ifndef TIMER1_HAL_H
#define	TIMER1_HAL_H

#include "../mcal_std_types.h"
#include "../GPIO/hal_gpio.h"
#include "../Interrupts/mcal_internal_interrupt.h"

#define Enables_Timer1()                          (T1CONbits.TMR1ON = 1)
#define Stops_Timer1()                            (T1CONbits.TMR1ON = 0)

#define Timer1_read_8_bit_mode()                  (T1CONbits.RD16 = 0)
#define Timer1_read_16_bit_mode()                 (T1CONbits.RD16 = 1)

#define Timer1_oscillator_enabled()               (T1CONbits.T1OSCEN = 1)
#define Timer1_oscillator_disable()               (T1CONbits.T1OSCEN = 0)

#define Timer1_Timer_mode()                       (T1CONbits.TMR1CS = 0)
#define Timer1_Counter_mode()                     (T1CONbits.TMR1CS = 1)

#define timer1_Synchronize_counter()                     (T1CONbits.T1SYNC = 0)
#define timer1_Asynchronize_counter()                    (T1CONbits.T1SYNC = 1)

#define TIMER1_SYSTEM_CLK_STATUS()                (T1CONbits.T1RUN)

typedef enum
{
    timer_timer1,
    counter_timer1
}timer1_mode;

typedef enum
{
    timer1_oscillator_mode_disable,
    timer1_oscillator_mode_enable   
}timer1_oscillator_mode;

typedef enum
{
    timer1_Synchronize,
    timer1_Asynchronize
}timer1_mode_of_counter;

typedef enum
{
    Timer1_Prescaler_DIV_1,
    Timer1_Prescaler_DIV_2,
    Timer1_Prescaler_DIV_4,
    Timer1_Prescaler_DIV_8
}Timer1_Prescaler_Select;

typedef enum
{
    timer1_read_8_bit,
    timer1_read_16_bit
}timer1_read_X_mode;

typedef struct
{
    uint16 timer1_preload_value ;
    
    #if TImer1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* TIMER1_INTERRUPT_HANDLER)(void);
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PRIORITY_CFG priority;
    #endif
    #endif
    
    timer1_read_X_mode read_mode;
    timer1_mode mode;
    Timer1_Prescaler_Select Timer1_Prescaler;
    timer1_mode_of_counter mode_of_counter;
    timer1_oscillator_mode oscillator_mode;
}timer1_confg_t;

std_ReturneType Timer1_initialize(const timer1_confg_t *timer_obj);
std_ReturneType Timer1_deinitialize(const timer1_confg_t *timer_obj);
std_ReturneType Timer1_Read_Value(const timer1_confg_t *timer_obj , uint16 *value);
std_ReturneType Timer1_Write_Value(const timer1_confg_t *timer_obj , uint16 value);

#endif	/* TIMER1_HAL_H */