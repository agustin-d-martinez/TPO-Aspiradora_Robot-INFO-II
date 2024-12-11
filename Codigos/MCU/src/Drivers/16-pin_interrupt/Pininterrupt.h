/*******************************************************************************************************************************//**
 *
 * @file		Pininterrupt.h
 * @brief		Clase para entradas con interrupciones por flanco.
 * @date		17 sep. 2022
 * @author		Grupo 4
 *
 **********************************************************************************************************************************/
#ifndef PININTERRUPT_H_
#define PININTERRUPT_H_
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "gpio.h"
#include <LPC845.h>
using namespace std;
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
 *** IMPLANTACION DE LA CLASE
 **********************************************************************************************************************************/
class Pin_interrupt : protected gpio
{
public:
	static 	uint8_t m_cant;					/*	PARA VERIFICAR QUE NO SE CREEN MAS DE 8	*/
	const 	uint8_t m_interrupt_number;
	const 	uint8_t	m_interrput_mode;

public:
	Pin_interrupt( uint8_t port , uint8_t bit , uint8_t gpio_mode , uint8_t activity , uint8_t intrp_mode);
	void EnableInterupt ( void );
	void DisableInterupt ( void );
	void PinInterrupt_Inicializar( void );
	virtual void GpioHandler(void) = 0;
	virtual ~Pin_interrupt();
private:
	void PinInterrupt_Enable_clock( void );

};

#if defined (__cplusplus)
	extern "C" {
	void PININT0_IRQHandler(void);
	}
	extern "C" {
	void PININT1_IRQHandler(void);
	}
	extern "C" {
	void PININT2_IRQHandler(void);
	}
	extern "C" {
	void PININT3_IRQHandler(void);
	}
	extern "C" {
	void PININT4_IRQHandler(void);
	}
	extern "C" {
	void PININT5_IRQHandler(void);
	}
	extern "C" {
	void PININT6_IRQHandler(void);
	}
	extern "C" {
	void PININT7_IRQHandler(void);
	}
#endif

extern Pin_interrupt * g_gpiohandler[8];

#endif /* PININTERRUPT_H_ */
