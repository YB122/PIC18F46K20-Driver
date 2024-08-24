#include "ecu_layer_initialize.h"

volatile uint32 int_flag = 0;

/******************************/

chr_lcd_4bit_t lcd_1 = 
{
    .lcd_rs.port = PORTC_INDEX ,
    .lcd_rs.pin  = pin0        ,
    .lcd_rs.direction = OUTPUT ,
    .lcd_rs.logic = LOW        ,
    .lcd_en.port = PORTC_INDEX ,
    .lcd_en.pin  = pin1        ,
    .lcd_en.direction = OUTPUT ,
    .lcd_en.logic = LOW        ,
    .lcd_data[0].port = PORTC_INDEX ,
    .lcd_data[0].pin = pin2 ,
    .lcd_data[0].direction = OUTPUT ,
    .lcd_data[0].logic = LOW ,
    .lcd_data[1].port = PORTC_INDEX ,
    .lcd_data[1].pin = pin3 ,
    .lcd_data[1].direction = OUTPUT ,
    .lcd_data[1].logic = LOW ,
    .lcd_data[2].port = PORTD_INDEX ,
    .lcd_data[2].pin = pin0 ,
    .lcd_data[2].direction = OUTPUT ,
    .lcd_data[2].logic = LOW ,
    .lcd_data[3].port = PORTD_INDEX ,
    .lcd_data[3].pin = pin1 ,
    .lcd_data[3].direction = OUTPUT ,
    .lcd_data[3].logic = LOW 
};

/******************************/

chr_lcd_8bit_t lcd_2 = 
{
    .lcd_rs.port = PORTC_INDEX ,
    .lcd_rs.pin  = pin6        ,
    .lcd_rs.direction = OUTPUT ,
    .lcd_rs.logic = LOW        ,
    .lcd_en.port = PORTC_INDEX ,
    .lcd_en.pin  = pin7        ,
    .lcd_en.direction = OUTPUT ,
    .lcd_en.logic = LOW        ,
    .lcd_data[0].port = PORTD_INDEX ,
    .lcd_data[0].pin = pin0 ,
    .lcd_data[0].direction = OUTPUT ,
    .lcd_data[0].logic = LOW ,
    .lcd_data[1].port = PORTD_INDEX ,
    .lcd_data[1].pin = pin1 ,
    .lcd_data[1].direction = OUTPUT ,
    .lcd_data[1].logic = LOW ,
    .lcd_data[2].port = PORTD_INDEX ,
    .lcd_data[2].pin = pin2 ,
    .lcd_data[2].direction = OUTPUT ,
    .lcd_data[2].logic = LOW ,
    .lcd_data[3].port = PORTD_INDEX ,
    .lcd_data[3].pin = pin3 ,
    .lcd_data[3].direction = OUTPUT ,
    .lcd_data[3].logic = LOW ,
    .lcd_data[4].port = PORTD_INDEX ,
    .lcd_data[4].pin = pin4 ,
    .lcd_data[4].direction = OUTPUT ,
    .lcd_data[4].logic = LOW ,
    .lcd_data[5].port = PORTD_INDEX ,
    .lcd_data[5].pin = pin5 ,
    .lcd_data[5].direction = OUTPUT ,
    .lcd_data[5].logic = LOW ,
    .lcd_data[6].port = PORTD_INDEX ,
    .lcd_data[6].pin = pin6 ,
    .lcd_data[6].direction = OUTPUT ,
    .lcd_data[6].logic = LOW ,
    .lcd_data[7].port = PORTD_INDEX ,
    .lcd_data[7].pin = pin7 ,
    .lcd_data[7].direction = OUTPUT ,
    .lcd_data[7].logic = LOW 
};

/******************************/

