/*******************************************************************************************************************************//**
 *
 * @file		EntradaDigital.cpp
 * @brief		funciones miembro de la clase EntradaDigital
 * @date		27 may. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "inputs.h"

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
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
inputs::inputs( uint8_t puerto , uint8_t bit , uint8_t modo , uint8_t actividad , uint8_t MaxBounce  ):
		gpio( puerto , bit , modo , gpio::input , actividad ),m_MaxBounce(MaxBounce)
{
	// Lo engancho con el tick del sistema
	m_CountBounce = 0;
	g_Handler.push_back( this );
}

inputs::~inputs() { }

void inputs::SWhandler ( void )
{
	uint8_t BufferEntradasInstantaneo = 0 ;

	BufferEntradasInstantaneo = GetPin( );

	if ( BufferEntradasInstantaneo ^ m_BufferEntrada )
	{
		m_CountBounce++;
		if ( m_CountBounce  >= m_MaxBounce )
				m_BufferEntrada = m_BufferEntrada ^  1  ;
	}
	else
		m_CountBounce = 0 ;
}

void inputs::Inicializar ( void )
{
	SetDir( );
	SetPinResistor( );
	SetBuffer( );
}

void inputs::SetBuffer ( void )
{
	m_BufferEntrada = GetPin( );
	return ;
}
inputs& inputs::operator =( uint8_t valor )
{
	if ( valor <= 1 )
		m_BufferEntrada = valor;
	return *this;
}
uint8_t inputs::SetDir ( void )
{
	return gpio::SetDir( ) ;
}

uint8_t inputs::get ( void )
{
	return m_BufferEntrada;
}
