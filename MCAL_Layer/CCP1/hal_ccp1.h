#ifndef CCP_HAL_H
#define	CCP_HAL_H

#include "../Interrupts/mcal_internal_interrupt.h"
#include "../TIMER1/timer1_hal.h"
#include "../TIMER2/timer2_hal.h"
#include "../TIMER3/timer3_hal.h"

#define ccp_Capture_mode_selected     0
#define ccp_Compare_mode_selected     1
#define ccp_pwm_mode_selected         2


#define ccp1_selected_mode       (ccp_pwm_mode_selected)
#define ccp2_selected_mode       (ccp_pwm_mode_selected)

#define ccp_Capture_not_ready   0 
#define ccp_Capture_ready       1

#define ccp_Compare_not_ready   0
#define ccp_Compare_ready       1

typedef enum
{
    Capture_Compare_PWM_disabled,
    Reserved_1,
    Compare_mode_1_toggle_output_on_match,
    Reserved_2,
    Capture_mode_1_every_falling_edge,
    Capture_mode_1_every_rising_dge,
    Capture_mode_1_every_4th_rising_edge,
    Capture_mode_1_every_16th_rising_edge,
    Compare_mode_set_pin_low,
    Compare_mode_set_pin_high,
    Compare_mode_generate_software_interrupt,
    Compare_mode_trigger_special_event,
    PWM_mode          
}Enhanced_CCP1_Mode_Select_bits;

#define ccp1_set_mode(config)    (CCP1CONbits.CCP1M = config)
#define ccp2_set_mode(config)    (CCP2CONbits.CCP2M = config)

typedef union
{
    struct
    {
        uint8 ccp_low;
        uint8 ccp_high;
    };
    struct
    {
        uint16 ccp_16_bit;
    };
}CCP_PERIOD_REG_t;
   
typedef enum
{
    CCP_Prescaler_DIV_1   = 1,
    CCP_Prescaler_DIV_4   = 4,
    CCP_Prescaler_DIV_16  = 16
}CCP_Prescaler_Select;

typedef enum
{
    CCP_Postscale_DIV_1 = 1,
    CCP_Postscale_DIV_2,
    CCP_Postscale_DIV_3,
    CCP_Postscale_DIV_4,
    CCP_Postscale_DIV_5,
    CCP_Postscale_DIV_6,
    CCP_Postscale_DIV_7,
    CCP_Postscale_DIV_8,
    CCP_Postscale_DIV_9,
    CCP_Postscale_DIV_10,
    CCP_Postscale_DIV_11,
    CCP_Postscale_DIV_12,
    CCP_Postscale_DIV_13,
    CCP_Postscale_DIV_14,
    CCP_Postscale_DIV_15,
    CCP_Postscale_DIV_16       
}CCP_Postscale_Select;

typedef enum
{
    CCP1_selected,
    CCP2_selected
}CCPX_selected;

typedef enum
{
    CCP1_CCP2_TIMER1,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER3         
}CCPX_selected_TimerX;  

typedef struct
{
    #if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* CCP1_INTERRUPT_HANDLER)(void);
    INTERRUPT_PRIORITY_CFG priority_1;
    #endif

    #if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (* CCP2_INTERRUPT_HANDLER)(void);
    INTERRUPT_PRIORITY_CFG priority_2;
    #endif

    #if((ccp1_selected_mode == ccp_pwm_mode_selected) || (ccp2_selected_mode == ccp_pwm_mode_selected)) 
    uint32 pwm_frequency ;
    CCP_Prescaler_Select CCP_Prescaler;
    CCP_Postscale_Select CCP_Postscale;
    timer2_confg_t ccp_timer2;
    #endif
    pin_config_t ccp_pin ;
    uint8 ccp_mode ;
    Enhanced_CCP1_Mode_Select_bits ccp_bits_mode ;
    CCPX_selected selecte_CCP;
    CCPX_selected_TimerX ccp_selecte_timer;
    
}ccp_config_t;

std_ReturneType CCP_initialize(const ccp_config_t *ccp_obj);
std_ReturneType CCP_deinitialize(const ccp_config_t *ccp_obj);

#if(ccp1_selected_mode == ccp_Capture_mode_selected) 
std_ReturneType ccp1_capture_data_ready(uint8 *capture_status);
std_ReturneType ccp1_capture_read_value(uint16 *capture_value);
std_ReturneType ccp2_capture_data_ready(uint8 *capture_status);
std_ReturneType ccp2_capture_read_value(uint16 *capture_value);
#endif

#if(ccp1_selected_mode == ccp_Compare_mode_selected) 
std_ReturneType ccp1_compare_data_ready(uint8 *compare_status);
std_ReturneType ccp1_compare_write_value(uint16 compare_value);
std_ReturneType ccp2_compare_data_ready(uint8 *compare_status);
std_ReturneType ccp2_compare_write_value(uint16 compare_value);
#endif

#if(ccp1_selected_mode == ccp_pwm_mode_selected) 
std_ReturneType ccp_pwm_duty_cycle(const ccp_config_t *ccp_obj , float duty);
std_ReturneType ccp_start_pwm(const ccp_config_t *ccp_obj);
std_ReturneType ccp_stop_pwm(const ccp_config_t *ccp_obj);
#endif

#endif	/* CCP_HAL_H */