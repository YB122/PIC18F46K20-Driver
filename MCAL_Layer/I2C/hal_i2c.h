#ifndef HAL_I2C_H
#define	HAL_I2C_H

/******************************/

#include "../Interrupts/mcal_internal_interrupt.h"

/******************************/

#define I2C_Slew_Rate_Enable                                0
#define I2C_Slew_Rate_disable                               1

#define I2C_Enable_SMBus                                    1
#define I2C_disable_SMBus                                   0

#define last_byte_received_or_transmitted_data              1
#define last_byte_received_or_transmitted_address           0

#define I2C_START_BIT_DETECTED                              1
#define I2C_START_BIT_NOT_DETECTED                          0

#define I2C_STOP_BIT_DETECTED                               1
#define I2C_STOP_BIT_NOT_DETECTED                           0

#define I2C_MASTER_MODE                                     1
#define I2C_SLAVE_MODE                                      0

#define I2C_Slave_mode_7_bit_address                        6                    
#define I2C_Slave_mode_10_bit_address                       7
#define I2C_Master_mode_with_clock                          8
#define I2C_Firmware_Controlled_Master_mode                 11
#define I2C_Slave_mode_7_bit_address_with_interrupts        14
#define I2C_Slave_mode_10_bit_address_with_interrupts       15

#define I2C_general_call_Enable                             1
#define I2C_general_call_disable                            0

/* Master Transmit mode only */
#define I2C_not_Acknowledge_Transmit                        1
#define I2C_Acknowledge_Transmit                            0

/* Master Receive mode only */
#define I2C_not_Acknowledge_Receive                         1
#define I2C_Acknowledge_Receive                             0

#define I2C_Receive_Enable_bit                              1
#define I2C_Receive_disable_bit                             0

/******************************/

#define I2C_Slew_Rate_Enable_cfg()                          (SSPSTATbits.SMP = 0)
#define I2C_Slew_Rate_disable_cfg()                         (SSPSTATbits.SMP = 1)

#define I2C_Enable_SMBus_cfg()                              (SSPSTATbits.CKE = 1)
#define I2C_disable_SMBus_cfg()                             (SSPSTATbits.SMP = 0)

#define Synchronous_Serial_Port_Mode_Select_bits(config)    (SSPCON1bits.SSPM = config)

#define I2C_general_call_Enable_cfg()                       (SSPCON2bits.GCEN = 1)
#define I2C_general_call_disable_cfg()                      (SSPCON2bits.GCEN = 0)

#define I2C_Receive_Enable_bit_cfg()                        (SSPCON2bits.RCEN = 1)
#define I2C_Receive_disable_bit_cfg()                       (SSPCON2bits.RCEN = 0)

#define MSSP_Enable_cfg()                                   (SSPCON1bits.SSPEN = 1)
#define MSSP_disable_cfg()                                  (SSPCON1bits.SSPEN = 0)

#define I2C_Start_Condition_Enable()                        (SSPCON2bits.SEN = 1)
#define I2C_Start_Condition_disable()                       (SSPCON2bits.SEN = 0)

#define I2C_Stop_Condition_Enable()                         (SSPCON2bits.PEN = 1)
#define I2C_Stop_Condition_disable()                        (SSPCON2bits.PEN = 0)

/******************************/

typedef struct
{
	uint8 i2c_mode_cfg ;             /* Master Synchronous Serial Port Mode Select */
    uint8 i2c_slave_address ;        /* I2C Slave Address */
	uint8 i2c_mode : 1 ;				/* I2C : Master or Slave Mode */
	uint8 i2c_slew_rate : 1 ; 		/* Slew Rate Enable/Disable */
	uint8 i2c_SMBus_control : 1 ; 	/* SMBus Enable/Disable */
	uint8 i2c_general_call : 1 ;		/* General Call Enable/Disable */
	uint8 i2c_master_rec_mode : 1 ; 	/* Master Receive Mode Enable/Disable */
	uint8 i2c_reserved : 3 ; 
    #if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PRIORITY_CFG mssp_i2c_priority;
    INTERRUPT_PRIORITY_CFG mssp_i2c_bc_priority;
    #endif   
}i2c_configs_t;

typedef struct
{
	uint32 i2c_clock;	/* Master Clock Frequency */
    i2c_configs_t i2c_cfg; /* I2C Configurations */
    #if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void (*I2C_Report_Write_Collision)(void);	/* Write Collision Indicator */
    void (*I2C_INTERRUPT_HANDLER)(void); 	    /* Default Interrupt Handler */
    void (*I2C_Report_Receive_Overflow)(void); 	/* Receive Overflow Indicator */
    #endif    
}mssp_i2c_t;

/******************************/

std_ReturneType MSSP_I2C_initialize(const mssp_i2c_t *i2c_obj);
std_ReturneType MSSP_I2C_deinitialize(const mssp_i2c_t *i2c_obj);
std_ReturneType MSSP_I2C_MASTER_SEND_START(const mssp_i2c_t *i2c_obj);
std_ReturneType MSSP_I2C_MASTER_SEND_REPEATED_START(const mssp_i2c_t *i2c_obj);
std_ReturneType MSSP_I2C_MASTER_SEND_STOP(const mssp_i2c_t *i2c_obj);
std_ReturneType MSSP_I2C_WRITE(const mssp_i2c_t *i2c_obj , uint8 i2c_data , uint8 *ack_status);
std_ReturneType MSSP_I2C_READ(const mssp_i2c_t *i2c_obj , uint8 i2c_ack , uint8 *i2c_data);
std_ReturneType MSSP_I2C_WRITE_BYTE(const mssp_i2c_t *i2c_obj , uint8 I2C_ADD, uint8 I2C_DATA);

#endif	/* HAL_I2C_H */