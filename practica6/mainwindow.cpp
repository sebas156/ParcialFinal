#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inicializarvalores.h"
#include "numeroplanetas.h"
#include <QDebug>
#include <iostream>
#include <fstream>
#include <sstream>
#include <QMessageBox>
#include <cmath>
using namespace std;
string Convert (float number);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowTitle("SIMULACION");
    CuantosPlanetas = new NumeroPlanetas();
    ValoresIniciales = new inicializarvalores();
    ui->setupUi(this);
    h_limit=12000;                   //Asigna el tamaño de la interfaz
    v_limit=12000;
    timer=new QTimer(this);                 //crea el timer
    scene=new QGraphicsScene(this);         //crea la scene
    scene->setSceneRect(-6000,-6000,h_limit,v_limit);
    ui->graphicsView->setScene(scene);
    scene->addRect(scene->sceneRect());
    ui->graphicsView->resize(1200,1200);
    ui->graphicsView->setHorizontalScrollBarPolicy ( Qt :: ScrollBarAlwaysOff  ) ;
    ui->graphicsView->setVerticalScrollBarPolicy ( Qt :: ScrollBarAlwaysOff  ) ;
    qDebug()<< ui->graphicsView->size();
    this->resize(1000, 600);
    connect(CuantosPlanetas,SIGNAL(buttonPressed()),this,SLOT(AsignarNumeroPlanetas()));
    connect(ValoresIniciales,SIGNAL(buttonPressed()),this,SLOT(EstablecerValoresIniciales()));
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));
    timer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::IniciarSimulacion()
{
    ValoresIniciales->close();
    EncontarReferencia();
    IteradorMostrar=PlanetReference+1;
    ui->graphicsView->centerOn(SistemaSolar.at(PlanetReference)->getPlanet()->get_posX(),SistemaSolar.at(PlanetReference)->getPlanet()->get_posY());
    timer->start(6);
}

void MainWindow::RegistrarPosicion() // Registra la posicion de los planetas en un archivo.
{
    ofstream archivo("posiciones.txt",ios::app);
    if(archivo.fail())
         QMessageBox::warning(this,"ERROR","No se pudo abrir el archivo.");
    else {
        string Linea="";
        for(int fila =1;fila<SistemaSolar.size();fila++){
            Linea+= Convert(SistemaSolar.at(fila)->getPlanet()->get_posX()) + "    " +Convert(SistemaSolar.at(fila)->getPlanet()->get_posY())+"        ";
        }
        archivo<<Linea<<endl;
    }
    archivo.close();
}

void MainWindow::EncontarReferencia() // Encuentra el planeta mas masivo que esté en la lista de sistema solar.
{
    int max=0;
    for(int fila=0;fila<SistemaSolar.size();fila++){
        if(SistemaSolar.at(fila)->getPlanet()->get_masa()>max){
            max=SistemaSolar.at(fila)->getPlanet()->get_masa();
            PlanetReference=fila;
        }
    }
}

void MainWindow::on_start_clicked()
{
    CuantosPlanetas->show();

}

void MainWindow::AsignarNumeroPlanetas()
{
    CantidadPlanetas=CuantosPlanetas->getNumeroCuerpos();
    CuantosPlanetas->close();
    ValoresIniciales->recordatorio();
    ValoresIniciales->show();
}

void MainWindow::actualizar()
{
    float AXA,AYA;
    if(SistemaSolar.size()<CantidadPlanetas)
        return;
    for(int fila=0;fila<SistemaSolar.size();fila++){ // Estas lineas  de codigo realizan las sumas vectoriales necesarias para hallar la aceleracion resultante de un planeta con respecto a los otros.
        AXA=SistemaSolar.at(fila)->getPlanet()->getACX();
        AYA=SistemaSolar.at(fila)->getPlanet()->getACY();
        for(int columna=0;columna<SistemaSolar.size();columna++){
            if(columna!=fila){
                SistemaSolar.at(fila)->getPlanet()->aceleracion(SistemaSolar.at(columna)->getPlanet()->get_posX(),SistemaSolar.at(columna)->getPlanet()->get_posY(),SistemaSolar.at(columna)->getPlanet()->get_masa(),AXA,AYA);
            }
        }
    }
    for(int fila=0;fila<SistemaSolar.size();fila++){ // Se actualizan las posiciones y se verifica si ha ocurrido alguna colision.
            SistemaSolar.at(fila)->actualizar();
            if(fila != PlanetReference)
                VerificarSiSeColisiona(fila);
            MostrarCaracteristicas(); // Mustras als caracteristicas de cada planeta en la interfaz.
            RegistrarPosicion();
    }
    //ui->graphicsView->centerOn(SistemaSolar.at(PlanetReference)->getPlanet()->get_posX(),SistemaSolar.at(PlanetReference)->getPlanet()->get_posY());
    tiempo+=0.1;
    ui->lcdNumber->display(tiempo);
}

void MainWindow::EstablecerValoresIniciales()// Esatablezco las caracteristias iniciales de cada uno de los planetas.
{
    SistemaSolar.push_back(ValoresIniciales->getPlaneta());
    SistemaSolar.at(SistemaSolar.size()-1)->color=SistemaSolar.size();
    scene->addItem(SistemaSolar.back());
    if(ValoresIniciales->NumeroP-1==CantidadPlanetas)
        IniciarSimulacion();
}

void MainWindow::AumentarIterador()
{
    if(IteradorMostrar==SistemaSolar.size())
        IteradorMostrar=0;
    IteradorMostrar+=1;
}

