/*******************************************************************************************************************************//**
 *
 * @file		teclado.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		24 jul. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef SRC_TECLADO_H_
#define SRC_TECLADO_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "gpio.h"
#include "swhandler.h"
#include <vector>

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define NO_KEY		0xff

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

class teclado : public swhandler
{
	private:
		const vector <gpio *> &m_scn;
		const vector <gpio *> &m_ret;

		uint8_t 		m_TeclaEstadoInicial ;
		uint32_t 		m_TeclaCantidadDeRebotes ;
		uint8_t 		m_BufferTeclado ;
		const uint8_t 	m_MaxRebotes;
		const uint32_t 	m_RebotesHold ;

	public:
		//teclado();
		teclado ( vector <gpio *> &s , vector <gpio *> &r);
		void SWhandler ( void );
		void Inicializar ( void );
		uint8_t	Get( void );
		virtual ~teclado();

	private:
		uint8_t TecladoHW ( void );
		void TecladoSW ( uint8_t TeclaEstadoActual );
};

#endif /* SRC_TECLADO_H_ */

