/*******************************************************************************************************************************//**
 *
 * @file		lcd.h
 * @brief		Clase para un LCD con comunicación de 4 patas, solo escritura
 * @date		22 jun. 2022
 * @author		Técnico. Martinez Agustin
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef LCD_H_
#define LCD_H_
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <Drivers/05-swhandler/swhandler.h>
#include <Drivers/09-display_LCD/display.h>
#include "gpio.h"
#include <vector>
#include <math.h>
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
enum { d7 = 0 ,  d6 , d5 , d4 , rs , enable };	/*Posiciones del buffer*/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLANTACION DE LA CLASE
 **********************************************************************************************************************************/
class lcd : public display, swhandler {
	private:
		#define CLEAR_DISPLAY			0b00000001
		#define RETURN_HOME				0b00000010
		#define ENTRY_MODE_SET			0b00000100	/*1 I/D S*/
		#define DISPLAY_CONTROL			0b00001000	/*1 D 	C 	B*/
		#define CURSOR_DISPLAY_SHIFT	0b00010000	/*1 S/C R/L - 	-*/
		#define FUNCTION_SET			0b00100000	/*1 DL 	N 	F 	- 	-*/
		#define SET_CGRAM				0b01000000	/*1 ACG ACG ACG ACG ACG ACG*/
		#define SET_DDRAM				0b10000000	/*1	ADD	ADD	ADD	ADD	ADD	ADD	ADD*/

	private:
		const vector<gpio*> m_salidas;
		uint8_t m_estado;
		uint8_t *m_buffer;
		uint8_t m_filas;
		uint8_t m_columnas;
		uint8_t m_delay;
		uint8_t m_barrido;
		uint8_t m_pos;

		enum { s_eigth_bits = 0 , s_four_bits , s_config_display , s_config_cursor , s_clear , s_print , s_row };	/*Estados inicializacion*/

	public:
		lcd( vector<gpio*> &salidas );
		void Inicializar( const uint8_t filas , const uint8_t columnas );
		void Write ( const int8_t *s );
		void Write ( const int32_t n );
		lcd& operator= ( const int8_t *s );
		void WriteAt( const int8_t *a , const uint8_t fila , const uint8_t columna );
		void WriteAt ( const int32_t n , const uint8_t fila , const uint8_t columna);
		void Clear( void );
		virtual ~lcd() {} ;

	protected:
		void SWhandler ( void );

	private:
		void WriteInstruction( const uint8_t data , const uint8_t mode );
};

#endif /* LCD_H_ */
