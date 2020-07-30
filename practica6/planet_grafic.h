#ifndef PLANET_GRAFIC_H
#define PLANET_GRAFIC_H

#include <QPainter>
#include <QGraphicsItem>
#include <stdlib.h>     /* srand, rand, abs */
#include <time.h>       /* time */
#include "planet.h"

class PLANET_GRAFIC: public QGraphicsItem
{
public:
    int color;
    PLANET_GRAFIC(float posx, float posy, float velx , float vely ,float r, float mass);
    ~PLANET_GRAFIC();
    QRectF boundingRect() const;    //necesario definirla, devuelve el rectangulo que encierra el objeto
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //define como se pintara el objeto
    void actualizar();
    PLANET* getPlanet();
private:
    PLANET * esf;
};

#endif // PLANET_GRAFIC_H
