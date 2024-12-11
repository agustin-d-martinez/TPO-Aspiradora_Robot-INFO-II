/*******************************************************************************************************************************//**
 *
 * @file		Pwm.h
 * @brief		Generador de PWM sin interrupción
 * @date		7 oct. 2022
 * @author		Técnico. Martinez Agustin
 *
 **********************************************************************************************************************************/

#ifndef PWM_PWM_H_
#define PWM_PWM_H_
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "gpio.h"
#include "SCtimer.h"
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
 *** IMPLANTACION DE LA CLASE
 **********************************************************************************************************************************/
class Pwm : protected SCtimer
{
public:
	typedef enum { SEG = 0, MILI_SEG , MICRO_SEG } pwm_time_unit_t;
	typedef enum { CHANNEL_1 = 1 , CHANNEL_2 , CHANNEL_3 , CHANNEL_4 , CHANNEL_5 , CHANNEL_6 } pwm_channel_t;
	enum activity_t		{ low ,	high };
protected:
	const 	uint8_t m_port ;
	const 	uint8_t m_bit ;
	const 	uint8_t m_activity;
	uint32_t m_ton;		/*	en micro segundos	*/
	uint32_t m_toff;	/*	en micro segundos	*/
	const uint8_t  m_pwm_channel;

public:
	Pwm( uint8_t puerto , uint8_t bit , uint8_t actividad , pwm_channel_t number );
	void Inicializar( uint32_t ton , uint32_t toff , pwm_time_unit_t t = MICRO_SEG );
	void SetTon( uint32_t time , pwm_time_unit_t t = MICRO_SEG );
	void SetPeriod( uint32_t time , pwm_time_unit_t t = MICRO_SEG );
	void On();
	void Off();
	virtual ~Pwm();
};

#endif /* PWM_PWM_H_ */
