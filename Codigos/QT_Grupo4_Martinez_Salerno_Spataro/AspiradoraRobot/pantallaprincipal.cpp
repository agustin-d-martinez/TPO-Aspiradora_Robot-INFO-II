#include "pantallaprincipal.h"
#include "ui_pantallaprincipal.h"

PantallaPrincipal::PantallaPrincipal(QWidget *parent): QMainWindow(parent), ui(new Ui::PantallaPrincipal)
{
    ui->setupUi(this);
    inicializar();
}

void PantallaPrincipal::inicializar()
{
    /*Seteo las variables del mainwindow*/
    bool configuracion_previa;
    configuracion_previa = LeerConfig();
    if ( m_path_basedatos.isNull() || !configuracion_previa || !QFileInfo::exists(m_path_basedatos) )
    {
        m_path_basedatos = PATH_DEFAULT;
        m_path_basedatos.append(NOMBRE_ARCHIVO_BASEDATOS);
    }

    m_mensaje_recibido = "";

    /*Cargo la imagen*/
    QString imagen_aspiradora = RUTA_IMAGEN;
    imagen_aspiradora += "aspiradora_desconectada.png";
    ui->ImagenAspiradora->setPixmap(QPixmap(imagen_aspiradora));

    /*Seteo la base de datos y el el puerto serie*/
    setUpBaseDatos();
    m_socket = new QTcpSocket(this);
    m_server = new QTcpServer(this);

    if(m_server->listen(QHostAddress::Any , PUERTO))
        SetConectedInterface(true);
    else
        SetConectedInterface(false);
    connect(m_server , SIGNAL(newConnection()) , this , SLOT(NuevaConexion()));

    return;
}

void PantallaPrincipal::NuevaConexion()
{   /*  Si alguien se conecta    */
    m_socket = m_server->nextPendingConnection();
    connect(m_socket , SIGNAL(readyRead()) , this , SLOT(LeerWiFi()));

    m_socket->write(m_mensaje_enviar.toUtf8());
    m_mensaje_enviar.clear();
}

bool PantallaPrincipal::LeerConfig()
{   /* Leo las variables de configuracion */
    bool exito = false;
    QFile config( ARCHIVO_CONFIGURACION , this );
    if ( config.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        exito = true;
        QTextStream mensaje(&config);
        m_path_basedatos = mensaje.readLine();
    }

    config.close();
    return exito;
}

bool PantallaPrincipal::GuardarConfig()
{   /* Guardo las variables de configuracion */
    bool exito = false;
    QFile config(ARCHIVO_CONFIGURACION,this);
    if (config.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        exito = true;
        QTextStream mensaje(&config);
        mensaje << m_path_basedatos << "\n";
    }
    config.close();
    return exito;
}

void PantallaPrincipal::on_BotonBaseDatos_clicked()    /*Abro "historial"*/
{
    PestaniaHistorial history(this);
    history.setModal(true);
    history.move(775, 400);
    history.exec();
}

void PantallaPrincipal::on_botonInicio_clicked()    /*Abro la "pestaña inicio"*/
{
    PantallaHora iniciar(this);
    iniciar.setVariables(&m_mensaje_enviar);
    iniciar.setModal(true);
    iniciar.move(775, 400);
    iniciar.exec();
    return;
}

void PantallaPrincipal::on_botonInfo_clicked()    /*Abro "Acerca de"*/
{
    PantallaAcercaDe info(this);
    info.move(775, 400);
    info.exec();
    return;
}

void PantallaPrincipal::on_botonConfig_clicked() /*Abro "configuracion"*/
{
    PestaniaConfig config(this);
    config.setVariables(  m_path_basedatos );
    config.setModal(true);
    config.move(825, 400);
    config.exec();
    return;
}

void PantallaPrincipal::on_botonConectar_clicked()
{
    if( !m_server->isListening() )
    {   /*  Si no está funcionando, vuelvo a iniciar el servidor    */
        if(m_server->listen(QHostAddress::Any , PUERTO))
            SetConectedInterface(true);
        else
            SetConectedInterface(false);

        connect(m_server , SIGNAL(newConnection()) , this , SLOT(NuevaConexion()));
    }
    else
        cout << "aplicacion ya conectada" << endl;
}

void PantallaPrincipal::SetVariables( QString &ruta_comunicacion) /*SLOT que setea las variables*/
{
    QString dbname;
    m_path_basedatos  = ruta_comunicacion;

    if (m_path_basedatos.endsWith(NOMBRE_ARCHIVO_BASEDATOS) == false)
        m_path_basedatos.append(NOMBRE_ARCHIVO_BASEDATOS);

    {
        dbname = QSqlDatabase::database().connectionName(); /* dejar las llaves. La Bibliografia de removeDatabase lo pide*/
        QSqlDatabase::database().close();
    }
    QSqlDatabase::removeDatabase(dbname);
    setUpBaseDatos();
    return;
}

void PantallaPrincipal::setUpBaseDatos() const    /*Creo y abro la base de datos*/
{
    QSqlDatabase base_datos = QSqlDatabase::addDatabase(TYPE_DB);
    base_datos.setDatabaseName(m_path_basedatos);

    if (!base_datos.open())
    {
        cout << "fallo al abrir la base de datos" << endl;
        exit(1);    /*$$$$ No utilizar exit*/
    }

    QSqlQuery tabla(base_datos);
    QString accion("CREATE TABLE IF NOT EXISTS aspiradora"
                   "(numero VARCHAR(2) NOT NULL PRIMARY KEY,"   /*Número para poder contabilizar*/
                   "fecha DATE,"                          /*Fecha en mes y año (MM/YYYY)*/
                   "tiempo_ini TIME,"                     /*Tiempo de arranque en horas y minutos (HH:mm)*/
                   "tiempo_fin TIME);");                  /*Tiempo de finalizacion en horas y minutos (HH:mm)*/

    tabla.prepare(accion);
    if ( !tabla.exec() )
    {
        cout << "Error al crear la tabla" << endl;
        exit(1);     /*$$$$ No utilizar exit*/
    }
    return;
}

