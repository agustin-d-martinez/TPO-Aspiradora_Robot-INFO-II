#include "systick.h"
#include "swhandler.h"

using namespace std;

list <swhandler*> g_Handler;

#define MAX_TICKS 	0xffffff

#include "systick.h"
#include "inicializar.h"

void SysTick_Handler(void)
{
	for (swhandler* q : g_Handler )
		q->SWhandler();
}


uint32_t Inicializar_SysTick( uint32_t ticks )
{
	if (ticks > MAX_TICKS)
		return 1 ;          	//* Reload value impossible

	SysTick->RELOAD = ticks - 1;  //* set reload register

	SysTick->CURR = 0;           //* Load the SysTick Counter Value

	SysTick->CTRL = 7;

	return 0;
}
