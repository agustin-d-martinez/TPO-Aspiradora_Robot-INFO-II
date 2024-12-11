/*
 * drSystick.h
 *
 *  Created on: 20 abr. 2022
 *      Author: Marcelo
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <LPC845.h>
#include <list>
#include "swhandler.h"

using namespace std;

extern list <swhandler*> g_Handler;

uint32_t Inicializar_SysTick( uint32_t ticks );

#if defined (__cplusplus)
	extern "C" {
	void SysTick_Handler(void);
	}
#endif

#endif /* SYSTICK_H_ */