void PantallaPrincipal::SetConectedInterface(bool activated) const
{
    QString imagen_aspiradora = RUTA_IMAGEN;
    if (activated == true)
    {
        imagen_aspiradora += "aspiradora.png";
        ui->ImagenAspiradora->setToolTip("ASPIRADORA CONECTADA");
    }
    else
    {
        imagen_aspiradora += "aspiradora_desconectada.png";
        ui->ImagenAspiradora->setToolTip("ASPIRADORA DESCONECTADA");
    }
    ui->ImagenAspiradora->setPixmap(QPixmap(imagen_aspiradora));
    ui->botonInicio->setEnabled(activated);
    ui->botonAbajo->setEnabled(activated);
    ui->botonArriba->setEnabled(activated);
    ui->botonIzquierda->setEnabled(activated);
    ui->botonDerecha->setEnabled(activated);
    return;
}

void PantallaPrincipal::LeerWiFi()
{
    char caracter;
    m_socket->read(&caracter, sizeof(char));

    do {
        if (m_mensaje_recibido.length() == 0 && caracter == BYTE_INICIO)    //Solo arranco si es un BIT_INICIO
            m_mensaje_recibido.append(caracter);
        else if (m_mensaje_recibido.length() > 0 && m_mensaje_recibido.length() < 20)    //A lo sumo leo 20 caracteres
        {
            if (caracter == BYTE_INICIO)    //Reinicio si me llega otro BIT_INICIO
                m_mensaje_recibido = "";

            m_mensaje_recibido.append(caracter);

            if (caracter == BYTE_FINAL)    //Si llega un BIT_FINAL lo analizo
                AnalizarMensaje();
        }
        else
            m_mensaje_recibido = "";

    } while (m_socket->read(&caracter,sizeof(char)) > 0);
    return;
}


void PantallaPrincipal::AnalizarMensaje()
{
   if ( m_mensaje_recibido.startsWith("<L") )
    {
        bool aux1;
        int minutos_limpieza = m_mensaje_recibido.midRef(2,4).toInt(&aux1);

        if (m_mensaje_recibido.length() == 7 && aux1 == true)    /*Inicio nomral*/
        {
            QMessageBox::information(NULL, "Información", "Limpieza iniciada desde la aspiradora.");
            guardarBaseDatos(minutos_limpieza);
        }
    }
    m_mensaje_recibido = "";
    return;
}

bool PantallaPrincipal::guardarBaseDatos(int inicio, int delay_inicio) const
{
    QTime tiempo_actual     = QTime::currentTime();
    QSqlDatabase base_datos = QSqlDatabase::database();
    QSqlQuery tabla(base_datos);
    QString mensaje = "INSERT INTO aspiradora(numero,fecha,tiempo_ini,tiempo_fin) VALUES ('";
    mensaje.append(getNumero());    /*Armo el mensaje para la base de datos*/
    mensaje.append("', '");
    mensaje.append(QDate::currentDate().toString("dd/MM/yyyy"));
    mensaje.append("', '");
    mensaje.append(tiempo_actual.addSecs(delay_inicio * 60).toString("hh:mm"));
    mensaje.append("', '");
    mensaje.append(tiempo_actual.addSecs(delay_inicio * 60 + inicio * 60).toString("hh:mm"));
    mensaje.append("');");

    tabla.prepare(mensaje);

    return tabla.exec();
}

QString PantallaPrincipal::getNumero() const
{
    int numero = -1;
    QSqlDatabase base_datos = QSqlDatabase::database();
    QSqlQuery tabla(base_datos);
    QString mensaje = "SELECT * FROM aspiradora";
    tabla.prepare(mensaje);
    if (tabla.exec())
    {
        tabla.last();
        numero = tabla.value(NUMERO).toInt();
        numero++;
    }
    return QString::number(numero);
}

void PantallaPrincipal::on_botonArriba_clicked()
{
    m_mensaje_enviar.append("<CU>");

    ui->botonDerecha->setChecked(false);
    ui->botonIzquierda->setChecked(false);
    ui->botonAbajo->setChecked(false);
    return;
}
void PantallaPrincipal::on_botonDerecha_clicked()
{
    m_mensaje_enviar.append("<CR>");

    ui->botonAbajo->setChecked(false);
    ui->botonIzquierda->setChecked(false);
    ui->botonArriba->setChecked(false);

    return;
}
void PantallaPrincipal::on_botonAbajo_clicked()
{
    m_mensaje_enviar.append("<CD>");

    ui->botonDerecha->setChecked(false);
    ui->botonIzquierda->setChecked(false);
    ui->botonArriba->setChecked(false);
    return;
}
void PantallaPrincipal::on_botonIzquierda_clicked()
{
    m_mensaje_enviar.append("<CL>");

    ui->botonDerecha->setChecked(false);
    ui->botonAbajo->setChecked(false);
    ui->botonArriba->setChecked(false);
    return;
}


PantallaPrincipal::~PantallaPrincipal()
{   /*  Cierro toda la comunicación */
    if (m_socket->isOpen())
        m_socket->close();
    m_server->close();
    QSqlDatabase::database().close();

    GuardarConfig();    /*  Guardo la configuración de la base de datos */

    delete ui;
}
