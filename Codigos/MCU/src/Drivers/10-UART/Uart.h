/*******************************************************************************************************************************//**
 *
 * @file		uart.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		5 oct. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef I1_USART_UART_H_
#define I1_USART_UART_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <ComunicacionAsincronica.h>
#include "LPC845.h"
//#include "tipos.h"

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

/***********************************************************************************************************************************
 *** IMPLANTACION DE UNA CLASE
 **********************************************************************************************************************************/
#if defined (__cplusplus)
	extern "C" {
	void UART0_IRQHandler ( void );
	}
#endif
#if defined (__cplusplus)
	extern "C" {
	void UART1_IRQHandler ( void );
	}
#endif
#if defined (__cplusplus)
	extern "C" {
	void UART2_IRQHandler ( void );
	}
#endif
#if defined (__cplusplus)
	extern "C" {
	void UART3_IRQHandler ( void );
	}
#endif
#if defined (__cplusplus)
	extern "C" {
	void UART4_IRQHandler ( void );
	}
#endif

class uart : public ComunicacionAsincronica
{
	private:
		USART_Type * m_usart;
		uint8_t 	*m_bufferRX;
		uint32_t	m_inxRxIn , m_inxRxOut , m_maxRx;
		uint8_t 	*m_bufferTX;
		uint32_t	m_inxTxIn , m_inxTxOut , m_maxTx;
		bool m_flagTx;
	public:
		typedef enum  { NoParidad , par = 2, impar} paridad_t;
		typedef enum  { siete_bits , ocho_bits } bits_de_datos;
		~uart();
		uart( uint8_t portTx , uint8_t pinTx , uint8_t portRx , uint8_t pinRx ,
				USART_Type * usart,uint32_t baudrate, bits_de_datos BitsDeDatos, paridad_t paridad ,
				uint32_t maxRx , uint32_t maxTx);

		void Transmit ( const char * msg) ;
		void Transmit ( void * msg , uint32_t n );
		void* Message ( void * msg , uint32_t n );
		void UART_IRQHandler (void);
	private:
		void pushRx ( uint8_t dato ) ;
		uint8_t popRx (uint8_t * dato ) ;
		void pushTx ( uint8_t dato ) ;
		uint8_t popTx (uint8_t * dato ) ;
		void EnableInterupt (  void );
		void DisableInterupt (  void );
};

#endif /* I1_USART_UART_H_ */
