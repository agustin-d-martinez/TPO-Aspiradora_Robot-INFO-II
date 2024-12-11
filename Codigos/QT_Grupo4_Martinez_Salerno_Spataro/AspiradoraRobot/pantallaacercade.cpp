#include "pantallaacercade.h"
#include "ui_pantallaacercade.h"

PantallaAcercaDe::PantallaAcercaDe(QWidget *parent) :QDialog(parent),ui(new Ui::PantallaAcercaDe)
{
    ui->setupUi(this);
}

PantallaAcercaDe::~PantallaAcercaDe()
{
    delete ui;
}

void PantallaAcercaDe::on_botonOk_clicked()
{
    close();
}
