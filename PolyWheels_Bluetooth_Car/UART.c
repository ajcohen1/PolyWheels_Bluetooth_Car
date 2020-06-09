#include <stdint.h>
#include "UART.h"
#include "MotorDriver.h"

void UART_init(void) {
    // UART: UCA2
    P3->SEL0    |=   ( BIT2 | BIT3 );
    P3->SEL1    &=  ~( BIT2 | BIT3 );

    EUSCI_A2->CTLW0   |=   EUSCI_A_CTLW0_SWRST;                                       // eUSCI in RESET
    EUSCI_A2->CTLW0    =   ( EUSCI_A_CTLW0_SWRST | EUSCI_A_CTLW0_SSEL__SMCLK );       // Select clock source from SMCLK ~ 4MHz
    // Baud Rate calculation
    // 3000000/9600/16 = 19.53125
    // Fractional portion = 0.53125
    // User's Guide Table 21-4: UCBRSx = 0xAA ( 170 )
    // UCBRFx = int ( ( 19.53125 - 19 ) * 16 ) = 8.5 ~ 9
    EUSCI_A2->BRW      =   19;                                                        // 3000000/16/9600 = 19.53125
    EUSCI_A2->MCTLW    =   ( 170 << EUSCI_A_MCTLW_BRS_OFS ) | ( 9 << EUSCI_A_MCTLW_BRF_OFS ) | EUSCI_A_MCTLW_OS16;
    EUSCI_A2->CTLW0   &=  ~EUSCI_A_CTLW0_SWRST;                                       // Initialize eUSCI

    EUSCI_A2->IFG     &=  ~EUSCI_A_IFG_RXIFG;                                         // Clear eUSCI RX interrupt flag
    EUSCI_A2->IE      |=   EUSCI_A_IE_RXIE;                                           // Enable USCI_A0 RX interrupt

    NVIC_EnableIRQ    ( EUSCIA2_IRQn );
    NVIC_SetPriority  ( EUSCIA2_IRQn, 0 );
}

void EUSCIA2_IRQHandler (void)
{
    if (EUSCI_A2->IFG & EUSCI_A_IFG_RXIFG)
        setMotion(EUSCI_A2->RXBUF);
}
