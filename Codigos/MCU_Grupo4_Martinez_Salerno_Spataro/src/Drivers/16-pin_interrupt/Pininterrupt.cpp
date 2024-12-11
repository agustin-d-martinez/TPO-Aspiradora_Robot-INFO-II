/**********************************************************************************************************************************
 *
 * @file		Pininterrupt.cpp
 * @brief		Clase para entradas con interrupciones por flanco.
 * @date		17 sep. 2022
 * @author		Grupo 4
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "Pininterrupt.h"
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
uint8_t Pin_interrupt::m_cant = 0;
/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
Pin_interrupt * g_gpiohandler[8];
/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/

/**
	\fn void PinInterrupt_Enable_clock(void)
	\brief Habilita el clock de interrupción general.
 	\details Habilito la interrupción.
	\return void
*/
void Pin_interrupt::PinInterrupt_Enable_clock( void )
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 28);	// 28 = GPIO PIN INTERRUPT
}
/**
	\fn void EnableInterupt(void)
	\brief Habilito la interrupción.
 	\details Habilito la interrupción de la pata específica que estoy utilizando.
	\return void
*/
void Pin_interrupt::EnableInterupt ( void )
{
	SYSCON->PINTSEL[m_interrupt_number] = m_bit + m_port * 32  ;
}
/**
	\fn void DisableInterupt(void)
	\brief Deshabilito la interrupción.
 	\details Deshabilito la interrupción de la pata específica que estoy utilizando.
	\return void
*/
void Pin_interrupt::DisableInterupt ( void )
{
	SYSCON->PINTSEL[m_interrupt_number] = 0 ;
}

Pin_interrupt::Pin_interrupt( uint8_t port , uint8_t bit , uint8_t gpio_mode , uint8_t activity , uint8_t intrp_mode ) :
gpio( port , bit , gpio_mode , activity , gpio::input ) , m_interrupt_number(m_cant) , m_interrput_mode(intrp_mode)
{
	g_gpiohandler[m_interrupt_number] = this;
	m_cant++;
}
/**
	\fn void PinInterrupt_Inicializar(void)
	\brief Inicializo la interrupción por pin.
 	\details Modifico todos los registros para que la interrupción por pin esté configurada.
	\return void
*/
void Pin_interrupt::PinInterrupt_Inicializar(void)
{
	if ( m_cant == 1 )
		PinInterrupt_Enable_clock();

	SYSCON->PINTSEL[m_interrupt_number] = m_bit + m_port * 32  ;
	NVIC->ISER[0] |= (1 << (24 + m_interrupt_number));

	if ( m_interrput_mode != gpio::low_level && m_interrput_mode != gpio::high_level )
		PIN_INTERRUPT->ISEL &= ~(1 << m_interrupt_number);
	else
		PIN_INTERRUPT->ISEL |= (1 << m_interrupt_number);

	if ( m_interrput_mode != gpio::falling_edge )
		PIN_INTERRUPT->SIENR |= (1 << m_interrupt_number);	/*Activo interrupticion rising edge/de nivel*/
	if ( m_interrput_mode == gpio::falling_edge || m_interrput_mode == gpio::rising_falling_edge || m_interrput_mode == gpio::high_level )
		PIN_INTERRUPT->SIENF |= (1 << m_interrupt_number);	/*Activo interrupcion falling edge / de nivel alto*/
	if ( m_interrput_mode == gpio::low_level )
		PIN_INTERRUPT->CIENF |= (1 << m_interrupt_number);	/*Activo interrupcion de nivel bajo*/

	PIN_INTERRUPT->IST |= (1 << m_interrupt_number);
}

Pin_interrupt::~Pin_interrupt()
{
	m_cant--;	/*Es solo simbólico, puesto que no se van a destruir nunca estos objetos*/
}



/* ----------------------------------
 * ----FUNCIONES INTERRUPCION------
 * ----------------------------------*/

void PININT0_IRQHandler (void)
{
	g_gpiohandler[0]->GpioHandler();
	PIN_INTERRUPT->IST |= ( 1 << 0 );			/*FINALIZO EL PEDIDO*/
}
void PININT1_IRQHandler (void)
{
	g_gpiohandler[1]->GpioHandler();
	PIN_INTERRUPT->IST |= ( 1 << 1 );	/*FINALIZO EL PEDIDO*/
}
void PININT2_IRQHandler (void)
{
	g_gpiohandler[2]->GpioHandler();
	PIN_INTERRUPT->IST |= ( 1 << 2 );	/*FINALIZO EL PEDIDO*/
}
void PININT3_IRQHandler (void)
{
	g_gpiohandler[3]->GpioHandler();
	PIN_INTERRUPT->IST |= ( 1 << 3 );	/*FINALIZO EL PEDIDO*/
}
void PININT4_IRQHandler (void)
{
	g_gpiohandler[4]->GpioHandler();
	PIN_INTERRUPT->IST |= ( 1 << 4 );	/*FINALIZO EL PEDIDO*/
}
void PININT5_IRQHandler (void)
{
	g_gpiohandler[5]->GpioHandler();
	PIN_INTERRUPT->IST |= ( 1 << 5 );	/*FINALIZO EL PEDIDO*/
}
void PININT6_IRQHandler (void)
{
	g_gpiohandler[6]->GpioHandler();
	PIN_INTERRUPT->IST |= ( 1 << 6 );	/*FINALIZO EL PEDIDO*/
}
void PININT7_IRQHandler (void)
{
	g_gpiohandler[7]->GpioHandler();
	PIN_INTERRUPT->IST |= ( 1 << 7 );	/*FINALIZO EL PEDIDO*/
}
