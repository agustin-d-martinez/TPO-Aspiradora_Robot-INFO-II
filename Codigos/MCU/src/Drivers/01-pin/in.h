/*******************************************************************************************************************************//**
 *
 * @file		in.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		18 oct. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef CLASES_2_GPIO_IN_H_
#define CLASES_2_GPIO_IN_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "tipos.h"

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
// extern tipo nombreVariable;
/***********************************************************************************************************************************
 *** IMPLANTACION DE UNA CLASE
 **********************************************************************************************************************************/

class in
{
	public:
		in() {};
		virtual uint8_t SetDirIn ( void )  = 0;
		virtual uint8_t GetPin ( void ) const = 0;
		virtual uint8_t SetPinResistor ( void ) = 0;
		virtual ~in() {};
};

#endif /* CLASES_2_GPIO_IN_H_ */
