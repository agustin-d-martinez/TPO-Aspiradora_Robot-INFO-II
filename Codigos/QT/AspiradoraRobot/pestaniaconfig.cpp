#include "pestaniaconfig.h"
#include "ui_pestaniaconfig.h"

PestaniaConfig::PestaniaConfig(QWidget *parent) :QDialog(parent),ui(new Ui::PestaniaConfig)
{
    ui->setupUi(this);
    ui->editRuta->setStyleSheet(COLOR_VISION);
}

PestaniaConfig::~PestaniaConfig()
{
    delete ui;
}

void PestaniaConfig::on_editRuta_textChanged(const QString &arg1)    /*cambia label ruta*/
{
    ui->botonAplicarCambios->setEnabled(true);
    ui->botonAplicarCambios->setStyleSheet(COLOR_VISION);

    cout << arg1.toStdString() << endl;
    return;
}

void PestaniaConfig::on_botonAplicarCambios_clicked()    /*Aplica los cambios*/
{
    QString ruta_aux = ui->editRuta->text();

    if (ruta_aux.endsWith(".sqlite"))
    {
        connect(this, SIGNAL(send_Data(QString&,QString&)), parent(), SLOT(SetVariables(QString&,QString&)));
        emit send_Data(ruta_aux);
        QMessageBox::information(NULL, "Aplicar cambios", "Cambios aplicados");
        close();
    }
    else
        QMessageBox::information(NULL, "Error", "Ruta de base de datos o puerto inválidos");
    return;
}

void PestaniaConfig::on_botonCancelar_clicked()    /*Cierra la configuración*/
{
    close();
}

void PestaniaConfig::on_botonElegirRuta_clicked()    /*Muestra la nueva ruta*/
{
    QString ruta_nueva;
    ruta_nueva = QFileDialog::getExistingDirectory(this, "Ruta base de datos", ui->editRuta->text());
    ruta_nueva.append(NOMBRE_ARCHIVO_BASEDATOS);

    ui->editRuta->setText(ruta_nueva);
    return;
}

void PestaniaConfig::setVariables( QString &ruta)    /*Seteo ruta actual*/
{
    QFileInfo base_datos(ruta);
    ui->editRuta->setText(base_datos.absoluteFilePath());

    ui->botonAplicarCambios->setDisabled(true);
    ui->botonAplicarCambios->setStyleSheet(COLOR_DESHABILITADO);

    return;
}
