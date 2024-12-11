/*
 * MTRtick.cpp
 *
 *  Created on: 2 sep. 2022
 *      Author: mari-ser
 */

#include "MRT_config.h"

void MRT_Reset( void )
{
	SYSCON->PRESETCTRL0 |= (1 << 10);		/*Reset multi-rate timer*/
}

void MRT_Inicializar (  MRT_timer_channels timer , MRT_MODES mode  )
{
	NVIC->ISER[0] |= (1 << 10);

	SYSCON->SYSAHBCLKCTRL0 |= (1 << 10);	/*Enables clock for multi-rate timer */

	( MRT + timer )->LOAD = 0;		/*Que reinicie el valor AL TERMINAR*/

	if ( mode != COUNTER )	/*COUNTER ES UN MODO INVENTADO, NO PERTENECE A NINGUNA CONFIGURACION*/
	{
		( MRT + timer )->INTEN = 1;		/*habilito interrupcion*/
		( MRT + timer )->IVALUE = 0;	/*Reseteo el temporizador*/
		( MRT + timer )->MODE = mode;
	}
	else
	{
		( MRT + timer )->INTEN = 0;		/*deshabilito interrupcion*/
		( MRT + timer )->IVALUE = 0x7FFFFFFF;
		( MRT + timer )->MODE = REPEAT;		/*Modo ONE SHOT*/
	}
}
