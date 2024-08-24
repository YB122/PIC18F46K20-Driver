#include "hal_eusart.h"

/******************************/

#if EUSART_INTERRUPT_FEATURE_ENABLE_TX == INTERRUPT_FEATURE_ENABLE
static void (*EUSART_Tx_Interrupt_Handler)(void) = NULL ;        
#endif

#if EUSART_INTERRUPT_FEATURE_ENABLE_RX == INTERRUPT_FEATURE_ENABLE
static void (*EUSART_Rx_Interrupt_Handler)(void) = NULL ;   
static void (*EUSART_Framing_Error_Handler)(void) = NULL ; 
static void (*EUSART_Overrun_Error_Handler)(void) = NULL ; 
#endif

static void EUSART_TX_initialize(const EUSART_t *eusart_obj);
static void EUSART_RX_initialize(const EUSART_t *eusart_obj);
static void EUSART_RB_Calculation(const EUSART_t *eusart_obj);

/******************************/

std_ReturneType EUSART_initialize(const EUSART_t *eusart_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(eusart_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        Serial_port_disabled();       
        EUSART_RB_Calculation(eusart_obj);
        EUSART_TX_initialize(eusart_obj);
        EUSART_RX_initialize(eusart_obj);
        Serial_port_enabled();
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType EUSART_deinitialize(const EUSART_t *eusart_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(eusart_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        Transmit_disabled();
        receive_disabled();
        Serial_port_disabled();
        
        #if EUSART_INTERRUPT_FEATURE_ENABLE_TX == INTERRUPT_FEATURE_ENABLE
        EUSART_INTERRUPT_DIASBLE_TX();
        #endif

        #if EUSART_INTERRUPT_FEATURE_ENABLE_RX == INTERRUPT_FEATURE_ENABLE
        EUSART_INTERRUPT_DIASBLE_RX();
        #endif

        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType EUSART_RX_Restart(void)
{
    std_ReturneType ret = E_NOT_OK ;
    receive_disabled();
    receive_enabled();
    ret = E_OK ;
    return ret ;
}

/******************************/

std_ReturneType EUSART_write_char_Blocking(uint8 eusart_char)
{
    std_ReturneType ret = E_NOT_OK ;
    while(!TXSTAbits.TRMT);
    #if EUSART_INTERRUPT_FEATURE_ENABLE_TX == INTERRUPT_FEATURE_ENABLE
    EUSART_INTERRUPT_ENABLE_TX();
    #endif
    TXREG = eusart_char ;
    ret = E_OK ;
    return ret ;
}

/******************************/

std_ReturneType EUSART_write_string_Blocking(uint8 *tx_string)
{
    std_ReturneType ret = E_NOT_OK ;
    if(tx_string == NULL)
        ret = E_NOT_OK ;
    else
    {
        uint8 str_len = (uint8)strlen((char*)tx_string) ;
        uint8 char_counter = 0 ;
        for(char_counter = 0  ; char_counter < str_len ; char_counter++)
            ret = EUSART_write_char_Blocking(tx_string[char_counter]);
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType EUSART_write_char_non_Blocking(uint8 eusart_char)
{
    std_ReturneType ret = E_NOT_OK ;
    TXREG = eusart_char ;    
    ret = E_OK ;
    return ret ;
}

/******************************/

std_ReturneType EUSART_write_string_non_Blocking(uint8 *tx_string)
{
    std_ReturneType ret = E_NOT_OK ;
    if(tx_string == NULL)
        ret = E_NOT_OK ;
    else
    {
        uint8 str_len = (uint8)strlen((char*)tx_string) ;
        uint8 char_counter = 0 ;
        for(char_counter = 0  ; char_counter < str_len ; char_counter++)
            ret = EUSART_write_char_non_Blocking(tx_string[char_counter]);
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType EUSART_read_char_Blocking(uint8 *rx_char)
{
    std_ReturneType ret = E_NOT_OK ;
    if(rx_char == NULL)
        ret = E_NOT_OK ;
    else
    {
        while(!PIR1bits.RCIF);
        #if EUSART_INTERRUPT_FEATURE_ENABLE_RX == INTERRUPT_FEATURE_ENABLE
        EUSART_INTERRUPT_ENABLE_RX();
        #endif
        *rx_char = RCREG ;
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType EUSART_read_char_non_Blocking(uint8 *rx_char)
{
    std_ReturneType ret = E_NOT_OK ;
    if(rx_char == NULL)
        ret = E_NOT_OK ;
    else
    {
        if(1 == PIR1bits.RCIF)
        {
            *rx_char = RCREG;
            ret = E_OK ;
        }
        else
            ret = E_NOT_OK ;  
    }
    return ret ;
}

/******************************/

#if EUSART_INTERRUPT_FEATURE_ENABLE_TX == INTERRUPT_FEATURE_ENABLE
void EUSART_TX_ISR(void)
{
    EUSART_INTERRUPT_DIASBLE_TX();
    if(EUSART_Tx_Interrupt_Handler)
        EUSART_Tx_Interrupt_Handler();
}
#endif

/******************************/

#if EUSART_INTERRUPT_FEATURE_ENABLE_RX == INTERRUPT_FEATURE_ENABLE
void EUSART_RX_ISR(void)
{
    EUSART_INTERRUPT_DIASBLE_RX();
    if(EUSART_Rx_Interrupt_Handler)
        EUSART_Rx_Interrupt_Handler();
    if(EUSART_Framing_Error_Handler)
        EUSART_Framing_Error_Handler();
    if(EUSART_Overrun_Error_Handler)
        EUSART_Overrun_Error_Handler();
}
#endif

/******************************/

static void EUSART_RB_Calculation(const EUSART_t *eusart_obj)
{
    float BR_local = 0 ;
    switch(eusart_obj->select_baud_rate_config)
    {
        case Baud_Rate_Asyn_08_bit_Low_speed : 
            select_EUSART_Mode_Select_bit(Asynchronous_mode);
            select_High_Baud_Rate_Select_bit(Low_speed);
            select_Baud_Rate_Generator_bit(transmission_08_bit);
            BR_local = (float)(((((float)_XTAL_FREQ)/(64.0 * (float)(eusart_obj->RB))) - 1 ));
            break;
        case Baud_Rate_Asyn_08_bit_High_speed : 
            select_EUSART_Mode_Select_bit(Asynchronous_mode);
            select_High_Baud_Rate_Select_bit(High_speed);
            select_Baud_Rate_Generator_bit(transmission_08_bit);
            BR_local = (float)(((((float)_XTAL_FREQ)/(16.0 * (float)(eusart_obj->RB))) - 1 ));
            break;
        case Baud_Rate_Asyn_16_bit_Low_speed : 
            select_EUSART_Mode_Select_bit(Asynchronous_mode);
            select_High_Baud_Rate_Select_bit(Low_speed);
            select_Baud_Rate_Generator_bit(transmission_16_bit);
            BR_local = (float)(((((float)_XTAL_FREQ)/(16.0 * (float)(eusart_obj->RB))) - 1 ));
            break;
        case Baud_Rate_Asyn_16_bit_High_speed : 
            select_EUSART_Mode_Select_bit(Asynchronous_mode);
            select_High_Baud_Rate_Select_bit(High_speed);
            select_Baud_Rate_Generator_bit(transmission_16_bit);
            BR_local = (float)(((((float)_XTAL_FREQ)/(4.0 * (float)(eusart_obj->RB))) - 1 ));
            break;
        case Baud_Rate_syn_08_bit : 
            select_EUSART_Mode_Select_bit(Synchronous_mode);
            select_Baud_Rate_Generator_bit(transmission_08_bit);
            BR_local = (float)(((((float)_XTAL_FREQ)/(4.0 * (float)(eusart_obj->RB))) - 1 ));
            break;
        case Baud_Rate_syn_16_bit : 
            select_EUSART_Mode_Select_bit(Synchronous_mode);
            select_Baud_Rate_Generator_bit(transmission_16_bit);
            BR_local = (float)(((((float)_XTAL_FREQ)/(4.0 * (float)(eusart_obj->RB))) - 1 ));
            break;
        default :
            break;
    }
    SPBRG  = (uint8)((uint32)BR_local);
    SPBRGH = (uint8)(((uint32)BR_local) >> 8);
    
}

/******************************/

static void EUSART_TX_initialize(const EUSART_t *eusart_obj)
{
    Transmit_enabled();
    TRISCbits.RC6 = 1 ;
    #if EUSART_INTERRUPT_FEATURE_ENABLE_TX == INTERRUPT_FEATURE_ENABLE
    EUSART_INTERRUPT_ENABLE_TX();
    EUSART_Tx_Interrupt_Handler = eusart_obj->EUSART_Tx_Interrupt_Handler;
    
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PRIORITY_LEVEL_ENABLE();
    if(eusart_obj->usart_tx_priority == HIGH_PRIORITY)
    {
        INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
        EUSART_HIGH_PRIORITY_SET_TX();
    }   
    else if(eusart_obj->usart_tx_priority == LOW_PRIORITY)
    {
        INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
        EUSART_LOW_PRIORITY_SET_TX();
    }            
    else{/* Nothing */}
    #else
    INTERRUPT_GLOBAL_INTERRUPT_ENABLE();  
    INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        
    #endif

    #else
    EUSART_INTERRUPT_DIASBLE_TX();
    
    #endif
    select_Transmit_transmission_bit(eusart_obj->select_number_of_bit_transmit);
        
}

/******************************/

static void EUSART_RX_initialize(const EUSART_t *eusart_obj)
{
    receive_enabled();
    TRISCbits.RC7 = 1 ;
    #if EUSART_INTERRUPT_FEATURE_ENABLE_RX == INTERRUPT_FEATURE_ENABLE
    EUSART_INTERRUPT_ENABLE_RX();
    EUSART_Rx_Interrupt_Handler = eusart_obj->EUSART_Rx_Interrupt_Handler;
    
    #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_PRIORITY_LEVEL_ENABLE();
    if(eusart_obj->usart_rx_priority == HIGH_PRIORITY)
    {
        INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
        EUSART_HIGH_PRIORITY_SET_RX();
    }   
    else if(eusart_obj->usart_rx_priority == LOW_PRIORITY)
    {
        INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
        EUSART_LOW_PRIORITY_SET_RX();
    }            
    else{/* Nothing */}
    #else
    INTERRUPT_GLOBAL_INTERRUPT_ENABLE();  
    INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        
    #endif
    #else 
    EUSART_INTERRUPT_DIASBLE_RX();
    
    #endif
    select_Receive_transmission_bit(eusart_obj->select_number_of_bit_receive);
}

/******************************/