keypad_t KeyPad1 =
{
    .keypad_row_pins[0].port = PORTB_INDEX,
    .keypad_row_pins[0].direction = OUTPUT,
    .keypad_row_pins[0].logic = LOW       ,
    .keypad_row_pins[0].pin = pin7        ,
    .keypad_row_pins[1].port = PORTB_INDEX,
    .keypad_row_pins[1].direction = OUTPUT,
    .keypad_row_pins[1].logic = LOW       ,
    .keypad_row_pins[1].pin = pin6        ,
    .keypad_row_pins[2].port = PORTB_INDEX,
    .keypad_row_pins[2].direction = OUTPUT,
    .keypad_row_pins[2].logic = LOW       ,
    .keypad_row_pins[2].pin = pin5        ,
    .keypad_row_pins[3].port = PORTB_INDEX,
    .keypad_row_pins[3].direction = OUTPUT,
    .keypad_row_pins[3].logic = LOW       ,
    .keypad_row_pins[3].pin = pin4        ,
    .keypad_columns_pins[0].port = PORTB_INDEX,
    .keypad_columns_pins[0].direction = INPUT     ,
    .keypad_columns_pins[0].logic = LOW           ,
    .keypad_columns_pins[0].pin = pin3            ,
    .keypad_columns_pins[1].port = PORTB_INDEX    ,
    .keypad_columns_pins[1].direction = INPUT     ,
    .keypad_columns_pins[1].logic = LOW           ,
    .keypad_columns_pins[1].pin = pin2            ,
    .keypad_columns_pins[2].port = PORTB_INDEX    ,
    .keypad_columns_pins[2].direction = INPUT     ,
    .keypad_columns_pins[2].logic = LOW           ,
    .keypad_columns_pins[2].pin = pin1            ,
    .keypad_columns_pins[3].port = PORTB_INDEX    ,
    .keypad_columns_pins[3].direction = INPUT     ,
    .keypad_columns_pins[3].logic = LOW           ,
    .keypad_columns_pins[3].pin = pin0                
};

/******************************/

button_t buuton_1 =
{
    .button_active = ACTIVE_HIGH ,
    .button_status = BUTTON_RELEASED,
    .button_pin.direction = INPUT ,
    .button_pin.logic = LOW ,
    .button_pin.port = PORTC_INDEX ,
    .button_pin.pin = pin7 
};

/******************************/

led_t led_red =
{
    .status = LED_OFF ,
    .pin_number = pin3 ,
    .port_name = PORTD_INDEX
};

/******************************/

led_t led_green =
{
    .status = LED_OFF ,
    .pin_number = pin2 ,
    .port_name = PORTD_INDEX
};

/******************************/

led_t led2 =
{
    .status = LED_OFF ,
    .pin_number = pin2 ,
    .port_name = PORTC_INDEX
};

/******************************/

led_t led3 =
{
    .status = LED_OFF ,
    .pin_number = pin3 ,
    .port_name = PORTC_INDEX
};

/******************************/

pin_config_t servo_pin =
{
    .direction = OUTPUT,
    .pin = pin0,
    .port = PORTC_INDEX
};

/******************************/

void INT0_APP_ISR(void);

interrupt_INTx_t int0_obj = {
  .external_interrupt = INT0_APP_ISR,
  .edge = RISING,
  .priority = HIGH_PRIORITY,
  .source = INT_0,
  .mcu_pin.port = PORTB_INDEX,
  .mcu_pin.pin = pin0,
  .mcu_pin.direction = INPUT
};

/******************************/

void INT1_APP_ISR(void);

interrupt_INTx_t int1_obj = {
  .external_interrupt = INT1_APP_ISR,
  .edge = RISING,
  .priority = HIGH_PRIORITY,
  .source = INT_1,
  .mcu_pin.port = PORTB_INDEX,
  .mcu_pin.pin = pin1,
  .mcu_pin.direction = INPUT
};

/******************************/

void INT2_APP_ISR(void);

interrupt_INTx_t int2_obj = {
  .external_interrupt = INT2_APP_ISR,
  .edge = FALLING,
  .priority = LOW_PRIORITY,
  .source = INT_2,
  .mcu_pin.port = PORTB_INDEX,
  .mcu_pin.pin = pin2,
  .mcu_pin.direction = INPUT
};

/******************************/

void RB4_HIGH_Int_APP_ISR(void);
void RB4_LOW_Int_APP_ISR(void);

interrupt_RBx_t rb4_int_obj = {
  .external_interrupt_HIGH =  RB4_HIGH_Int_APP_ISR,
  .external_interrupt_LOW =  RB4_LOW_Int_APP_ISR,
  .priority = HIGH_PRIORITY,
  .mcu_pin.port = PORTB_INDEX,
  .mcu_pin.pin = pin4,
  .mcu_pin.direction = INPUT
};

/******************************/

void RB5_HIGH_Int_APP_ISR(void);
void RB5_LOW_Int_APP_ISR(void);
void CCP1_Int_APP_ISR(void);


