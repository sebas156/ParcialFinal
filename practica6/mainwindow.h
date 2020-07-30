#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "inicializarvalores.h"
#include "numeroplanetas.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QFile>
#include "planet.h"
#include "planet_grafic.h"
#include <QEventLoop>
#include <QGraphicsItem>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int CantidadPlanetas;       //Cantidad de planetas que abran en mi sistema solar.
    int iterar=0;               // Iterador para iterar sobre los planetas de la lista.
    QList<PLANET_GRAFIC *> SistemaSolar;   //lista con los cuerpos para mostrarlos.
    void IniciarSimulacion();
    void RegistrarPosicion();
    void EncontarReferencia();
private slots:
    void on_start_clicked();
    void AsignarNumeroPlanetas();
    void actualizar();
    void EstablecerValoresIniciales();
    void AumentarIterador();

    void on_senal_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;              //timer para los intervalos de tiempo entre cada frame
    QGraphicsScene *scene;      //scene que muestra los objetos animados
    float dt;                   //intervalo de tiempo entre frames
    int h_limit;                //longitud en X del mundo
    int v_limit;                //longitud en Y del mundo
    int PlanetReference;        // Guarda la posicion del planeta que tenga una mayor masa.
    int IteradorMostrar;
    float tiempo=0;
    inicializarvalores * ValoresIniciales;
    NumeroPlanetas * CuantosPlanetas;
    void VerificarSiSeColisiona(int);
    void MostrarCaracteristicas();

};

#endif // MAINWINDOW_H
