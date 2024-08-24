#ifndef HAL_EUSART_H
#define	HAL_EUSART_H

#include "../Interrupts/mcal_internal_interrupt.h"

#define Asynchronous_mode            0x0
#define Synchronous_mode             0x1

#define eusart_selected_mode         (Asynchronous_mode)

#define transmission_16_bit          0x1
#define transmission_08_bit          0x0

#define Low_speed                    0x0
#define High_speed                   0x1

/******************************/

typedef enum
{
    Selects_8_bit_transmission,
    Selects_9_bit_transmission
}Transmit_transmission_bit;

typedef enum
{
    Selects_8_bit_Receive,
    Selects_9_bit_Receive
}Receive_transmission_bit;

typedef enum
{
    Slave_mode,
    Master_mode
}Clock_Source_Select_bit;

typedef enum
{
    Baud_Rate_Generator_is_used_08_bit,
    Baud_Rate_Generator_is_used_16_bit 
}Baud_Rate_Generator_bit;

typedef enum
{
    Baud_Rate_Asyn_08_bit_Low_speed,
    Baud_Rate_Asyn_08_bit_High_speed,
    Baud_Rate_Asyn_16_bit_Low_speed,
    Baud_Rate_Asyn_16_bit_High_speed,
    Baud_Rate_syn_08_bit, 
    Baud_Rate_syn_16_bit
}Baud_Rate_Generator;

/******************************/

#define select_EUSART_Mode_Select_bit(config)     (TXSTAbits.SYNC = config)
#define select_Transmit_transmission_bit(config)  (TXSTAbits.TX9 = config)
#define select_Receive_transmission_bit(config)   (RCSTAbits.RX9 = config)
#define select_Clock_Source_Select_bit(config)    (TXSTAbits.CSRC = config)
#define select_High_Baud_Rate_Select_bit(config)  (TXSTAbits.BRGH = config)
#define select_Baud_Rate_Generator_bit(config)    (BAUDCONbits.BRG16 = config)

/******************************/

#define Transmit_enabled()            (TXSTAbits.TXEN = 1)
#define Transmit_disabled()           (TXSTAbits.TXEN = 0)
#define Serial_port_enabled()         (RCSTAbits.SREN = 1)
#define Serial_port_disabled()        (RCSTAbits.SREN = 0)
#define receive_enabled()             (RCSTAbits.CREN = 1)
#define receive_disabled()            (RCSTAbits.CREN = 0)

#define EUSART_FRAMING_ERROR_DETECTED 1
#define EUSART_FRAMING_ERROR_CLEARED  0

#define EUSART_OVERRUN_ERROR_DETECTED 1
#define EUSART_OVERRUN_ERROR_CLEARED  0

/******************************/

typedef union
{
	struct
    {
		uint8 usart_tx_reserved : 6;
		uint8 usart_ferr : 1;
		uint8 usart_oerr : 1;
	};
	uint8 status;
}usart_error_status_t;

typedef struct
{
    Transmit_transmission_bit select_number_of_bit_transmit;
    Receive_transmission_bit select_number_of_bit_receive;
    usart_error_status_t error_status;
    uint32 RB;
    
    #if(eusart_selected_mode == Synchronous_mode)
    Clock_Source_Select_bit select_source;
    #endif

    Baud_Rate_Generator select_baud_rate_config;
    
    #if EUSART_INTERRUPT_FEATURE_ENABLE_TX == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PRIORITY_CFG usart_tx_priority;
    void (*EUSART_Tx_Interrupt_Handler)(void);
    #endif
    
    #if EUSART_INTERRUPT_FEATURE_ENABLE_RX == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PRIORITY_CFG usart_rx_priority; 
    void (*EUSART_Rx_Interrupt_Handler)(void);
    #endif

    void (*EUSART_Framing_Error_Handler)(void);
    void (*EUSART_Overrun_Error_Handler)(void);
    
}EUSART_t;

/******************************/

std_ReturneType EUSART_initialize(const EUSART_t *eusart_obj);
std_ReturneType EUSART_deinitialize(const EUSART_t *eusart_obj);
std_ReturneType EUSART_RX_Restart(void);

std_ReturneType EUSART_write_char_Blocking(uint8 eusart_char);
std_ReturneType EUSART_write_string_Blocking(uint8 *tx_string);
std_ReturneType EUSART_write_char_non_Blocking(uint8 eusart_char);
std_ReturneType EUSART_write_string_non_Blocking(uint8 *tx_string);

std_ReturneType EUSART_read_char_Blocking(uint8 *rx_char);
std_ReturneType EUSART_read_char_non_Blocking(uint8 *rx_char);

/******************************/

#endif	/* HAL_EUSART_H */