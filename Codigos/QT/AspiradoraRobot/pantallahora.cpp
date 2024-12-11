#include "pantallahora.h"
#include "ui_pantallahora.h"
PantallaHora::PantallaHora(QWidget *parent) :QDialog(parent),ui(new Ui::PantallaHora)
{    
    ui->setupUi(this);
    QTime cero= QTime::fromString("0:00", "H:mm");
    ui->tiempoRapido->setTime(cero);
    ui->tiempoProg->setTime(cero);
    ui->tiempoP1->setTime(cero);
    ui->boton_guardar->setDisabled(true);

    ui->text_information->hide();
}

PantallaHora::~PantallaHora()
{
    delete ui;
}

void PantallaHora::on_boton_guardar_clicked()    /*Se comunica con la aspiradora y guarda el valor en la base de datos*/
{
    QSqlDatabase base_datos = QSqlDatabase::database();

    QSqlQuery tabla(base_datos);
    QString mensaje = "INSERT INTO aspiradora(numero,fecha,tiempo_ini,tiempo_fin) VALUES ('";

    ui->text_information->show();
    if (Tiempo_valido())
    {
        mensaje.append(getNumero());    /*Armo el mensaje para la base de datos*/
        mensaje.append("', '");
        mensaje.append(QDate::currentDate().toString());
        mensaje.append("', '");
        mensaje.append(getHoraInicial());
        mensaje.append("', '");
        mensaje.append(getHoraFinal());
        mensaje.append("');");
        tabla.prepare(mensaje);

        if (!tabla.exec())
        {
            ui->text_information->setText("Fallo al guardar la información.");

        }
        else
        {
            ui->text_information->setText("El tiempo se ha guardado con exito.");
            enviarMensaje();
        }

    }
    else
        ui->text_information->setText("Hora inválida. Elija horarios libres para aspirar");
    return;
}

void PantallaHora::on_botonInicioRapido_clicked()    /*Cambio a inicio rápido*/
{
    QTime cero = QTime::fromString("0:00", "H:mm");

    ui->tiempoRapido->setEnabled(true);

    ui->tiempoProg->setDisabled(true);
    ui->tiempoP1->setDisabled(true);

    if (ui->tiempoRapido->time() == cero)
        ui->boton_guardar->setDisabled(true);
    else
        ui->boton_guardar->setEnabled(true);

    return;
}

void PantallaHora::on_botonProgramar_clicked()    /*Cambio a inicio programado*/
{
    QTime cero = QTime::fromString("0:00", "H:mm");

    ui->tiempoProg->setEnabled(true);
    ui->tiempoP1->setEnabled(true);

    ui->tiempoRapido->setDisabled(true);

    if (ui->tiempoProg->time() == cero)
        ui->boton_guardar->setDisabled(true);
    else
        ui->boton_guardar->setEnabled(true);
    return;
}

void PantallaHora::on_tiempoRapido_timeChanged(const QTime &time)    /*Inicio rápido*/
{
    QTime cero= QTime::fromString("0:00", "H:mm");
    if (time == cero)
        ui->boton_guardar->setDisabled(true);
    else
        ui->boton_guardar->setEnabled(true);
    return;
}

void PantallaHora::on_tiempoProg_timeChanged(const QTime &time)    /*Inicio programado*/
{
    QTime cero= QTime::fromString("0:00","H:mm");

    if (time == cero)
        ui->boton_guardar->setDisabled(true);
    else
        ui->boton_guardar->setEnabled(true);

    return;
}

QString PantallaHora::getHoraInicial() const    /*Funcion que obtiene hora de arranque*/
{
    QTime hora_aux= QTime::currentTime();
    QString hora_inicial;

    if (ui->botonProgramar->isChecked())
        hora_aux = hora_aux.addSecs(ui->tiempoP1->time().hour()*60*60 + ui->tiempoP1->time().minute()*60);

    hora_inicial = hora_aux.toString();
    return hora_inicial;
}

