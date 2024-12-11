#include "pantallaconfig.h"
#include "ui_pantallaconfig.h"

PantallaConfig::PantallaConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PantallaConfig)
{
    ui->setupUi(this);
}

PantallaConfig::~PantallaConfig()
{
    delete ui;
}
