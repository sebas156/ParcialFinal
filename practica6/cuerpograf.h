#ifndef CUERPOGRAF_H
#define CUERPOGRAF_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "cuerpo.h"
#include <stdlib.h>     /* srand, rand, abs */
#include <time.h>       /* time */

class cuerpograf: public QGraphicsItem
{
public:
    cuerpograf();
    ~cuerpograf();
    QRectF boundingRect() const;    //necesario definirla, devuelve el rectangulo que encierra el objeto
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //define como se pintara el objeto
    void setEscala(float s);
    void actualizar(float v_lim);
    cuerpo* getEsf();
private:
    cuerpo* esf;
    float escala;
};

#endif // CUERPOGRAF_H
