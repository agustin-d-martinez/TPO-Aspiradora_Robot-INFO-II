/*******************************************************************************************************************************//**
 *
 * @file		display.h
 * @brief		Clase base para objetos del tipo pantallas/displays
 * @date		22 jun. 2022
 * @author		Técnico. Martinez Agustin
 *
 **********************************************************************************************************************************/
/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef DISPLAY_H_
#define DISPLAY_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "tipos.h"

/***********************************************************************************************************************************
 *** IMPLANTACION DE LA CLASE
 **********************************************************************************************************************************/
class display {
	public:
		display(){};
		virtual void Write ( const int8_t *s ) = 0;
		virtual void Clear ( void ) = 0;
		virtual ~display(){};
};

#endif /* DISPLAY_H_ */
