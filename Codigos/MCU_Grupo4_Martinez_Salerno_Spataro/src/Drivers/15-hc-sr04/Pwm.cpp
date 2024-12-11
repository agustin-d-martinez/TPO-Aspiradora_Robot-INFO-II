/**********************************************************************************************************************************
 *
 * @file		Pwm.cpp
 * @brief		Generador de PWM sin interrupción
 * @date		7 oct. 2022
 * @author		Técnico. Martinez Agustin
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Drivers/15-hc-sr04/Pwm.h>
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


Pwm::Pwm( uint8_t puerto , uint8_t bit , uint8_t actividad , pwm_channel_t number )
: m_port( puerto ) , m_bit(bit) , m_activity ( actividad ) , m_pwm_channel ( number )
{
	m_ton = 0;
	m_toff = 0;
}
/**
	\fn void SetTon( uint32_t time , pwm_time_unit_t t )
	\brief Seteo el tiempo de encendido del PWM.
 	\details Utilizando los regristros con SetTime creo el tiempo de encendido de mi PWM.
 	\param	Tiempo de encendido.
 	\param	Unidad de medida del tiempo de encendido.
	\return void
*/
void Pwm::SetTon( uint32_t time , pwm_time_unit_t t )
{
	m_ton = time;
	if ( t == MILI_SEG )
		m_ton *= 1000;
	if ( t == SEG )
		m_ton  *= 1000000;

	SetTime(m_ton * (FREQ_PRINCIPAL / 1000000), m_pwm_channel);
}
/**
	\fn void SetPeriod( uint32_t time , pwm_time_unit_t t)
	\brief Seteo el periodo del PWM.
 	\details Utilizando los regristros con SetTime creo el tiempo de apagado de mi PWM.
 	\param	Tiempo del periodo.
 	\param	Unidad de medida del tiempo de periodo.
	\return void
*/
void Pwm::SetPeriod( uint32_t time , pwm_time_unit_t t)
{
	m_toff = time;
	if ( t == MILI_SEG )
		m_toff *= 1000;
	if ( t == SEG )
		m_toff  *= 1000000;
	m_toff = m_toff - m_ton;

	SetTime((m_ton + m_toff) * (FREQ_PRINCIPAL / 1000000), 0);
}
/**
	\fn void Inicializar( uint32_t ton , uint32_t toff , pwm_time_unit_t t )
	\brief Inicializo el PWM.
 	\details Utilizando los regristros configuro todo para la utilizacion del PWM.
 	\param	Tiempo de encendido.
 	\param	Tiempo de apagado (no es el periodo. El periodo es la suma de ambos).
 	\param	Unidad de medida de los tiempos de encendido y apagado.
	\return void
*/
void Pwm::Inicializar( uint32_t ton , uint32_t toff , pwm_time_unit_t t )
{
	SetSwitchMatrizSCTOUT( m_bit , m_port , m_pwm_channel - 1 );

	SetUnify(true);
	SetAutoLimit(true);

	m_ton = ton;
	m_toff = toff;
	if ( t == SEG )
	{
		m_ton  *= 1000000;
		m_toff *= 1000000;
	}
	if ( t == MILI_SEG )
	{
		m_ton  *= 1000;
		m_toff *= 1000;
	}
	SetTime((m_ton + m_toff) * (FREQ_PRINCIPAL / 1000000), 0);	/*	CHANNEL 0 ALWAYS IS THE PERIOD	*/
	SetTime( m_ton * (FREQ_PRINCIPAL / 1000000), m_pwm_channel);	/*	Setteo del tiempo de encendido	*/

	if ( m_activity == gpio::high )
	{
		SCT->OUT[m_pwm_channel - 1].SET = (1 << 0); // event 0 sets OUT0
		SCT->OUT[m_pwm_channel - 1].CLR = (1 << m_pwm_channel); // event 1 clear OUT0

		SCT->OUTPUT &= ~( 1 << (m_pwm_channel - 1)); // default clear OUT[m_pwm_channel]
		SCT->RES &= ~( 0b11 << ((m_pwm_channel - 1)* 2)); 	// limpio el res en caso de que tenga algo
		SCT->RES |= ( 0b10 << ((m_pwm_channel - 1)* 2)); 	// conflict: Inactive state takes precedence
	}
	else
	{
		SCT->OUT[m_pwm_channel - 1].CLR = (1 << 0);
		SCT->OUT[m_pwm_channel - 1].SET = (1 << m_pwm_channel);


		SCT->OUTPUT |= ( 1 << (m_pwm_channel - 1));
		SCT->RES &= ~( 0b11 << ((m_pwm_channel - 1)* 2)); 	// limpio el res en caso de que tenga algo
		SCT->RES |= ( 0b01 << ((m_pwm_channel - 1)* 2)); 	// conflict: active state takes precedence
	}
}
/**
	\fn void On( void )
	\brief Enciende el PWM.
 	\details Utiliza los registros con StarTimer para habilitar la salida.
	\return void
*/
void Pwm::On( void )
{
	StartTimer();
}
/**
	\fn void Off( void )
	\brief Apaga el PWM.
 	\details Utiliza los registros con StopTimer para deshabilitar la salida.
	\return void
*/
void Pwm::Off( void )
{
	StopTimer();
}


Pwm::~Pwm()
{ }
