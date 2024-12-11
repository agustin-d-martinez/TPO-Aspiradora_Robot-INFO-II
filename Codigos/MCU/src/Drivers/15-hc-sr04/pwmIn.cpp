/**********************************************************************************************************************************
 *
 * @file		pwmIn.h
 * @brief		Pata que lee tamaños de pulsos de entrada
 * @date		22 jun. 2022
 * @author		Técnico. Martinez Agustin
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "pwmIn.h"
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
pwmIn::pwmIn( uint8_t puerto , uint8_t bit , uint8_t modo , uint8_t activity , MRT_timer_channels timer_channel ) :
Pin_interrupt( puerto , bit , modo , activity , gpio::rising_falling_edge ) , MRThandler(timer_channel) ,
m_pulse_on(2000000000)
{ }
/**
	\fn void Inicializar(void)
	\brief Inicializo el PWM_In.
 	\details Seteo dirección resistencia y habilito la interrupción por flancos.
	\return void
*/
void pwmIn::Inicializar(void)
{
	PinInterrupt_Inicializar();
	SetDir();
	SetPinResistor();
}
/**
	\fn uint32_t GetPulseOn(void)
	\brief Obtengo el largo del pulso.
 	\details Realizo la cuenta del tiempo transcurrido entre el último flanco y este.
	\return largo del pulso
*/
uint32_t pwmIn::GetPulseOn( void ) const
{
	return  ((0x7FFFFFFE - m_pulse_on) * (1000000000 / FREQ_PRINCIPAL)) / 1000;
}
/**
	\fn void Off(void)
	\brief Apago el PWM_In.
 	\details Deshabilito la interrupción y seteo el pulso a un valor gigante que no genere overflow.
	\return void
*/
void pwmIn::Off(void)
{
	DisableInterupt();
	m_pulse_on = 2000000000;	//Este número es arbitrario y se eligió para evitar un overflow al realizar la cuenta de GetPulseOn además de devolver un valor excesivamente grande
}
/**
	\fn void On(void)
	\brief Enciendo el PWM_In.
 	\details Habilito la interrupción.
	\return void
*/
void pwmIn::On(void)
{
	EnableInterupt();
}
/**
	\fn void GpioHandler(void)
	\brief Handler de la interrupción por flanco.
 	\details Si el flanco es ascendente reseteo el contador. Si es desendente guado el valor del contador. La cuenta se realiza en otra función para ahorrar tiempo acá
	\return void
*/
void pwmIn::GpioHandler(void)
{
	if ( (((PIN_INTERRUPT->FALL) >> m_interrupt_number) & 1) == 1 )	//Si es un flanco ascendente, reseteo	//
		m_pulse_on = MRT_get_time();
	if ( (((PIN_INTERRUPT->RISE) >> m_interrupt_number) & 1) == 1)	//Si es un flanco descendente, guardop el valor //
		MRT_reset_time();

}
