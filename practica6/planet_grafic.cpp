#include "planet_grafic.h"
#include "QDebug"
#include <stdlib.h>     /* srand, rand, abs */
#include <time.h>       /* time */



PLANET_GRAFIC::PLANET_GRAFIC(float posx, float posy, float velx , float vely ,float r, float mass) //constructoor
{
    esf = new PLANET(posx,posy,velx,vely,mass,r);
}

PLANET_GRAFIC::~PLANET_GRAFIC()//destructor
{
    delete esf;
}

QRectF PLANET_GRAFIC::boundingRect() const
{
        return QRectF(-1*esf->get_Radio(),-1*esf->get_Radio(),2*esf->get_Radio(),2*esf->get_Radio());
}

void PLANET_GRAFIC::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(color==1)
        painter->setBrush(Qt::black);
    else if (color==2)
        painter->setBrush(Qt::blue);
    else if (color==3)
        painter->setBrush(Qt::yellow);
    else if (color==4)
        painter->setBrush(Qt::red);
    else if (color==5)
        painter->setBrush(Qt::green);
    else if (color==6)
        painter->setBrush(Qt::gray);
    painter->drawEllipse(boundingRect());    //dibuja una elipse encerrada en la boundingRect
}

void PLANET_GRAFIC::actualizar()
{
    esf->actualizar();//actualiza las posiciones del cuerpo
    setPos(esf->get_posX(),(esf->get_posY()));// actualiza posiciones en la interfaz
}

PLANET * PLANET_GRAFIC::getPlanet()
{
    return esf;
}
