/*******************************************************************************************************************************//**
 *
 * @file		aspiradora.cpp
 * @brief		Clase de una aspiradora.
 * @date		02 dec. 2022
 * @author		Grupo 4
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "aspiradora.h"
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
//	Timers:
#define FIN_TIMER_LIMPIEZA	(m_timer_limpiar->GetTmrEvent())
#define FIN_TIMER_PUNTO		(m_timer_bienvenido->GetTmrEvent())
#define FIN_TIMER_GIRO		(m_timer_giro->GetTmrEvent())

#define TIEMPO_PUNTO			(10)
#define TIEMPO_LIMPIAR_MAX 		(255)
#define TIEMPO_MEDIA_VUELTA		(19)
#define TIEMPO_UN_CUARTO		(10)

//	Inputs:	SENSOR DERECHA , SENSOR IZQUIERDA
#define SENSOR_DER		(m_in[0]->get())
#define SENSOR_IZQ		(m_in[1]->get())
#define	NO_PARED		(0)
#define	PARED			(1)
#define DISTANCIA_AD	(15)
#define PARED_ADELANTE	(m_ultrasonico->GetDistancia() <= DISTANCIA_AD)

#define	PRES_IZQ		(m_tecla_presionada == 2)
#define	PRES_DER		(m_tecla_presionada == 0)
#define	PRES_OK			(m_tecla_presionada == 1)

//	Outputs: Aspiradora
#define ASPIRADORA_ON	(m_out[0]->On())
#define ASPIRADORA_OFF	(m_out[0]->Off())

//	RE-DEFINE para simplificar
#define	IZQ			Puente_H::IZQUIERDA
#define DER			Puente_H::DERECHA

//	Comunicacion
enum{ 	POS_MENSAJE_ARRIBA = 0,
		POS_MENSAJE_ABAJO ,
		POS_MENSAJE_IZQ ,
		POS_MENSAJE_DER ,
		POS_TIEMPO_ASPIRADO ,
		POS_TIEMPO_MANUAL
};
/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
Aspiradora::Aspiradora( vector <inputs *> &in , vector <outputs *> &out ,
		HC_SR04* &ultrasonic ,
		teclado* &_teclado ,
		lcd*& pantalla ,
		L298N *& motor ,
		vector <uint32_t > &msg ) :
m_in(in) , m_out(out) , m_ultrasonico(ultrasonic) , m_teclado(_teclado) , m_pantalla(pantalla) , m_motor(motor) , m_msg(msg)
{
	m_maquina[  0 ] = &Aspiradora::Reset;
	m_maquina[  1 ] = &Aspiradora::Bienvenido;
	m_maquina[  2 ] = &Aspiradora::Menu;
	m_maquina[  3 ] = &Aspiradora::InicioLimpieza;
	m_maquina[  4 ] = &Aspiradora::Giro;
	m_maquina[  5 ] = &Aspiradora::FinGiro;
	m_maquina[  6 ] = &Aspiradora::ConfigTimer;
	m_maquina[  7 ] = &Aspiradora::AcercaDe;
	m_maquina[  8 ] = &Aspiradora::MovArriba;
	m_maquina[  9 ] = &Aspiradora::MovAbajo;
	m_maquina[ 10 ] = &Aspiradora::MovDER;
	m_maquina[ 11 ] = &Aspiradora::MovIZQ;

	m_estado = RESET;
	m_estado_pantalla = PANTALLA_LIMPIEZA_RAPIDA;

	//Inicializacion variables
	m_sentido_giro = IZQ;
	m_esquina_final = false;
	m_tiempo_limpieza = 20;
	m_cant_puntos = 0;

	//Inicializacion timers
	m_timer_bienvenido = 	new timer ( nullptr , timer::DEC);
	m_timer_giro = 			new timer ( nullptr , timer::DEC);
	m_timer_limpiar = 		new timer ( nullptr , timer::MIN);
}

void Aspiradora::MaquinaDeEstados ( void )
{
	m_tecla_presionada = m_teclado->Get();	//Leo el teclado

	if ( m_estado > MOV_IZQUIERDA )
		m_estado = BIENVENIDO ;

	( this->*m_maquina[m_estado] )( );	//Ejecuto la máquina
}

Aspiradora::~Aspiradora() { }

bool Aspiradora::LeerMensajes( void )
{
	if ( m_msg[POS_MENSAJE_ARRIBA] == 1 )
	{
		ASPIRADORA_OFF;
		detener_timer();
		m_pantalla->WriteAt("  Avanzando", 0, 0);
		m_ultrasonico->Off();
		m_estado = MOV_ARRIBA;
		return true;
	}
	if ( m_msg[POS_MENSAJE_ABAJO] == 1 )
	{
		ASPIRADORA_OFF;
		detener_timer();
		m_pantalla->WriteAt(" Retrocediendo", 0, 0);
		m_ultrasonico->Off();
		m_estado = MOV_ABAJO;
		return true;
	}
	if ( m_msg[POS_MENSAJE_DER] == 1 )
	{
		ASPIRADORA_OFF;
		detener_timer();
		m_pantalla->WriteAt("  Derecha", 0, 0);
		m_ultrasonico->Off();
		m_estado = MOV_DERECHA;
		return true;
	}
	if ( m_msg[POS_MENSAJE_IZQ] == 1 )
	{
		ASPIRADORA_OFF;
		detener_timer();
		m_pantalla->WriteAt("  Izquierda", 0, 0);
		m_ultrasonico->Off();
		m_estado = MOV_IZQUIERDA;
		return true;
	}
	if ( m_msg[POS_TIEMPO_ASPIRADO] != 0 )
	{
		m_tiempo_limpieza = m_msg[POS_TIEMPO_ASPIRADO];
		m_msg[POS_TIEMPO_ASPIRADO] = 0;
		detener_timer();
		ASPIRADORA_ON;
		m_ultrasonico->On();
		m_timer_limpiar->TimerStart(m_tiempo_limpieza);
		m_estado = INICIO_LIMPIEZA;
		return true;
	}
	return false;
}
void Aspiradora::MovArriba( void )
{
	m_motor->Avanzar();
	if ( LeerMensajes() && m_msg[POS_MENSAJE_ARRIBA] == 0)
	{
		m_pantalla->Clear();
		return;
	}
	if ( m_msg[POS_MENSAJE_ARRIBA] == 0 )
	{
		m_pantalla->Clear();
		m_motor->Frenar();
		m_estado = MENU;
	}
}
void Aspiradora::MovAbajo( void )
{
	m_motor->Retroceder();
	if ( LeerMensajes() && m_msg[POS_MENSAJE_ABAJO] == 0 )
	{
		m_pantalla->Clear();
		return;
	}
	if ( m_msg[POS_MENSAJE_ABAJO] == 0 )
	{
		m_pantalla->Clear();
		m_motor->Frenar();
		m_estado = MENU;
	}
}
void Aspiradora::MovDER( void )
{
	m_motor->GirarDer();
	if ( LeerMensajes() && m_msg[POS_MENSAJE_DER] == 0 )
	{
		m_pantalla->Clear();
		return;
	}
	if ( m_msg[POS_MENSAJE_DER] == 0 )
	{
		m_pantalla->Clear();
		m_motor->Frenar();
		m_estado = MENU;
	}
}
void Aspiradora::MovIZQ( void )
{
	m_motor->GirarIzq();
	if ( LeerMensajes() && m_msg[POS_MENSAJE_IZQ] == 0 )
	{
		m_pantalla->Clear();
		return;
	}
	if ( m_msg[POS_MENSAJE_IZQ] == 0 )
	{
		m_pantalla->Clear();
		m_motor->Frenar();
		m_estado = MENU;
	}
}
void Aspiradora::Reset ( void )
{
	m_motor->Frenar();
	detener_timer();

	m_pantalla->WriteAt( "ASPIRADORA ROBOT" , 0 , 0 );
	m_pantalla->WriteAt( "INICIANDO" , 1 , 3 );
	m_timer_bienvenido->TimerStart( TIEMPO_PUNTO );

	m_estado = BIENVENIDO;
}

void Aspiradora::Bienvenido( void )
{
	if( FIN_TIMER_PUNTO )
	{
		m_pantalla->WriteAt( "." , 1 , ( m_cant_puntos + 12 ));
		m_cant_puntos++;
		if( m_cant_puntos > 3 )
		{
			m_pantalla->Clear( );
			m_timer_bienvenido->TimerStop();
			m_ultrasonico->On();
			m_estado = MENU;
			return;
		}

		m_timer_bienvenido->TimerStart( TIEMPO_PUNTO );
	}
}
void Aspiradora::Menu( void )
{
	ASPIRADORA_OFF;

	if ( LeerMensajes() )
	{
		m_pantalla->Clear();
		return;
	}
	//-------------PANTALLA----------------------------
	if ( m_estado_pantalla == PANTALLA_CONFIG_TIMER )
		m_pantalla->WriteAt( "CONFIG. TIEMPO" , 0 , 1 );
	if ( m_estado_pantalla == PANTALLA_LIMPIEZA_RAPIDA )
		m_pantalla->WriteAt( "INCIAR LIMPIEZA" , 0 , 1 );
	if ( m_estado_pantalla == PANTALLA_ACERCA_DE )
		m_pantalla->WriteAt( "ACERCA DE" , 0 , 3 );
	//-------------------------------------------------

	m_pantalla->WriteAt( "<-     OK     ->" , 1 , 0 );

	if ( PRES_DER )
	{
		m_pantalla->Clear( );
		m_estado_pantalla++;
	}

	if ( PRES_IZQ )
	{
		m_pantalla->Clear( );
		m_estado_pantalla--;
	}

	if( m_estado_pantalla > PANTALLA_ACERCA_DE )
		m_estado_pantalla = PANTALLA_CONFIG_TIMER;

	if( m_estado_pantalla < PANTALLA_CONFIG_TIMER )
		m_estado_pantalla = PANTALLA_ACERCA_DE;


	if ( PRES_OK )
	{
		m_pantalla->Clear();

		switch (m_estado_pantalla) {
		default:
			case PANTALLA_CONFIG_TIMER:
				m_estado = CONFIG_TIMER;
				break;
			case PANTALLA_LIMPIEZA_RAPIDA:
				ASPIRADORA_ON;
				m_sentido_giro = IZQ;
				m_timer_limpiar->TimerStart( m_tiempo_limpieza );
				m_msg[POS_TIEMPO_MANUAL] = m_tiempo_limpieza;
				m_ultrasonico->On();
				m_motor->Avanzar();
				m_estado = INICIO_LIMPIEZA;
				break;
			case PANTALLA_ACERCA_DE:
				m_estado = ACERCA_DE;
				break;
		}
	}
}
void Aspiradora::InicioLimpieza( void )
{
	if (LeerMensajes())
	{
		m_pantalla->Clear();
		return;
	}

	ImprimirTiempoRestante();

	if ( PRES_DER || m_timer_limpiar->GetTmrEvent() )
	{	// Cancelado/terminado
		m_pantalla->Clear( );
		detener_timer();
		m_motor->Frenar();
		m_ultrasonico->Off();
		m_estado = MENU;
		return;
	}

	if( PARED_ADELANTE )
	{ //PARED ADELANTE
		m_estado = GIRA;
		if( (SENSOR_IZQ == NO_PARED && m_sentido_giro == IZQ ) || ( SENSOR_DER == NO_PARED && m_sentido_giro == DER ))
		{	//Esquina que no molesta
			m_timer_giro->TimerStart(TIEMPO_MEDIA_VUELTA);
			return;
		}

		if( SENSOR_IZQ == PARED && m_sentido_giro == IZQ )
		{ // Cambio de modo por IZQ
			m_sentido_giro = DER;
			m_timer_giro->TimerStart(TIEMPO_UN_CUARTO);
			m_esquina_final = true;
			return;
		}
		if( SENSOR_DER == PARED && m_sentido_giro == DER)
		{// Cambio de modo por DER
			m_sentido_giro = IZQ;
			m_timer_giro->TimerStart(TIEMPO_UN_CUARTO);
			m_esquina_final = true;
		}
	}
}
void Aspiradora::Giro( void )
{
	if (LeerMensajes())
	{
		m_pantalla->Clear();
		return;
	}

	ImprimirTiempoRestante();

	m_motor->Girar( m_sentido_giro );

	if ( PRES_DER || m_timer_limpiar->GetTmrEvent() )
	{	// Cancelado/terminado
		m_pantalla->Clear( );
		detener_timer();
		m_motor->Frenar();
		m_ultrasonico->Off();
		m_estado = MENU;
		return;
	}

	if( FIN_TIMER_GIRO )
	{
		m_timer_giro->TimerStop();
		m_estado = FIN_GIRO;
	}
}
void Aspiradora::FinGiro( void )
{
	if (LeerMensajes())
	{
		m_pantalla->Clear();
		return;
	}

	ImprimirTiempoRestante();

	if( !m_esquina_final )
	{	//CAMBIO EL PROX SENTIDO DE GIRO
		if ( m_sentido_giro == IZQ )
			m_sentido_giro = DER;
		else if ( m_sentido_giro == DER )
			m_sentido_giro = IZQ;
	}
	m_esquina_final = false;
	m_motor->Avanzar();
	m_estado = INICIO_LIMPIEZA;
}
void Aspiradora::ConfigTimer( void )
{
	ASPIRADORA_OFF;

	if (LeerMensajes())
	{
		m_pantalla->Clear();
		return;
	}
	//-------------PANTALLA----------------------------
	m_pantalla->WriteAt( "TIEMPO:" , 0 , 0 );

	if ( m_tiempo_limpieza >= 10 )
		m_pantalla->WriteAt( m_tiempo_limpieza , 0 , 7 );
	else
	{
		m_pantalla->WriteAt( "0" , 0 , 7 );
		m_pantalla->WriteAt( m_tiempo_limpieza , 0 , 8 );
	}

	m_pantalla->Write( " MIN" );
	m_pantalla->WriteAt( "(-)    OK    (+)", 1 , 0 );
	//--------------------------------------------------

	if ( PRES_DER )
		m_tiempo_limpieza++;
	if ( PRES_IZQ )
		m_tiempo_limpieza--;

	if( m_tiempo_limpieza >= TIEMPO_LIMPIAR_MAX )
		m_tiempo_limpieza = 0;

	if( m_tiempo_limpieza <= 0 )
		m_tiempo_limpieza = TIEMPO_LIMPIAR_MAX;

	if ( PRES_OK )
	{
		m_pantalla->Clear();
		m_estado = MENU;
	}
}
void Aspiradora::AcercaDe( void )
{
	if (LeerMensajes())
	{
		m_pantalla->Clear();
		return;
	}
	//-------------PANTALLA----------------------------
	m_pantalla->WriteAt( "MARTINEZ SALERNO" , 0 , 0 );
	m_pantalla->WriteAt( "SPATARO     OK->" , 1 , 0 );
	//-------------------------------------------------

	if ( PRES_DER )
	{
		m_pantalla->Clear( );
		m_estado = MENU;
	}
}

void Aspiradora::detener_timer( void )
{
	m_timer_giro->TimerStop();
	m_timer_limpiar->TimerStop();
	m_timer_bienvenido->TimerStop();
}
void Aspiradora::ImprimirTiempoRestante(void)
{
	m_pantalla->WriteAt( "TIEMPO: " , 0 , 0 );
	m_pantalla->WriteAt( m_timer_limpiar->GetTimer() , 0 , 9 );
	m_pantalla->Write(" MIN ");
	m_pantalla->WriteAt(" PARAR->", 1 , 9 );
}



