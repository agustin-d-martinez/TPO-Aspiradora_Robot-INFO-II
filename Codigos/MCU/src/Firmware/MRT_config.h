/*
 * MTRtick.h
 *
 *  Created on: 2 sep. 2022
 *      Author: mari-ser
 */

#ifndef MRTTICK_H_
#define MRTTICK_H_

#include "MRThandler.h"
#include <LPC845.h>
#include "tipos.h"

using namespace type_MRT;

void MRT_Inicializar ( MRT_timer_channels timer , MRT_MODES mode );
void MRT_Reset( void );

#endif /* MRTTICK_H_ */
