#ifndef _P_UART_H
#define _P_UART_H

#include "peripherals/base.h"

#define UART_DR_REG        (PBASE+0x00201000)
#define UART_RSRECR_REG    (PBASE+0x00201004)
#define UART_FR_REG        (PBASE+0x00201018)
#define UART_ILPR_REG      (PBASE+0x00201020)
#define UART_IBRD_REG      (PBASE+0x00201024)
#define UART_FBRD_REG      (PBASE+0x00201028)
#define UART_LCRH_REG      (PBASE+0x0020102c)
#define UART_CR_REG        (PBASE+0x00201030)
#define UART_IFLS_REG      (PBASE+0x00201034)
#define UART_IMSC_REG      (PBASE+0x00201038)
#define UART_RIS_REG       (PBASE+0x0020103c)
#define UART_MIS_REG       (PBASE+0x00201040)
#define UART_ICR_REG       (PBASE+0x00201044)
#define UART_DMACR_REG     (PBASE+0x00201048)
#define UART_ITCR_REG      (PBASE+0x00201080)
#define UART_ITIP_REG      (PBASE+0x00201084)
#define UART_ITOP_REG      (PBASE+0x00201088)
#define UART_TDR_REG       (PBASE+0x0020108c)

#endif /* _P_UART_H */
