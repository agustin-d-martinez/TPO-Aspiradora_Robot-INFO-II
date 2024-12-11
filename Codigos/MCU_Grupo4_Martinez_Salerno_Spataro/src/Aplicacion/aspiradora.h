/*******************************************************************************************************************************//**
 *
 * @file		sspiradora.h
 * @brief		Clase de una aspiradora.
 * @date		02 dec. 2022
 * @author		Grupo 4
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef MOTOR_H_
#define MOTOR_H_

#include "outputs.h"
#include "inputs.h"
#include "lcd.h"
#include "teclado.h"
#include "HCSR04.h"
#include "timer.h"
#include "L298N.h"

#include <vector>
using namespace std;

class Aspiradora
{
	private:
		enum estados { RESET ,BIENVENIDO , MENU , INICIO_LIMPIEZA , GIRA , FIN_GIRO , CONFIG_TIMER , ACERCA_DE ,
			MOV_ARRIBA , MOV_ABAJO , MOV_DERECHA , MOV_IZQUIERDA };
		enum estados_pantalla { PANTALLA_CONFIG_TIMER = 1 , PANTALLA_LIMPIEZA_RAPIDA , PANTALLA_ACERCA_DE };

		void (Aspiradora::*m_maquina[12]) (void);

	private:
			const vector <inputs *> 	&m_in;
			const vector <outputs *> 	&m_out;
			HC_SR04*  					&m_ultrasonico ;
			teclado*  					&m_teclado;
			lcd*  						&m_pantalla;
			L298N*	 					&m_motor;
			vector <uint32_t > 			&m_msg;

			timer *	m_timer_giro;
			timer *	m_timer_bienvenido;
			timer *	m_timer_limpiar;

			uint8_t m_estado;
			uint8_t m_estado_pantalla;

			uint8_t m_cant_puntos;
			uint8_t m_sentido_giro;
			bool 	m_esquina_final;
			uint8_t m_tecla_presionada;
			int32_t m_tiempo_limpieza;

	public :
		Aspiradora( vector <inputs *> &in , vector <outputs *> &out ,
				HC_SR04* &ultrasonic ,
				teclado* &_teclado ,
				lcd*& pantalla ,
				L298N *& motor ,
				vector <uint32_t > &msg);
		void MaquinaDeEstados ( void );
		~Aspiradora();
	private:	//Máquina de estados
		void Reset( void );
		void Bienvenido( void );
		void Menu( void );
		void InicioLimpieza( void );
		void Giro( void );
		void FinGiro( void );
		void ConfigTimer( void );
		void AcercaDe( void );

		void MovArriba( void );
		void MovAbajo( void );
		void MovDER( void );
		void MovIZQ( void );

		bool LeerMensajes( void );	//Como los mensajes ocurren en todos los estados, es más sencillo tener una funcion

	private:	//Funciones auxiliares
		void detener_timer( void );
		void ImprimirTiempoRestante(void);

};

#endif /* MOTOR_H_ */
