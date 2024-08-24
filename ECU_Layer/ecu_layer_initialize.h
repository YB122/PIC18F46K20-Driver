#ifndef ECU_LAYER_INITIALIZE_H
#define	ECU_LAYER_INITIALIZE_H

#define _XTAL_FREQ 8000000

/**************************************/

#include "LED/ecu_led.h"
#include "button/ecu_button.h"
#include "relay/ecu_relay.h"
#include "DC_MOTOR/ecu_dc_motor.h"
#include "7_Segment/ecu_seven_segment.h"
#include "KeyPad/ecu_Keypad.h"
#include "Chr_LCD/ecu_chr_lcd.h"
#include "../MCAL_Layer/Interrupts/mcal_external_interrupt.h"
#include "../MCAL_Layer/Interrupts/mcal_internal_interrupt.h"
#include "../MCAL_Layer/Interrupts/mcal_interrupt_manger.h"
#include "../MCAL_Layer/EEPROM/hal_eeprom.h"
#include "../MCAL_Layer/ADC/hal_adc.h"
#include "../MCAL_Layer/TIMER0/timer0_hal.h"
#include "../MCAL_Layer/TIMER1/timer1_hal.h"
#include "../MCAL_Layer/TIMER2/timer2_hal.h"
#include "../MCAL_Layer/TIMER3/timer3_hal.h"
#include "../MCAL_Layer/CCP1/hal_ccp1.h"
#include "servo_motor/servo_motor.h"
#include "../MCAL_Layer/EUSART/hal_eusart.h"
#include "../MCAL_Layer/I2C/hal_i2c.h"
#include "Ultrasonic_Sensor/Ultrasonic_Sensor.h"
#include "LM35/LM35.h"
#include "4_channel_line_tracker/line_tracker.h"
#include "JOY_STICK/joy_stick.h"
#include "MQ2/mq2.h"
#include "DHT11/dht11.h"
//#include "servo_motor/servo_motor.h"

/**************************************/

void ecu_layer_initialize(void);

#endif	/* ECU_LAYER_INITIALIZE_H */

