#include "cuerpograf.h"
#include <time.h>       /* time */



cuerpograf::cuerpograf(float posx,float posy, float ay) : escala(1) //consrucyor
{
    float velx , vely ,r, mass, K, e, Ay;
    r = 10;
    Ay=ay
    mass = 50;
    velx = 0;
    vely = 0;
    K = 0.08;
    e = 0.15;
    esf = new cuerpo(posx,posy,velx,vely,mass,r,K,e,Ay);
}

cuerpograf::~cuerpograf()//destructor
{
    delete esf;
}

QRectF cuerpograf::boundingRect() const
{
        return QRectF(-1*escala*esf->get_Radio(),-1*escala*esf->get_Radio(),2*escala*esf->get_Radio(),2*escala*esf->get_Radio());
}

void cuerpograf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);        //asigna el color
    painter->drawEllipse(boundingRect());    //dibuja una elipse encerrada en la boundingRect
}

void cuerpograf::setEscala(float s)
{
    escala=s;
}

void cuerpograf::actualizar(float v_lim)
{
    esf->actualizar();//actualiza las posiciones del cuerpo
    setPos(esf->get_posX(),(v_lim-esf->get_posY()));// actualiza posiciones en la interfaz
}

cuerpo *cuerpograf::getEsf()
{
    return esf;
}
