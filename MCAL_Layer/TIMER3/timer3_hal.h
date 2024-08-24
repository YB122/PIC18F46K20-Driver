#ifndef TIMER3_HAL_H
#define	TIMER3_HAL_H

#include "../Interrupts/mcal_internal_interrupt.h"

#define Enables_Timer3()                          (T3CONbits.TMR3ON = 1)
#define Stops_Timer3()                            (T3CONbits.TMR3ON = 0)

#define Timer3_Timer_mode()                       (T3CONbits.TMR3CS = 0)
#define Timer3_Counter_mode()                     (T3CONbits.TMR3CS = 1)

#define timer3_Synchronize_counter()              (T3CONbits.T3SYNC = 0)
#define timer3_Asynchronize_counter()             (T3CONbits.T3SYNC = 1)

#define Timer3_read_8_bit_mode()                  (T3CONbits.RD16 = 0)
#define Timer3_read_16_bit_mode()                 (T3CONbits.RD16 = 1)

typedef enum
{
    timer_timer3,
    counter_timer3
}timer3_mode;

typedef enum
{
    timer3_Synchronize,
    timer3_Asynchronize
}timer3_mode_of_counter;

typedef enum
{
    timer3_read_8_bit,
    timer3_read_16_bit
}timer3_read_X_mode;

typedef enum
{
    Timer3_Prescaler_DIV_1,
    Timer3_Prescaler_DIV_2,
    Timer3_Prescaler_DIV_4,
    Timer3_Prescaler_DIV_8
}Timer3_Prescaler_Select;

typedef struct
{
    uint16 timer3_preload_value ;
    
    #if TImer3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* T3MER3_INTERRUPT_HANDLER)(void);
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PRIORITY_CFG priority;
    #endif
    #endif
    
    timer3_read_X_mode read_mode;
    timer3_mode mode;
    Timer3_Prescaler_Select Timer3_Prescaler;
    timer3_mode_of_counter mode_of_counter;
}timer3_confg_t;

std_ReturneType Timer3_initialize(const timer3_confg_t *timer_obj);
std_ReturneType Timer3_deinitialize(const timer3_confg_t *timer_obj);
std_ReturneType Timer3_Read_Value(const timer3_confg_t *timer_obj , uint16 *value);
std_ReturneType Timer3_Write_Value(const timer3_confg_t *timer_obj , uint16 value);

#endif	/* TIMER3_HAL_H */

