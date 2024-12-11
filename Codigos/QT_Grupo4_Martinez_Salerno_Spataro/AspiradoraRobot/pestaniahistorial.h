#ifndef PESTANIAHISTORIAL_H
#define PESTANIAHISTORIAL_H

#include <QDialog>

//---Base de datos-----------------------------
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

//---Configuarición----------------------------
#include "configuracion.h"
#include <QMessageBox>
#include <iostream>

using namespace std;

namespace Ui{class PestaniaHistorial;}

class PestaniaHistorial : public QDialog
{
    Q_OBJECT

    public:
        explicit PestaniaHistorial(QWidget *parent = nullptr);
        ~PestaniaHistorial();

    private slots:
        void on_tablaHistorial_cellPressed(int row, int column);
        void on_botonBorrar_clicked();
        void on_botonBorrarTodo_clicked();
        void on_botonActualizar_clicked();

        void on_botonOk_clicked();

private:
        //--Variables---------------
        Ui::PestaniaHistorial * ui;

        //--Funciones---------------
        void  setUpTabla() const;
        void  crearTabla() const ;
        bool  borrarFila(int  i) const;
};

#endif // PESTANIAHISTORIAL_H
