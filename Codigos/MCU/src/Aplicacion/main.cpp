/*
===============================================================================
 Name        : main.c
 Author      : Grupo 4
 Version     : 4.0
 Description : main aspiradora
===============================================================================
 */

#include "inicializar.h"

int  main(void)
{
	inicializarApp(  );
	while ( 1 )
	{
		maquina_com->MaquinaDeEstados();

		Proyecto->MaquinaDeEstados();
	}
}