void MainWindow::ActualizarCuerposCayendo()
{
    for(int i=0;i<ObjetosCayendoActualmente.size();i++){

        ObjetosCayendoActualmente.at(i)->actualizar(v_limit);//actualiza en esferagraf
        bordercollision(ObjetosCayendoActualmente.at(i)->getEsf());//actualiza el choque con el borde
    }
}


void MainWindow::VerificarSiSeColisiona(int fila) // Veriffica las colisiones entre planetas.
{
    float d1,d2;
    for (int posicion=0;posicion<SistemaSolar.size();posicion++) {
        if(posicion != fila)
        {
            d1=SistemaSolar.at(fila)->getPlanet()->get_Radio()+SistemaSolar.at(posicion)->getPlanet()->get_Radio();
            d2=pow(pow(SistemaSolar.at(fila)->getPlanet()->get_posX()-SistemaSolar.at(posicion)->getPlanet()->get_posX(),2)+pow(SistemaSolar.at(fila)->getPlanet()->get_posY()-SistemaSolar.at(posicion)->getPlanet()->get_posY(),2),0.5);
            if(d1>=d2){  // Las siguientes linas de codigo marcan los planetas que se han colisionado.
                SistemaSolar.at(fila)->getPlanet()->chocar=true;
                scene->removeItem(SistemaSolar.at(fila));
                if(posicion != PlanetReference){   //El planeta referencia o de mayor masa nunca se va a eliminar.
                    SistemaSolar.at(posicion)->getPlanet()->chocar=true; // Por lo que nunca se va a marcar como positivo.
                    scene->removeItem(SistemaSolar.at(posicion));
                }

            }
        }
    }
    for (int posicion=0;posicion<SistemaSolar.size();posicion++) {
        QList<PLANET_GRAFIC *>::iterator eliminar=SistemaSolar.begin(); // Estas lineas de codigo eliminan los planetas que esten marcados como true.
        if(SistemaSolar.at(posicion)->getPlanet()->chocar==true){       // Significa que que se han chocado y tiene que eliminarse.
            eliminar+=posicion;
            SistemaSolar.erase(eliminar);
            posicion=-1;
            EncontarReferencia(); // Una vez se han realizado las eliminaciones los planetas restantes van a cambiar de posicion. Por lo que se tiene que volver a encontrar la referencia.
            CantidadPlanetas=SistemaSolar.size(); // Una vez se realizaron las eliminaciones el numero de planeta se va a modificar.
            IteradorMostrar=PlanetReference+1;
        }
    }
}

void MainWindow::MostrarCaracteristicas() // Mustra las caracteristicas de cada planeta en cuestion.
{
    ui->PA->setNum(IteradorMostrar);
    ui->PXA->setNum(SistemaSolar.at(IteradorMostrar-1)->getPlanet()->get_posX());
    ui->PYA->setNum(SistemaSolar.at(IteradorMostrar-1)->getPlanet()->get_posY());
    ui->VXA->setNum(SistemaSolar.at(IteradorMostrar-1)->getPlanet()->get_velX());
    ui->VYA->setNum(SistemaSolar.at(IteradorMostrar-1)->getPlanet()->get_velY());
    ui->AXA->setNum(SistemaSolar.at(IteradorMostrar-1)->getPlanet()->getACX());
    ui->AYA->setNum(SistemaSolar.at(IteradorMostrar-1)->getPlanet()->getACY());
}

string Convert (float number){
    number=number*100;   // Aproxima los numeros float con dos decimales para luego guardarlos en el archivo.
    number=round(number);
    number/=100;
    ostringstream buff;
    buff<<number;
    return buff.str();
}

void MainWindow::on_senal_clicked()
{
    AumentarIterador();
}

int MainWindow::GenerarPosicionAleatoria()
{
    srand(time(NULL));
    int PosicionLimite=SistemaSolar.at(PlanetReference)->getPlanet()->get_posX()-500 ;
    int posicionAparacer=PosicionLimite +rand()%( PosicionLimite+1000 -1);
    return posicionAparacer;
}

void MainWindow::bordercollision(cuerpo *b)//son los choques con los bordes
{
    if(b->get_posX()<SistemaSolar.at(PlanetReference)->getPlanet()->get_posX()-500){
        b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), b->get_Radio(), b->get_posY()) ;//con el borde izquierdo

    }
    if(b->get_posX()>SistemaSolar.at(PlanetReference)->getPlanet()->get_posX()+500){//posicion con el borde derecho.
        b->set_vel(-1*b->get_e()*b->get_velX(),b->get_velY(), h_limit-b->get_Radio(), b->get_posY());
    }
    if(b->get_posY()<SistemaSolar.at(PlanetReference)->getPlanet()->get_posY()-500){//choque con el borde superior.
        b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), (b->get_posX()), b->get_Radio());
    }
    if(b->get_posY()>SistemaSolar.at(PlanetReference)->getPlanet()->get_posY()+500){//choque con el borde inferior.
        b->set_vel(b->get_velX(),-1*b->get_e()*b->get_velY(), b->get_posX(), v_limit-b->get_Radio());
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(SistemaSolar.size()<1){
        QMessageBox::warning(this,"INVALIDO", "No se pueden generar objeto cayendo si no hay planetas disponibles");
        return;
    }
    cuerpograf *AuxCuerpo;
    AuxCuerpo=new cuerpograf(GenerarPosicionAleatoria(),SistemaSolar.at(PlanetReference)->getPlanet()->get_posY()-500);
    ObjetosCayendoActualmente.push_back(AuxCuerpo);
}