interrupt_RBx_t rb5_int_obj = {
  .external_interrupt_HIGH =  RB5_HIGH_Int_APP_ISR,
  .external_interrupt_LOW =  RB5_LOW_Int_APP_ISR,
  .priority = HIGH_PRIORITY,
  .mcu_pin.port = PORTB_INDEX,
  .mcu_pin.pin = pin5,
  .mcu_pin.direction = INPUT
};

/******************************/

void RB6_HIGH_Int_APP_ISR(void);
void RB6_LOW_Int_APP_ISR(void);

interrupt_RBx_t rb6_int_obj = {
  .external_interrupt_HIGH =  RB6_HIGH_Int_APP_ISR,
  .external_interrupt_LOW =  RB6_LOW_Int_APP_ISR,
  .priority = HIGH_PRIORITY,
  .mcu_pin.port = PORTB_INDEX,
  .mcu_pin.pin = pin6,
  .mcu_pin.direction = INPUT
};

/******************************/

void RB7_HIGH_Int_APP_ISR(void);
void RB7_LOW_Int_APP_ISR(void);

interrupt_RBx_t rb7_int_obj = {
  .external_interrupt_HIGH =  RB7_HIGH_Int_APP_ISR,
  .external_interrupt_LOW =  RB7_LOW_Int_APP_ISR,
  .priority = HIGH_PRIORITY,
  .mcu_pin.port = PORTB_INDEX,
  .mcu_pin.pin = pin7,
  .mcu_pin.direction = INPUT
};

/******************************/

lm35_t lm35_mc =
{
    .lm35_pin.ADC_pin.pin = pin0,
    .lm35_pin.ADC_pin.direction = INPUT,
    .lm35_pin.ADC_pin.port = PORTA_INDEX,
    .lm35_pin.ANx = ADC_AN_0,
    .lm35_pin.Frequency = ADC_FOSC_16,
    .lm35_pin.Time = ADC_TAD_12,
    .lm35_pin.Justified = ADC_Right,
    .lm35_pin.Volte = ADC_VCC_GND,
};

/******************************/

ADC_config_t adc_1 =
{
    .ADC_pin.direction = INPUT,
    .ADC_pin.pin = pin0,
    .ADC_pin.port = PORTA_INDEX,
    .ANx = ADC_AN_0,
    .Frequency = ADC_FOSC_16,
    .Time = ADC_TAD_12,
    .Volte = ADC_VCC_GND,
    .Justified = ADC_Right,
};

/******************************/

ADC_config_t adc_2 =
{
    .ADC_pin.direction = INPUT,
    .ADC_pin.pin = pin1,
    .ADC_pin.port = PORTA_INDEX,
    .ANx = ADC_AN_1,
    .Frequency = ADC_FOSC_16,
    .Time = ADC_TAD_12,
    .Volte = ADC_VCC_GND,
    .Justified = ADC_Right,
};

/******************************/

ADC_config_t adc_3 =
{
    .ADC_pin.direction = INPUT,
    .ADC_pin.pin = pin2,
    .ADC_pin.port = PORTA_INDEX,
    .ANx = ADC_AN_2,
    .Frequency = ADC_FOSC_16,
    .Time = ADC_TAD_12,
    .Volte = ADC_VCC_GND,
    .Justified = ADC_Right,
};

/******************************/

dc_motor_t motor_1 =
{
    .dc_motor[0].direction = OUTPUT,
    .dc_motor[0].pin = pin0,
    .dc_motor[0].port = PORTA_INDEX,
    .dc_motor[0].logic = LOW,
    .dc_motor[1].direction = OUTPUT,
    .dc_motor[1].pin = pin1,
    .dc_motor[1].port = PORTA_INDEX,
    .dc_motor[1].logic = LOW,
};

/******************************/

ccp_config_t ccp_1_obj =
{
    .CCP1_INTERRUPT_HANDLER = NULL,
    .selecte_CCP = CCP1_selected,
    .ccp_mode = ccp_pwm_mode_selected,
    .ccp_bits_mode = PWM_mode,
    .ccp_pin.pin = pin2,
    .ccp_pin.port = PORTC_INDEX,
    .ccp_pin.direction = OUTPUT,
    .CCP_Postscale = CCP_Postscale_DIV_1,
    .CCP_Prescaler = CCP_Prescaler_DIV_1,
    .pwm_frequency = 20000,
    .ccp_timer2.Timer2_Postscale = Timer2_Postscale_DIV_1,
    .ccp_timer2.Timer2_Prescaler = Timer2_Prescaler_DIV_1,
};

/******************************/

