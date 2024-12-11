/*******************************************************************************************************************************//**
 *
 * @file		tipos.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		22 jun. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef TIPOS_H_
#define TIPOS_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
#define  	__I    					volatile const  	/*Defines 'read only' permission */
#define  	__O    					volatile             /*Defines 'write only' permission */
#define  	__IO   					volatile             /*Defines 'read / write' permission */

typedef		unsigned char 			uint8_t;
typedef		char					int8_t;
typedef		short unsigned int 		uint16_t;
typedef		short signed int		int16_t;
typedef		unsigned int 			uint32_t;
typedef		signed int				int32_t;

#define		INT32_MAX				(2147483647)
#define		INT32_MIN				(-2147483648)
#define		UINT32_MAX				(4294967295)

#define		INT8_MAX				(127)
#define		INT8_MIN				(-128)
#define		UINT8_MAX				(255)

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/

#endif /* TIPOS_H_ */
