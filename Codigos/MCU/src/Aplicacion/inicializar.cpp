/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "inicializar.h"

lcd 	* pantalla;

HC_SR04 * ultrasonic;
Pwm		* prueba;
pwmIn 	* detector;

inputs 	* s_der;
inputs 	* s_izq;
vector<inputs*> asp_in;

L298N 	* motor;
gpio 	* motor_izq_1;
gpio 	* motor_izq_2;
gpio 	* motor_der_1;
gpio 	* motor_der_2;

outputs * g_aspiradora;
vector<outputs *> asp_out;

//!<	TECLADO
vector <gpio *> scn;
vector <gpio *> ret;
teclado *Teclado;

Aspiradora * Proyecto;

//!<	COMUNICACION
vector<uint32_t> msg;
uart * uart0;
Comunicacion * maquina_com;

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
void InicializarFirmware ( void )
{
	Inicializar_PLL( );

	SYSCON->SYSAHBCLKCTRL0 |= (1 << 7);								// 7 = SWM
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 6) | (1 << 20) | (1 << 18);		// 6 = GPIO0	20 = GPIO1	18 = IOCON
	Inicializar_SysTick( FREQ_PRINCIPAL / FREQ_SYSTICK );
}

void inicializarApp ( void )
{
	InicializarFirmware();	// Inicializo Firmware

	msg.push_back(0);
	msg.push_back(0);
	msg.push_back(0);
	msg.push_back(0);
	msg.push_back(0);
	msg.push_back(0);

	//	CREACION DEL LCD
	vector<gpio*> patas_pantalla;
	patas_pantalla.push_back( new gpio( gpio::port0 , 13 , gpio::opencolector , gpio::high , gpio::output ));	//D7
	patas_pantalla.push_back( new gpio( gpio::port0 , 11 , gpio::opencolector , gpio::high , gpio::output ));	//D6
	patas_pantalla.push_back( new gpio( gpio::port0 , 10 , gpio::opencolector , gpio::high , gpio::output ));	//D5
	patas_pantalla.push_back( new gpio( gpio::port0 ,  9 , gpio::opencolector , gpio::high , gpio::output ));	//D4
	patas_pantalla.push_back( new gpio( gpio::port0 , 15 , gpio::opencolector , gpio::high , gpio::output ));	//RS
	patas_pantalla.push_back( new gpio( gpio::port0 , 14 , gpio::opencolector , gpio::high , gpio::output ));	//E
	pantalla = new lcd(patas_pantalla);
	pantalla->Inicializar( 2 , 16 );

	//	MOTOR
	motor_der_1 = new gpio ( gpio::port0 , 1 , gpio::pushpull , gpio::high , gpio::output );
	motor_der_2 = new gpio ( gpio::port1 , 2 , gpio::pushpull , gpio::high , gpio::output );
	motor_izq_1 = new gpio ( gpio::port1 , 1 , gpio::pushpull , gpio::high , gpio::output );
	motor_izq_2 = new gpio ( gpio::port1 , 0 , gpio::pushpull , gpio::high , gpio::output );
	motor = new L298N( motor_der_1 , motor_der_2 , motor_izq_1 , motor_izq_2);
	motor->Inicializar();

	//	Motor Aspirador
	g_aspiradora = new outputs ( gpio::port0 , 26 , gpio::pushpull , gpio::high,0);
	g_aspiradora->SetUp();
	asp_out.push_back(g_aspiradora);

	//	Sensores INFRARROJOS
	s_der = new inputs ( gpio::port0 , 20 , gpio::pullup , gpio::low );
	s_izq = new inputs ( gpio::port0 , 22 , gpio::pullup , gpio::low );
	s_der->Inicializar( );
	s_izq->Inicializar( );

	asp_in.push_back(s_der);
	asp_in.push_back(s_izq);

	//	Sensor Ultrasonico
	MRT_Reset();
	MRT_Inicializar( type_MRT::CHANNEL_0 , type_MRT::COUNTER );
	detector = new pwmIn( gpio::port0 , 23 , gpio::pullup , gpio::low , type_MRT::CHANNEL_0 ); //echo
	prueba = new Pwm( gpio::port0, 26 , Pwm::high, Pwm::CHANNEL_1 );  //trigger

	ultrasonic = new HC_SR04(detector, prueba);
	ultrasonic->Inicializar();

	// Teclado
	scn.push_back(new gpio ( gpio::port0 ,  27 , gpio::pushpull ,  gpio::high , gpio::output ));
	//scn.push_back(new gpio ( gpio::port0 ,  28 , gpio::pushpull ,  gpio::high , gpio::output ));

	ret.push_back(new gpio ( gpio::port0 ,  30 , gpio::pullup ,  gpio::low , gpio::input ));
	ret.push_back(new gpio ( gpio::port0 ,  31 , gpio::pullup ,  gpio::low , gpio::input ));
	ret.push_back(new gpio ( gpio::port0 ,   8 , gpio::pullup ,  gpio::low , gpio::input ));

	Teclado = new teclado ( scn , ret );
	Teclado->Inicializar();


	Proyecto = new Aspiradora(asp_in, asp_out, ultrasonic, Teclado, pantalla, motor , msg);


	uart0 = new uart(0, 16, 0, 17, USART0 , 9600 , uart::ocho_bits , uart::NoParidad , 64 , 64 );
	maquina_com = new Comunicacion(uart0, msg);

	SYSCON->SYSAHBCLKCTRL0 &= ~(1 << 7);
}
