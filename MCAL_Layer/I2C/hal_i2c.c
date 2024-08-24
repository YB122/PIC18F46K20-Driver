#include "hal_i2c.h"

/******************************/

#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*I2C_INTERRUPT_HANDLER)(void) = NULL ;  
static void (*I2C_Report_Write_Collision)(void) = NULL ; 
static void (*I2C_Report_Receive_Overflow)(void) = NULL ; 
#endif

/******************************/

std_ReturneType MSSP_I2C_initialize(const mssp_i2c_t *i2c_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(i2c_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        MSSP_disable_cfg();
        
        Synchronous_Serial_Port_Mode_Select_bits(i2c_obj->i2c_cfg.i2c_mode_cfg);
        if(i2c_obj->i2c_cfg.i2c_mode == I2C_MASTER_MODE)
        {
            SSPADD = (uint8)(((_XTAL_FREQ/4.0) / i2c_obj->i2c_clock) - 1);
        }
        else if(i2c_obj->i2c_cfg.i2c_mode == I2C_SLAVE_MODE)
        {
            if(i2c_obj->i2c_cfg.i2c_general_call == I2C_general_call_Enable)
                I2C_general_call_Enable_cfg();
            else if(i2c_obj->i2c_cfg.i2c_general_call == I2C_general_call_disable)
                I2C_general_call_disable_cfg();
            else{ /* NOTHING */ }
            SSPCON1bits.WCOL  = 0 ;
            SSPCON1bits.SSPOV = 0 ;
            SSPCON1bits.CKP   = 1 ;
            SSPADD = i2c_obj->i2c_cfg.i2c_slave_address;
        }
        else
            /* NOTHING */
        
        TRISCbits.TRISC3 = INPUT ;
        TRISCbits.TRISC4 = INPUT ;
        
        if(i2c_obj->i2c_cfg.i2c_slew_rate == I2C_Slew_Rate_Enable)
            I2C_Slew_Rate_Enable_cfg();
        else if(i2c_obj->i2c_cfg.i2c_slew_rate == I2C_Slew_Rate_disable)
            I2C_Slew_Rate_disable_cfg();
        else{ /* NOTHING */ }
        
        if(i2c_obj->i2c_cfg.i2c_SMBus_control == I2C_Enable_SMBus)
            I2C_Enable_SMBus_cfg();
        else if(i2c_obj->i2c_cfg.i2c_SMBus_control == I2C_disable_SMBus)
            I2C_disable_SMBus_cfg();
        else{ /* NOTHING */ }
        
        /******************************/
        
        #if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        I2C_INTERRUPT_ENABLE();
        I2C__BUS_COL_INTERRUPT_ENABLE();
        I2C_INTERRUPT_CLEAR_FLAG();
        I2C_BUS_COL_INTERRUPT_CLEAR_FLAG();
        I2C_INTERRUPT_HANDLER = i2c_obj->I2C_INTERRUPT_HANDLER;  
        I2C_Report_Write_Collision = i2c_obj->I2C_Report_Write_Collision; 
        I2C_Report_Receive_Overflow = i2c_obj->I2C_Report_Receive_Overflow; 
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_LEVEL_ENABLE();
        if(i2c_obj->i2c_cfg.mssp_i2c_priority == HIGH_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            I2C_HIGH_PRIORITY_SET();
        }   
        else if(i2c_obj->i2c_cfg.mssp_i2c_priority == LOW_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
            I2C_LOW_PRIORITY_SET();
        }            
        else{/* Nothing */}
        if(i2c_obj->i2c_cfg.mssp_i2c_bc_priority == HIGH_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_HIGH_ENABLE();
            I2C_BUS_COL_HIGH_PRIORITY_SET();
        }   
        else if(i2c_obj->i2c_cfg.mssp_i2c_bc_priority == LOW_PRIORITY)
        {
            INTERRUPT_GLOBAL_INTERRUPT_LOW_ENABLE();
            I2C_BUS_COL_LOW_PRIORITY_SET();
        }            
        else{/* Nothing */}
        #else
        INTERRUPT_GLOBAL_INTERRUPT_ENABLE();  
        INTERRUPT_PERIPHERAL_INTERRUPT_ENABLE();
        #endif
        #endif 

        /******************************/
        
        MSSP_Enable_cfg();
        ret = E_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType MSSP_I2C_deinitialize(const mssp_i2c_t *i2c_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(i2c_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        MSSP_disable_cfg();
        #if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        I2C_INTERRUPT_DIASBLE();
        I2C_BUS_COL_INTERRUPT_DIASBLE();
        #endif
        ret = E_OK;
    }
    return ret ;
}

/******************************/

std_ReturneType MSSP_I2C_MASTER_SEND_START(const mssp_i2c_t *i2c_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(i2c_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        I2C_Start_Condition_Enable(); /* Initiate Start condition on SDA and SCL pins. Automatically cleared by hardware */
        while(SSPCON2bits.SEN);
        PIR1bits.SSPIF = 0;
        if(SSPSTATbits.S == I2C_START_BIT_DETECTED)
            ret = E_OK;
        else
            ret = E_NOT_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType MSSP_I2C_MASTER_SEND_REPEATED_START(const mssp_i2c_t *i2c_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(i2c_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        SSPCON2bits.RSEN = 1; /* Initiate Repeated Start condition on SDA and SCL pins. Automatically cleared by hardware */
        while(SSPCON2bits.RSEN);
        PIR1bits.SSPIF = 0;
        ret = E_OK;
    }
    return ret ;
}

/******************************/

std_ReturneType MSSP_I2C_MASTER_SEND_STOP(const mssp_i2c_t *i2c_obj)
{
    std_ReturneType ret = E_NOT_OK ;
    if(i2c_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        I2C_Stop_Condition_Enable(); 
        while(SSPCON2bits.PEN);
        PIR1bits.SSPIF = 0;
        if(SSPSTATbits.P == I2C_STOP_BIT_DETECTED)
            ret = E_OK;
        else
            ret = E_NOT_OK ;
    }
    return ret ;
}

/******************************/

std_ReturneType MSSP_I2C_WRITE(const mssp_i2c_t *i2c_obj , uint8 i2c_data , uint8 *ack_status)
{
    std_ReturneType ret = E_NOT_OK ;
    if(i2c_obj == NULL)
        ret = E_NOT_OK ;
    else
    {
        SSPBUF = i2c_data;
        while(!PIR1bits.SSPIF);
        PIR1bits.SSPIF = 0;
        if(I2C_Acknowledge_Transmit == SSPCON2bits.ACKSTAT)
            *ack_status = I2C_Acknowledge_Transmit;
        else
            *ack_status = I2C_not_Acknowledge_Transmit;
        ret = E_OK;
    }
    return ret ;
}

/******************************/

std_ReturneType MSSP_I2C_READ(const mssp_i2c_t *i2c_obj , uint8 i2c_ack , uint8 *i2c_data)
{
    std_ReturneType ret = E_NOT_OK ;
    if((i2c_obj == NULL) || (i2c_data == NULL))
        ret = E_NOT_OK ;
    else
    {
        I2C_Receive_Enable_bit_cfg();
        while(!SSPSTATbits.BF);
        *i2c_data = SSPBUF;
        if(i2c_ack == I2C_Acknowledge_Receive)
        {
            SSPCON2bits.ACKDT = I2C_Acknowledge_Receive;
            SSPCON2bits.ACKEN = 1;
        }
        else if(i2c_ack == I2C_not_Acknowledge_Receive)
        {
            SSPCON2bits.ACKDT = I2C_not_Acknowledge_Receive;
            SSPCON2bits.ACKEN = 1;
        }
        else
            /* NOTHING */
        ret = E_OK;
    }
    return ret ;
}

/******************************/

std_ReturneType MSSP_I2C_WRITE_BYTE(const mssp_i2c_t *i2c_obj , uint8 I2C_ADD, uint8 I2C_DATA)
{
    uint8 slave_ack;
    std_ReturneType ret = E_NOT_OK;
    ret = MSSP_I2C_MASTER_SEND_START(i2c_obj);
    ret = MSSP_I2C_WRITE(i2c_obj , I2C_ADD  , &slave_ack);
    ret = MSSP_I2C_WRITE(i2c_obj , I2C_DATA , &slave_ack);
    ret = MSSP_I2C_MASTER_SEND_STOP(i2c_obj);
    ret = E_OK;
    return ret ;
}

/******************************/

#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

void MSSP_I2C_ISR(void)
{
    I2C_INTERRUPT_CLEAR_FLAG();
    if(I2C_INTERRUPT_HANDLER)
        I2C_INTERRUPT_HANDLER();
    if(I2C_Report_Receive_Overflow)
        I2C_Report_Receive_Overflow();
}

void MSSP_I2C_BUS_COL_ISR(void)
{
    I2C_BUS_COL_INTERRUPT_CLEAR_FLAG();
    if(I2C_Report_Write_Collision)
        I2C_Report_Write_Collision();
}

#endif

/******************************/