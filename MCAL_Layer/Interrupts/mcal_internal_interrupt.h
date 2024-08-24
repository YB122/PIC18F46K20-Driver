#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/******************************/

#include "mcal_interrupt_config.h"

/******************** ADC ********************/

#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define ADC_INTERRUPT_DIASBLE()       (PIE1bits.ADIE = 0)
#define ADC_INTERRUPT_ENABLE()        (PIE1bits.ADIE = 1)

#define ADC_INTERRUPT_CLEAR_FLAG()    (PIR1bits.ADIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define ADC_HIGH_PRIORITY_SET()       (IPR1bits.ADIP = 1)
#define ADC_LOW_PRIORITY_SET()        (IPR1bits.ADIP = 0)

#endif
#endif

/******************** TIMER0 ********************/

#if TImer0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define TIMER0_INTERRUPT_DIASBLE()    (INTCONbits.TMR0IE = 0)
#define TIMER0_INTERRUPT_ENABLE()     (INTCONbits.TMR0IE = 1)

#define TIMER0_INTERRUPT_CLEAR_FLAG() (INTCONbits.TMR0IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define TIMER0_HIGH_PRIORITY_SET()    (INTCON2bits.TMR0IP = 1)
#define TIMER0_LOW_PRIORITY_SET()     (INTCON2bits.TMR0IP = 0)

#endif
#endif

/******************** TIMER1 ********************/

#if TImer1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define TIMER1_INTERRUPT_DIASBLE()    (PIE1bits.TMR1IE = 0)
#define TIMER1_INTERRUPT_ENABLE()     (PIE1bits.TMR1IE = 1)

#define TIMER1_INTERRUPT_CLEAR_FLAG() (PIR1bits.TMR1IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define TIMER1_HIGH_PRIORITY_SET()    (IPR1bits.TMR1IP = 1)
#define TIMER1_LOW_PRIORITY_SET()     (IPR1bits.TMR1IP = 0)

#endif
#endif

/******************** TIMER2 ********************/

#if TImer2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define TIMER2_INTERRUPT_DIASBLE()    (PIE1bits.TMR2IE = 0)
#define TIMER2_INTERRUPT_ENABLE()     (PIE1bits.TMR2IE = 1)

#define TIMER2_INTERRUPT_CLEAR_FLAG() (PIR1bits.TMR2IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define TIMER2_HIGH_PRIORITY_SET()    (IPR1bits.TMR2IP = 1)
#define TIMER2_LOW_PRIORITY_SET()     (IPR1bits.TMR2IP = 0)

#endif
#endif

/******************** TIMER3 ********************/

#if TImer3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define TIMER3_INTERRUPT_DIASBLE()    (PIE2bits.TMR3IE = 0)
#define TIMER3_INTERRUPT_ENABLE()     (PIE2bits.TMR3IE = 1)

#define TIMER3_INTERRUPT_CLEAR_FLAG() (PIR2bits.TMR3IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define TIMER3_HIGH_PRIORITY_SET()    (IPR2bits.TMR3IP = 1)
#define TIMER3_LOW_PRIORITY_SET()     (IPR2bits.TMR3IP = 0)

#endif
#endif

/******************** CCP1 ********************/

#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define CCP1_INTERRUPT_DIASBLE()    (PIE1bits.CCP1IE = 0)
#define CCP1_INTERRUPT_ENABLE()     (PIE1bits.CCP1IE = 1)

#define CCP1_INTERRUPT_CLEAR_FLAG() (PIR1bits.CCP1IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define CCP1_HIGH_PRIORITY_SET()    (IPR1bits.CCP1IP = 1)
#define CCP1_LOW_PRIORITY_SET()     (IPR1bits.CCP1IP = 0)

#endif
#endif

/******************** CCP2 ********************/

#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define CCP2_INTERRUPT_DIASBLE()    (PIE2bits.CCP2IE = 0)
#define CCP2_INTERRUPT_ENABLE()     (PIE2bits.CCP2IE = 1)

#define CCP2_INTERRUPT_CLEAR_FLAG() (PIR2bits.CCP2IF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define CCP2_HIGH_PRIORITY_SET()    (IPR2bits.CCP2IP = 1)
#define CCP2_LOW_PRIORITY_SET()     (IPR2bits.CCP2IP = 0)

#endif
#endif

/******************** EUSART_TX ********************/

#if EUSART_INTERRUPT_FEATURE_ENABLE_TX == INTERRUPT_FEATURE_ENABLE

#define EUSART_INTERRUPT_DIASBLE_TX()    (PIE1bits.TXIE = 0)
#define EUSART_INTERRUPT_ENABLE_TX()     (PIE1bits.TXIE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EUSART_HIGH_PRIORITY_SET_TX()    (IPR1bits.TXIP = 1)
#define EUSART_LOW_PRIORITY_SET_TX()     (IPR1bits.TXIP = 0)

#endif
#endif

/******************** EUSART_RX ********************/

#if EUSART_INTERRUPT_FEATURE_ENABLE_RX == INTERRUPT_FEATURE_ENABLE

#define EUSART_INTERRUPT_DIASBLE_RX()    (PIE1bits.RCIE = 0)
#define EUSART_INTERRUPT_ENABLE_RX()     (PIE1bits.RCIE = 1)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define EUSART_HIGH_PRIORITY_SET_RX()    (IPR1bits.RCIP = 1)
#define EUSART_LOW_PRIORITY_SET_RX()     (IPR1bits.RCIP = 0)

#endif
#endif

/******************** I2C ********************/

#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE

#define I2C_INTERRUPT_DIASBLE()                   (PIE1bits.SSPIE = 0)
#define I2C_INTERRUPT_ENABLE()                    (PIE1bits.SSPIE = 1)

#define I2C_BUS_COL_INTERRUPT_DIASBLE()           (PIE2bits.BCLIE = 0)
#define I2C__BUS_COL_INTERRUPT_ENABLE()           (PIE2bits.BCLIE = 1)

#define I2C_INTERRUPT_CLEAR_FLAG()                (PIR1bits.SSPIF = 0)
#define I2C_BUS_COL_INTERRUPT_CLEAR_FLAG()        (PIR2bits.BCLIF = 0)

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

#define I2C_HIGH_PRIORITY_SET()                   (IPR1bits.SSPIP = 1)
#define I2C_LOW_PRIORITY_SET()                    (IPR1bits.SSPIP = 0)

#define I2C_BUS_COL_HIGH_PRIORITY_SET()           (IPR2bits.BCLIP = 1)
#define I2C_BUS_COL_LOW_PRIORITY_SET()            (IPR2bits.BCLIP = 0)

#endif
#endif

#endif	/* MCAL_INTERNAL_INTERRUPT_H */