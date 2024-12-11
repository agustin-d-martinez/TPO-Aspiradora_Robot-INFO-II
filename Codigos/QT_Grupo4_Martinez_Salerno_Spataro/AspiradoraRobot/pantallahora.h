#ifndef PANTALLAHORA_H
#define PANTALLAHORA_H

#include <QDialog>

//---Base de datos-----------------------------
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

//---Com WIFI----------------------------------
#include <QTcpSocket>
#include <QString>

//---Configuarición----------------------------
#include "configuracion.h"
#include <QMessageBox>
#include <iostream>

using namespace std;

namespace Ui{class PantallaHora;}

class PantallaHora : public QDialog
{
    Q_OBJECT

    public:
        explicit PantallaHora(QWidget *parent = nullptr);
        ~PantallaHora();
        void setVariables(QString *a);

    private slots:
        void on_botonInicioRapido_clicked();
        void on_botonProgramar_clicked();
        void on_tiempoRapido_timeChanged(const QTime &time);
        void on_tiempoProg_timeChanged(const QTime &time);
        void on_boton_guardar_clicked();

private:
        //--Variables---------------
        Ui::PantallaHora    * ui;
        QString             * m_mensaje_enviar;

        //--Funciones---------------
        QString  getHoraInicial() const;
        QString  getNumero() const;
        QString  getHoraFinal() const;
        QString  rellenarCeros(unsigned int  &numero) const;

        void  enviarMensaje();
        bool  Tiempo_valido();
};

#endif // PANTALLAHORA_H
