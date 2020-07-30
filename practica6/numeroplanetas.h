#ifndef NUMEROPLANETAS_H
#define NUMEROPLANETAS_H
#include "inicializarvalores.h"
#include <QWidget>
#include "planet.h"
#include "planet_grafic.h"

namespace Ui {
class NumeroPlanetas;
}

class NumeroPlanetas : public QWidget
{
    Q_OBJECT

public:
    explicit NumeroPlanetas(QWidget *parent = nullptr);
    ~NumeroPlanetas();
    int Aux_Numero=-1;
    int getNumeroCuerpos();
private slots:
    void on_NextNP_clicked();

signals:
    void buttonPressed();

private:
    Ui::NumeroPlanetas *ui;
};

#endif // NUMEROPLANETAS_H
