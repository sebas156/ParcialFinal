#include "inicializarvalores.h"
#include "ui_inicializarvalores.h"
#include <QMessageBox>
#include "planet_grafic.h"

inicializarvalores::inicializarvalores(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inicializarvalores)
{
    ui->setupUi(this);
    ui->ContadorPlaneta->setNum(NumeroP);
}

inicializarvalores::~inicializarvalores()
{
    delete ui;
}

PLANET_GRAFIC *inicializarvalores::getPlaneta()
{
    return aux;
}

void inicializarvalores::recordatorio(){
    QMessageBox::warning(this,"Planetas","Uno de los planetas que ingreses debe ser la referencia. \nEs decir, el cuerpo alrededor del cual van a viajar todos los demas.\nPara lo cual este cuerpo debe ser el de mayor masa y velocidad igual a cero.");
}
void inicializarvalores::on_pushButton_clicked() // ponerle un return
{
    float posx, posy, velx , vely ,r, mass;
    posx=ui->VPosX->value();
    posy=ui->VPosY->value();
    velx=ui->VVX->value();
    vely=ui->VVY->value();
    mass=ui->MP->value();
    r=ui->RP->value();
    aux = new PLANET_GRAFIC(posx, posy, velx , vely ,r, mass);
    ui->ContadorPlaneta->setNum(++NumeroP);
    emit buttonPressed();
}
