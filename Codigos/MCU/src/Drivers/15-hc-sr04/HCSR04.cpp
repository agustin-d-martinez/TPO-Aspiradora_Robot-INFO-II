/*******************************************************************************************************************************//**
 *
 * @file		HCSR04.h
 * @brief		Clase del sensor ultrasónico HCSR04
 * @date		22 jun. 2022
 * @author		Técnico. Martinez Agustin
 *
 **********************************************************************************************************************************/

#include "HCSR04.h"

HC_SR04::HC_SR04( pwmIn*  rx , Pwm * tx ) : m_rx(rx) , m_tx(tx) , m_distancia(0) , m_stop(true)
{ }
/**
	\fn void Inicializar(void)
	\brief Inicializa todas las patas del ultrasónico.
 	\details Inicializa el PWM con el valor correspondiente y el contador de ancho ancho de pulso.
	\return void
*/
void HC_SR04::Inicializar(void)
{
	m_rx->Inicializar();
	m_tx->Inicializar( 10 , (PERIODO * 1000 - 10) , Pwm::MICRO_SEG );
}
/**
	\fn uint32_t GetDistancia(void)
	\brief Devuelve la distancia.
 	\details A menos que esté apagado, devuelve el valor de distancia obtenido. Para evitar overflow del Uint32, se verifica el valor censado.
	\return m_distancia
*/
uint32_t HC_SR04::GetDistancia(void)
{
	if ( m_stop == false )
	{
		m_distancia = m_rx->GetPulseOn();
		if ( m_distancia < (UINT32_MAX/164) )
			m_distancia = CALC_DISTANCIA(m_distancia);
		else
			m_distancia = DISTANCIA_MAX;
	}
	return m_distancia;
}
/**
	\fn bool operator==( const uint32_t a)
	\brief Operador ==.
 	\details Consulta si la distancia es igual o no a la entregada.
 	\param	Valor de distancia.
	\return bool
*/
bool HC_SR04::operator==( const uint32_t a)
{
	m_distancia = m_rx->GetPulseOn();
	if ( m_distancia < (UINT32_MAX/164) )
		m_distancia = CALC_DISTANCIA(m_distancia);
	else
		m_distancia = DISTANCIA_MAX;
	return (m_distancia == a) ? true : false;
}
/**
	\fn bool operator<=( const uint32_t a )
	\brief Verifica si la distancia es menor o igual que a.
 	\details Realiza el cálculo de distancia actual y luego lo compara con a.
 	\param	Distancia a comparar.
	\return bool
*/
bool HC_SR04::operator<=( const uint32_t a )
{
	m_distancia = m_rx->GetPulseOn();
	if ( m_distancia < (UINT32_MAX/164) )
		m_distancia = CALC_DISTANCIA(m_distancia);
	else
		m_distancia = DISTANCIA_MAX;
	return (m_distancia <= a) ? true : false;
}
/**
	\fn bool operator>=( const uint32_t a )
	\brief Verifica si la distancia es mayor o igual que a.
 	\details Realiza el cálculo de distancia actual y luego lo compara con a.
 	\param	Distancia a comparar.
	\return bool
*/
bool HC_SR04::operator>=( const uint32_t a )
{
	m_distancia = m_rx->GetPulseOn();
	if ( m_distancia < (UINT32_MAX/164) )
		m_distancia = CALC_DISTANCIA(m_distancia);
	else
		m_distancia = DISTANCIA_MAX;
	return (m_distancia >= a) ? true : false;
}
/**
	\fn bool operator<( const uint32_t a )
	\brief Verifica si la distancia es menor que a.
 	\details Realiza el cálculo de distancia actual y luego lo compara con a.
 	\param	Distancia a comparar.
	\return bool
*/
bool HC_SR04::operator<( const uint32_t a )
{
	m_distancia = m_rx->GetPulseOn();
	if ( m_distancia < (UINT32_MAX/164) )
		m_distancia = CALC_DISTANCIA(m_distancia);
	else
		m_distancia = DISTANCIA_MAX;
	return (m_distancia < a) ? true : false;
}
/**
	\fn bool operator>( const uint32_t a )
	\brief Verifica si la distancia es mayor que a.
 	\details Realiza el cálculo de distancia actual y luego lo compara con a.
 	\param	Distancia a comparar.
	\return bool
*/
bool HC_SR04::operator>( const uint32_t a )
{
	m_distancia = m_rx->GetPulseOn();
	if ( m_distancia < (UINT32_MAX/164) )
		m_distancia = CALC_DISTANCIA(m_distancia);
	else
		m_distancia = DISTANCIA_MAX;
	return (m_distancia > a) ? true : false;
}
/**
	\fn void Off(void)
	\brief Apago las patas del ultrasonico.
 	\details Llamo a las funciones de apagar y guardo en el buffer un valor imposible.
	\return void
*/
void HC_SR04::Off(void)
{
	m_rx->Off();
	m_tx->Off();
	m_stop = true;
	m_distancia = DISTANCIA_MAX + 100;
}
/**
	\fn void On(void)
	\brief Enciendo las patas del ultrasonico.
 	\details Llamo a las funciones de encender de tx y rx.
	\return void
*/
void HC_SR04::On(void)
{
	m_rx->On();
	m_tx->On();
	m_stop = false;
}
