/*******************************************************************************************************************************//**
 *
 * @file		Reloj.h
 * @brief		Objeto que guardará el tiempo desde que se creo
 * @date		27 nov. 2022
 * @author		Técnico Martinez Agustin
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#include <Reloj.h>

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
Reloj::Reloj()
{
	Reset();
	g_Handler.push_back(this);
}
/**
	\fn void GetHour(void)
	\brief Devuelve el valor de hora.
 	\details Entrega la variable m_hora.
	\return m_hora
*/
int32_t Reloj::GetHour( void ) const
{
	return m_hora;
}
/**
	\fn void GetMin(void)
	\brief Devuelve el valor de minutos.
 	\details Entrega la variable m_minutos.
	\return m_minutos
*/
int32_t Reloj::GetMin( void ) const
{
	return m_minutos;
}
/**
	\fn void GetSeg(void)
	\brief Devuelve el valor de segundos.
 	\details Entrega la variable m_segundos.
	\return m_segundos
*/
int32_t Reloj::GetSeg( void ) const
{
	return m_segundos;
}
/**
	\fn void Reset(void)
	\brief Resetea el reloj.
 	\details Coloca todas las variables en 0.
*/
void Reloj::Reset ( void )
{
	m_cont = 0;
	m_hora = 0;
	m_minutos = 0;
	m_segundos = 0;
}
/**
	\fn void SetTime(void)
	\brief Setea el reloj.
 	\details Configura el valor actual de horas, minutos y segundos.
*/
void Reloj::SetTime ( const int32_t _hour , const int32_t _min , const int32_t _seg )
{
	m_hora = _hour;
	if ( _min > 0 )
		m_minutos = _min;
	if ( _seg > 0 )
		m_segundos = _seg;
	Actualizar();
}
/**
	\fn void Actualizar(void)
	\brief Controla las variables del reloj.
 	\details Controla el overflow lógico de las horas, minutos y segundos.
*/
void Reloj::Actualizar( void )
{
	if( m_segundos == 60 )
	{
		m_segundos = 0;
		m_minutos++;
	}
	if ( m_minutos == 60 )
	{
		m_minutos = 0;
		m_hora++;
	}
	m_hora %= INT32_MAX;	//En caso de superar el límite
}
/**
	\fn void SWhandler(void)
	\brief Actualiza el reloj.
 	\details Cada 1000 ticks pasa un segundo. Lo suma a la cuenta.
*/
void Reloj::SWhandler ( void )
{
	m_cont++;
	if ( m_cont == 1000 )
	{	// SUPONGO QUE SYSTICK A 1ms
		m_cont = 0;
		m_segundos++;
		Actualizar();
	}
}

Reloj::~Reloj() {}