QString PantallaHora::getHoraFinal() const    /*Funcion que obtiene hora finalizacion*/
{
    QTime tiempo_aux = QTime::currentTime();
    QString hora_final;

    if (ui->botonInicioRapido->isChecked())
        tiempo_aux = tiempo_aux.addSecs(ui->tiempoRapido->time().hour() *60*60 + ui->tiempoRapido->time().minute()*60);
    else if (ui->botonProgramar->isChecked())
    {
        int calculo = ui->tiempoP1->time().hour() * 60 * 60 + ui->tiempoP1->time().minute() * 60;
        calculo    += ui->tiempoProg->time().hour() * 60 * 60 + ui->tiempoProg->time().minute() * 60;
        tiempo_aux  = tiempo_aux.addSecs(calculo);
    }
    hora_final = tiempo_aux.toString();

    return hora_final;
}

QString PantallaHora::getNumero() const    /*Funcion que obtiene num barrida*/
{
    signed int numero = -1;
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

bool PantallaHora::Tiempo_valido ()
{
    bool is_valid = true;
    QDateTime inicial(QDate::currentDate(), QTime::currentTime());
    QDateTime final(QDate::currentDate(), ui->tiempoRapido->time());
    QDateTime inicial_db;
    QDateTime final_db;

    QSqlDatabase base_datos = QSqlDatabase::database();
    QSqlQuery tabla(base_datos);
    QString mensaje = "SELECT * FROM aspiradora";

    if ( ui->botonProgramar->isChecked() )
    {
        int calculo = ui->tiempoP1->time().hour() * 60 * 60 + ui->tiempoP1->time().minute() * 60;
        calculo    += ui->tiempoProg->time().hour() * 60 * 60 + ui->tiempoProg->time().minute() * 60;
        final  = final.addSecs(calculo);
        inicial = inicial.addSecs(ui->tiempoP1->time().hour()*60*60 + ui->tiempoP1->time().minute()*60);
    }

    if( inicial >= final )
        final = final.addDays(1);

    tabla.prepare(mensaje);
    if ( !tabla.exec() )
        is_valid = false;

    tabla.first();
    do
    {
        inicial_db.setDate(QDate::fromString(tabla.value(FECHA).toString()));
        inicial_db.setTime(QTime::fromString(tabla.value(TIEMPO_INI).toString()));
        final_db.setDate(QDate::fromString(tabla.value(FECHA).toString()));
        final_db.setTime(QTime::fromString(tabla.value(TIEMPO_FIN).toString()));
        if(inicial_db >= final_db)
            final_db = final_db.addDays(1);

        if(inicial <= final_db && inicial_db <= final )
            is_valid = false;
    }while( tabla.next() && is_valid );

    return is_valid;
}

void PantallaHora::enviarMensaje()
{
    unsigned int tiempo_limpieza;
    unsigned int tiempo_inicio;
    QString mensaje(BYTE_INICIO);

    if ( ui->botonInicioRapido->isChecked() )
    {
        mensaje.append("L");    /*creo el mensaje "<L"*/
        tiempo_limpieza = ui->tiempoRapido->time().minute() + ui->tiempoRapido->time().hour() * 60;
        mensaje.append(rellenarCeros(tiempo_limpieza));
    }
    else
    {
        mensaje.append("P");    /*creo el mensaje "<P"*/
        tiempo_limpieza = ui->tiempoProg->time().minute() + ui->tiempoProg->time().hour() * 60;
        mensaje.append(rellenarCeros(tiempo_limpieza));
        mensaje.append("/");

        tiempo_inicio = ui->tiempoP1->time().minute() + ui->tiempoP1->time().hour() * 60;
        mensaje.append(rellenarCeros(tiempo_inicio));
    }

    mensaje.append(BYTE_FINAL);

    m_mensaje_enviar->append(mensaje);

    cout << "Enviaste: " << mensaje.toStdString() << endl;
}

QString PantallaHora::rellenarCeros(unsigned int &numero) const
{
    QString aux = "";

    if ( numero < 1000 && numero > 100 )    /*Relleno con 0*/
        aux.append("0");
    else if ( numero < 100 && numero > 10 )
        aux.append("00");
    else if ( numero < 10 )
        aux.append("000");

    aux.append(QString::number(numero));
    return aux;
}

void PantallaHora::setVariables(QString *a)    /*Inicializo mi variable*/
{
    m_mensaje_enviar = a;
    return;
}




