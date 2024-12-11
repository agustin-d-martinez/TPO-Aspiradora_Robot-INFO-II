/*******************************************************************************************************************************//**
 *
 * @file		timers.h
 * @brief		Clase para creacion de temporizadores
 * @date		4 may. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/
#ifndef TIMER_H
#define TIMER_H

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "swhandler.h"
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
typedef void (*Timer_Handler)(void);

/***********************************************************************************************************************************
 *** IMPLANTACION DE LA CLASE
 **********************************************************************************************************************************/
class timer : public swhandler
{
	protected:
		volatile uint32_t 	m_TmrRun;
		volatile bool  		m_TmrEvent;
		void   		(* m_TmrHandler ) (void);
		volatile bool  		m_TmrStandBy ;
		volatile uint8_t  	m_TmrBase ;
	private:
		enum 		ticks_t 			{ DECIMAS = 100 , SEGUNDOS = 10 , MINUTOS  = 60 };
	public:
		enum 		bases_t 			{ DEC , SEG , MIN , HOR };
		enum 		erroresTimers_t 	{ errorTimer , OKtimers };
		enum 		standby_t 			{ RUN , PAUSE };

		timer( ) ;
		timer(const Timer_Handler handler , const uint8_t base );
		void 		TimerStart( uint32_t time, const Timer_Handler handler , const uint8_t base  );
		void 		SetTimer(  uint32_t time );
		uint32_t 	GetTimer( void ) const;
		void 		StandByTimer( const uint8_t accion );
		void		SetTimerBase( const uint8_t base );
		void 		TimerStop( void );
		uint32_t	GetTmrRun( )  { return m_TmrRun; }
		void  		SetTmrEvent( ) { m_TmrEvent = 1; }
		void  		ClrTmrEvent( ) { m_TmrEvent = 0; }
		bool  		GetTmrEvent( ) { return m_TmrEvent ; }
		bool  		GetmrStandBy( ) { return m_TmrStandBy ;}
		void  		SetmrStandBy( uint8_t accion) { m_TmrStandBy = accion ;}
		void		SetTmrHandler( ) { m_TmrHandler( ); }
		void 		TimerStart( uint32_t time );

		timer& 		operator=( uint32_t t );
		bool 		operator!( );
		explicit 	operator bool () ;
		bool 		operator==( uint32_t t );

		// por el hecho de haber convertido el operador bool como explicit
		// me obligo a realizar las funciones amigas del operador==
		// con sus dos prototipos, porque dejo de aceptar
		// la promocion automatica de tipos
		friend bool 	operator==( uint32_t t , timer &T );
		// Implementacion de funcion virtual pura heredada
		void 			SWhandler( void );
		virtual 		~timer();
		int8_t TmrEvent ( void );

};

#endif /* TIMER_H */
