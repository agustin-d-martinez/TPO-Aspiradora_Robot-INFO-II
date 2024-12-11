#ifndef PANTALLAPRINCIPAL_H
#define PANTALLAPRINCIPAL_H

#define RUTA_IMAGEN "..\\AspiradoraRobot\\fotos\\fotos_pantalla_principal\\"


#include <QMainWindow>
#include <QDate>
//---Base de datos-----------------------------
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

//---Paginas-----------------------------------
#include "pestaniahistorial.h"
#include "pestaniaconfig.h"
#include "pantallaacercade.h"
#include "pantallahora.h"
#include "configuracion.h"

//---Com WIFI----------------------------------
#include <QTcpServer>
#include <QTcpSocket>

//---Configuarición----------------------------
#include <QMessageBox>
#include <iostream>
#include <QFile>
#include <qtextstream.h>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class PantallaPrincipal; }
QT_END_NAMESPACE


class PantallaPrincipal : public QMainWindow
{
    Q_OBJECT

    public:
        PantallaPrincipal(QWidget *parent = nullptr);
        ~PantallaPrincipal();

    public slots:
        void SetVariables( QString &ruta_comunicacion);

    private slots:
        void on_BotonBaseDatos_clicked();
        void on_botonInicio_clicked();
        void on_botonConfig_clicked();
        void on_botonInfo_clicked();

        void on_botonArriba_clicked();
        void on_botonAbajo_clicked();
        void on_botonIzquierda_clicked();
        void on_botonDerecha_clicked();

        //--Comunicacion---------------
        void LeerWiFi();
        void on_botonConectar_clicked();
        void NuevaConexion();

private:
        //--Variables---------------
        Ui::PantallaPrincipal   *ui;
        QTcpSocket              * m_socket;
        QTcpServer              * m_server;

        QString m_mensaje_recibido;
        QString m_mensaje_enviar;
        QString m_path_basedatos;

        //--Funciones---------------
        void  inicializar();
        void  SetConectedInterface( bool  activated ) const;

        void  setUpBaseDatos() const;
        bool  guardarBaseDatos( int  tiempo , int  delay_inicio = 0 ) const;

        void  AnalizarMensaje();

        bool  LeerConfig();
        bool  GuardarConfig();

        QString  getNumero() const;
};
#endif // PANTALLAPRINCIPAL_H
