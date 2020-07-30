#include "numeroplanetas.h"
#include "ui_numeroplanetas.h"
#include <QMessageBox>
#include <QDebug>
#include <windows.h>
NumeroPlanetas::NumeroPlanetas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NumeroPlanetas)
{
    ui->setupUi(this);
}

NumeroPlanetas::~NumeroPlanetas()
{
    delete ui;
}

int NumeroPlanetas::getNumeroCuerpos()
{
    return Aux_Numero;
}

void NumeroPlanetas::on_NextNP_clicked()
{
    if(ui->spinBox->value()>=2){
        Aux_Numero=ui->spinBox->value();
        emit buttonPressed();
    }
    else{
        QMessageBox::warning(this,"Planetas","Para simular el sistema se necesitan minimo 2 planetas");
    }
}
