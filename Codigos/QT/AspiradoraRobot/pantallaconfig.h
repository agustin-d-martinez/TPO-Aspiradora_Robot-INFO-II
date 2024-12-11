#ifndef PANTALLACONFIG_H
#define PANTALLACONFIG_H

#include <QDialog>

namespace Ui {
class PantallaConfig;
}

class PantallaConfig : public QDialog
{
    Q_OBJECT

public:
    explicit PantallaConfig(QWidget *parent = nullptr);
    ~PantallaConfig();

private:
    Ui::PantallaConfig *ui;
};

#endif // PANTALLACONFIG_H
