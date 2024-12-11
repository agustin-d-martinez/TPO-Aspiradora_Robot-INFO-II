#ifndef PESTANIACONFIG_H
#define PESTANIACONFIG_H

#include <qfiledialog.h>        // <-- Para buscar carpetas

//---Configuarición----------------------------
#include "configuracion.h"
#include <QMessageBox>
#include <iostream>
#include <QDialog>

using namespace std;

namespace Ui {class PestaniaConfig;}

class PestaniaConfig : public QDialog
{
    Q_OBJECT

    public:
        explicit PestaniaConfig(QWidget *parent = nullptr);
        ~PestaniaConfig();
        void setVariables(QString &ruta);

    private slots:
        void on_editRuta_textChanged(const QString &arg1);
        void on_botonAplicarCambios_clicked();
        void on_botonCancelar_clicked();
        void on_botonElegirRuta_clicked();

    signals:
        void  send_Data(QString  &ruta);

    private:
        //--Variables---------------
        Ui::PestaniaConfig * ui;

        //--Funciones---------------
        unsigned int  buscar_puertos( void );
};

#endif // PESTANIACONFIG_H
