#ifndef PANTALLAACERCADE_H
#define PANTALLAACERCADE_H

#include <QDialog>

namespace Ui {class PantallaAcercaDe;}

class PantallaAcercaDe : public QDialog
{
    Q_OBJECT

    public:
        explicit PantallaAcercaDe(QWidget *parent = nullptr);
        ~PantallaAcercaDe();

    private slots:
        void on_botonOk_clicked();

    private:
        //--Variables---------------
        Ui::PantallaAcercaDe *ui;
};

#endif // PANTALLAACERCADE_H
