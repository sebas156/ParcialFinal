#ifndef CUERPOGRAF_H
#define CUERPOGRAF_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "cuerpo.h"

class cuerpograf: public QGraphicsItem
{
public:
    cuerpograf(float,float,float);
    ~cuerpograf();
    QRectF boundingRect() const;    //necesario definirla, devuelve el rectangulo que encierra el objeto
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //define como se pintara el objeto
    void setEscala(float s);
    void actualizar(float v_lim);
    void CambiarColor();
    cuerpo* getEsf();
private:
    cuerpo* esf;
    float escala;
};

#endif // CUERPOGRAF_H
