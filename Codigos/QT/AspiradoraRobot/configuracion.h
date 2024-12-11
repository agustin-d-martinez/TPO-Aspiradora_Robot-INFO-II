#ifndef CONFIGURACION_H
#define CONFIGURACION_H

//Defines base_datos
#define PATH_DEFAULT                    "../BaseDatos"
#define NOMBRE_ARCHIVO_BASEDATOS        "/baseDatos.sqlite"
#define TYPE_DB                         "QSQLITE"

#define NUMERO          0
#define FECHA           1
#define TIEMPO_INI      2
#define TIEMPO_FIN      3

//Defines TABLA base_datos
#define COLUMNAS        4
#define POS_NUMERO      0
#define POS_FECHA       1
#define POS_TIEMPO_INI  2
#define POS_TIEMPO_FIN  3

//Defines servidor wifi
#define PUERTO  83

//Defines protocolo comunicacion
#define BYTE_INICIO      '<'
#define BYTE_FINAL       '>'

//Defines Configuración
#define ARCHIVO_CONFIGURACION           ".config.txt"
#define COLOR_DESHABILITADO             "background-color: rgb(255,105,97);"
#define COLOR_VISION                    "background-color: rgb(239,239,239);"
#define COLOR_PALETA                    "background-color: rgb(255,234,197);"


//---PROTOCOLO------------------------------------------------------------------
// CONTROL  ----> <CU>    C-CONTROL, U-ARRIBA, D-ABAJO, R-DERECHA, L-IZQ, S-STOP
// TIEMPO   ----> <L0245>   L-LIMPIAR, TIEMPO(MINS)
// TIEMPO PROG  ----> <P0245/0160>  P-PROGRAMADO, TIEMPO(MINS), / , TIMEPO DE DESFASE (MINS)
//------------------------------------------------------------------------------

#endif // CONFIGURACION_H
