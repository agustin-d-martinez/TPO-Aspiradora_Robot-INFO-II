/*******************************************************************************************************************************//**
 *
 * @file		gpio.cpp
 * @brief		Descripcion del modulo
 * @date		22 jun. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "LPC845.h"
#include "gpio.h"

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
const uint8_t IOCON_INDEX_PIO0[] = { 17,11,6,5,4,3,16,15,4,13,8,7,2,1,18,10,9,0,30,29,28,27,26,25,24,23,22,21,20,0,0,35};
const uint8_t IOCON_INDEX_PIO1[] = { 36,37,3,41,42,43,46,49,31,32,55,54,33,34,39,40,44,45,47,48,52,53,0,0,0,0,0,0,0,50,51};


/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
gpio::gpio ( uint8_t port , uint8_t bit , uint8_t mode , uint8_t direction , uint8_t activity) :
m_port ( port) , m_bit ( bit ) , m_mode ( mode ) , m_direction ( direction ) , m_activity ( activity )
{
	m_error = ok;

	if ( m_port > port1 )
		m_error = error;
	if ( m_port == port0 && m_bit > b_port0 )
		m_error = error;
	if ( m_port == port1 && m_bit > b_port1 )
		m_error = error;
}

uint8_t gpio::SetPin ( void )
{
	if ( m_error == ok )
	{
		if ( m_activity == high )
			GPIO->SET[ m_port ] |= 1 << m_bit ;
		else
			GPIO->CLR[ m_port ] |= 1 << m_bit ;
	}

	return m_error;
}

uint8_t gpio::ClrPin ( void )
{
	if ( m_error == ok )
	{
		if ( m_activity == high )
			GPIO->CLR[ m_port ] |= 1 << m_bit ;
		else
			GPIO->SET[ m_port ] |= 1 << m_bit ;
	}
	return m_error;
}

uint8_t gpio::SetTogglePin ( void )
{
	if ( m_error == ok )
	{
		GPIO->NOT [ m_port ] |= 1 << m_bit;
	}
	return m_error;
}

uint8_t gpio::SetDir ( void )
{
	if ( m_error == ok )
	{
		if ( m_direction == output)
			GPIO->DIRSET[ m_port ] |= 1 << m_bit ;
		else
			GPIO->DIRCLR[ m_port ] |= 1 << m_bit ;
	}

	return m_error ;
}

uint8_t gpio::SetToggleDir ( void )
{
	if ( m_error == ok )
		GPIO->DIRNOT[m_port] |= ( 1 << m_bit );

	return m_error;
}

uint8_t gpio::GetPin ( void ) const
{
	if ( m_error == ok )
		return (m_activity == high ) ? GPIO->B[m_port][m_bit] : !GPIO->B[m_port][m_bit];
	return m_error;
}

uint8_t gpio::SetPinMode ( void )
{
	uint32_t index = 0;
	if(m_error == ok){
		if(m_port == 0){
			index = IOCON_INDEX_PIO0[m_bit];
		}
		else if(m_port == 1){
			index = IOCON_INDEX_PIO1[m_bit];
		}
		IOCON->PIO[index] &= ~(1 << 10);
		IOCON->PIO[index] |= (m_mode << 10);
	}
	return m_error;
}

uint8_t gpio::SetPinResistor ( void )
{
	uint8_t Indice_PortPin ;

	if ( m_error == ok )
	{
		Indice_PortPin = IOCON_INDEX_PIO0[m_bit];
		if ( m_port )
			Indice_PortPin = IOCON_INDEX_PIO1[m_bit];

		IOCON->PIO[Indice_PortPin] &= ~0x180;
		IOCON->PIO[Indice_PortPin] |= m_mode << 3;
	}
	return m_error;
}

gpio& gpio::operator= ( uint8_t a )
{
	if ( a == 1 )
		SetPin();
	else if ( a == 0 )
		ClrPin();
	return *this;
}
