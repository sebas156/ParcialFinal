#ifndef INICIALIZARVALORES_H
#define INICIALIZARVALORES_H

#include <QWidget>
#include "planet.h"
#include "planet_grafic.h"

namespace Ui {
class inicializarvalores;
}

class inicializarvalores : public QWidget
{
    Q_OBJECT

public:
    explicit inicializarvalores(QWidget *parent = nullptr);
    ~inicializarvalores();
    int NumeroP=1;
    PLANET_GRAFIC * aux;  // Auxiliar para agregar a la lista.
    PLANET_GRAFIC * getPlaneta();
    void recordatorio();
signals:
    void buttonPressed();

private slots:
    void on_pushButton_clicked();

private:
    Ui::inicializarvalores *ui;
};

#endif // INICIALIZARVALORES_H
