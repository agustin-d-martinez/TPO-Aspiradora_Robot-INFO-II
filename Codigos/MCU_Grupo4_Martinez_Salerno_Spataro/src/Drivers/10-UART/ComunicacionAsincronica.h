/*******************************************************************************************************************************//**
 *
 * @file		usart.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		5 oct. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef I1_USART_COMUNICACIONSERIE_H_
#define I1_USART_COMUNICACIONSERIE_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "tipos.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
// extern tipo nombreVariable;
/***********************************************************************************************************************************
 *** IMPLANTACION DE UNA CLASE
 **********************************************************************************************************************************/

class ComunicacionAsincronica
{
	public:	
		ComunicacionAsincronica() {};
		virtual void Transmit ( const char * msg) = 0;
		virtual void Transmit ( void * msg , uint32_t n ) = 0;
		virtual void* Message ( void * msg , uint32_t n ) = 0;
		virtual void UART_IRQHandler (void) = 0;
		virtual ~ComunicacionAsincronica() {};
	protected:
		virtual void pushRx ( uint8_t dato ) = 0 ;
		virtual uint8_t popRx (uint8_t * dato ) = 0 ;
		virtual void pushTx ( uint8_t dato ) = 0 ;
		virtual uint8_t popTx (uint8_t * dato ) = 0 ;
};

#endif /* I1_USART_COMUNICACIONSERIE_H_ */
