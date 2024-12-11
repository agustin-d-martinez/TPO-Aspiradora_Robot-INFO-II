#include "pestaniahistorial.h"
#include "ui_pestaniahistorial.h"

PestaniaHistorial::PestaniaHistorial(QWidget *parent) :QDialog(parent),ui(new Ui::PestaniaHistorial)
{
    ui->setupUi(this);
    setUpTabla();
    crearTabla();
}

PestaniaHistorial::~PestaniaHistorial()
{
    delete ui;
}

void PestaniaHistorial::on_tablaHistorial_cellPressed(int row, int column)
{
    ui->botonBorrar->setEnabled(true);
    cout << "presionaste: " << row << ", " << column << endl;
}

void PestaniaHistorial::on_botonBorrar_clicked()    /*Llamo a borrar una fila*/
{
    if (borrarFila(ui->tablaHistorial->currentRow()))
        ui->botonBorrar->setEnabled(false);
    else
    {
        QMessageBox::critical(NULL, "ERROR AL BORRAR", "No se pudo borrar correctamente. Vuelva a intentarlo");
        cout << "FALLO AL BORRAR EL REGISTRO" << endl;
    }
    return;
}

void PestaniaHistorial::on_botonBorrarTodo_clicked()    /*Borro la tabla y la base de datos entera*/
{
    int filas_total = ui->tablaHistorial->rowCount();
    bool error      = false;

    QMessageBox msgBox;
    msgBox.setText("ESTAS SEGURO?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret)
    {
    case (QMessageBox::Yes):
        for(int i = 0; (i < filas_total) && (!error) ; i++)
        {
            if (!borrarFila(0))
            {
                error = true;
                cout << "FALLO AL BORRAR EL REGISTRO" << endl;
                QMessageBox::critical(NULL, "ERROR AL BORRAR", "No se pudo borrar correctamente. Vuelva a intentarlo");
            }
        }
        break;

    case (QMessageBox::No):
        msgBox.close();
        break;

    }


    return;
}

void PestaniaHistorial::setUpTabla() const    /*Inicializo mi tabla*/
{
    ui->tablaHistorial->setColumnCount(COLUMNAS);
    QStringList apendice= {"NUM","FECHA", "HORA INICIO", "HORA FIN"};
    ui->tablaHistorial->setHorizontalHeaderLabels(apendice);
    ui->tablaHistorial->hideColumn(POS_NUMERO);
}

void PestaniaHistorial::crearTabla() const    /*Creo la tabla con la base de datos*/
{
    int i = 0;
    QSqlDatabase base_datos = QSqlDatabase::database();
    QSqlQuery historial(base_datos);

    QString consulta_historial;

    ui->tablaHistorial->setRowCount(0);
    consulta_historial.append("SELECT * FROM aspiradora");
    historial.prepare(consulta_historial);

    if ( !historial.exec() )
    {
        QMessageBox::critical(NULL, "ERROR AL CREAR", "No se pudo crear la tabla correctamente. Vuelva a intentarlo");
        cout << "error al intentar crear la tabla" << endl;
    }
    historial.first();

    do {
        ui->tablaHistorial->insertRow(i);
        ui->tablaHistorial->setItem(i, POS_NUMERO, new QTableWidgetItem (historial.value(NUMERO).toString()));
        ui->tablaHistorial->setItem(i, POS_FECHA, new QTableWidgetItem (historial.value(FECHA).toString()));
        ui->tablaHistorial->setItem(i, POS_TIEMPO_INI, new QTableWidgetItem (historial.value(TIEMPO_INI).toString()));
        ui->tablaHistorial->setItem(i, POS_TIEMPO_FIN, new QTableWidgetItem (historial.value(TIEMPO_FIN).toString()));
        i++;
    } while (historial.next());

    /*Detalles decorativos*/
    ui->tablaHistorial->sortByColumn(POS_FECHA);
    ui->tablaHistorial->resizeColumnsToContents();
    return;
}

bool PestaniaHistorial::borrarFila(int fila) const    /*Borro una fila*/
{
    bool exito = true;
    QSqlDatabase base_datos = QSqlDatabase::database();

    QSqlQuery historial(base_datos);
    QString borra_basedatos = "DELETE FROM aspiradora WHERE numero = ";
    borra_basedatos.append(ui->tablaHistorial->item(fila, POS_NUMERO)->text());
    historial.prepare(borra_basedatos);

    if ( !historial.exec() )
        exito = false;
    else
        ui->tablaHistorial->removeRow(fila);

    return exito;
}

void PestaniaHistorial::on_botonActualizar_clicked()
{
    crearTabla();
    return;
}

void PestaniaHistorial::on_botonOk_clicked()
{
    close();
}