servo_motor_t servo = 
{
    .servo_pin.direction = OUTPUT,
    .servo_pin.pin = pin0,
    .servo_pin.port = PORTC_INDEX,
    .timer_pin.TIMER0_INTERRUPT_HANDLER = NULL,
    .timer_pin.mode = timer_timer0,
    .timer_pin.select_bit = Timer0_16_bit,
    .timer_pin.edge = timer0_rising,
    .timer_pin.timer0_preload_value = 0,
    .timer_pin.Timer0_Prescaler = Timer0_Prescaler_DIV_4,
};
        
/******************************/

EUSART_t eusart_pin =
{
    .RB = 9600,
    .select_number_of_bit_transmit = Selects_8_bit_transmission,
    .select_number_of_bit_receive = Selects_8_bit_Receive,
    .select_baud_rate_config = Baud_Rate_Asyn_16_bit_High_speed,
    .EUSART_Framing_Error_Handler = NULL,
    .EUSART_Overrun_Error_Handler = NULL,
};

/******************************/

void I2C_ISR(void);

mssp_i2c_t i2c_p =
{
    //.i2c_clock = 100000,
    .i2c_cfg.i2c_slave_address = 0x62,
    .i2c_cfg.i2c_SMBus_control = I2C_disable_SMBus,
    .i2c_cfg.i2c_general_call = I2C_general_call_disable,
    .i2c_cfg.i2c_mode = I2C_SLAVE_MODE,
    .i2c_cfg.i2c_mode_cfg = I2C_Slave_mode_7_bit_address,
    .i2c_cfg.i2c_slew_rate = I2C_Slew_Rate_disable,
    //.I2C_INTERRUPT_HANDLER = I2C_ISR,
    //.I2C_Report_Receive_Overflow = NULL,
    //.I2C_Report_Write_Collision = NULL,
};

/******************************/

Ultrasonic_Sensor_pin US_pin = 
{
    .ECHO.direction = INPUT,
    .ECHO.pin = pin6,
    .ECHO.port = PORTC_INDEX,
    .TRIG.direction = OUTPUT,
    .TRIG.pin = pin7,
    .TRIG.port = PORTC_INDEX,
    .timer_pin.TIMER0_INTERRUPT_HANDLER = NULL,
    .timer_pin.mode = timer_timer0,
    .timer_pin.select_bit = Timer0_16_bit,
};

/******************************/

mq2_t mq2_pin = 
{
    .MQ2_pin_digital.direction = INPUT,
    .MQ2_pin_digital.pin = pin4,
    .MQ2_pin_digital.port = PORTC_INDEX,
    .MQ2_pin_analog.ADC_pin.direction = INPUT,
    .MQ2_pin_analog.ADC_pin.pin = pin0,
    .MQ2_pin_analog.ADC_pin.port = PORTA_INDEX,
    .MQ2_pin_analog.ANx = ADC_AN_0,
    .MQ2_pin_analog.Frequency = ADC_FOSC_16,
    .MQ2_pin_analog.Justified = ADC_Right,
    .MQ2_pin_analog.Time = ADC_TAD_12,
    .MQ2_pin_analog.Volte = ADC_VCC_GND,
};

/******************************/

line_tracker_3_pin line_tracker = 
{
    .center.direction = INPUT,
    .center.pin = pin0,
};

void ecu_layer_initialize(void)
{  
    std_ReturneType ret = E_OK ;
    
}

/******************************/

/* Function of ISR OF INTx and RBx */

void INT0_APP_ISR(void)
{
       
}

void INT1_APP_ISR(void)
{
    
}

void INT2_APP_ISR(void)
{
    led_turn_toggle(&led2);
}

void RB4_HIGH_Int_APP_ISR(void)
{
    
}

void RB4_LOW_Int_APP_ISR(void)
{
    
}

void RB5_HIGH_Int_APP_ISR(void)
{
    
}

void RB5_LOW_Int_APP_ISR(void)
{
    
}

void RB6_HIGH_Int_APP_ISR(void)
{
    led_turn_on(&led2);
}

void RB6_LOW_Int_APP_ISR(void)
{
    led_turn_off(&led2);
}

void RB7_HIGH_Int_APP_ISR(void)
{
    led_turn_on(&led3);
}

void RB7_LOW_Int_APP_ISR(void)
{
    led_turn_off(&led3);
}

void CCP1_Int_APP_ISR(void)
{
    int_flag++;
}

/******************************/
